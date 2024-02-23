#include "header_principal.h"

#include <iostream>
#include <fstream>
#include <string>

#define IMAGECLASS IconoPrograma
#define  IMAGEFILE <BusquedaIPs/icono_principal.iml>
#include <Draw/iml.h>

using namespace std;

namespace Config {
	INI_INT(rojoFondo, 123456, "Number parameter");
};

//definicion de funciones
String GetKeyDescEx(int key);


//struct para coordenadas de widget
struct coordenadasWidget{
	int x0;
	int y0;
	int x1;
	int y1;
};

//manejo de tecla SUPR para eliminar elementos del columnlist
bool ProgramaBusqueda::Key(dword key, int count)
{
	if(GetKeyDescEx(key)=="Delete"){
		if (clist_archivos.GetCount()!=0) {
			//clist_archivos.Remove(clist_archivos.GetCursor());
			//clist_archivos.Remove(clist_archivos.RemoveSelection());
			clist_archivos.RemoveSelection();
		}
	}
	return false;
}

//constructor
void ProgramaBusqueda::Close(){
	
	//Config::rojoFondo=~bg_rojo;
	//Config::rojoFondo=bg_rojo.GetData();
	
	
	//PromptOK("cerrando");
	//lbl_2.SetText(AsString(~bg_rojo));
	
	//guardando configuracion
	//ofstream exp_config("configuracion_exportada.txt", std::ios::trunc);
	ofstream exp_config("config", std::ios::trunc);
	exp_config<<AsString(~bg_rojo).ToStd();
	exp_config.close();
	
	//cerrando programa
	delete this;
}

ProgramaBusqueda::ProgramaBusqueda()
{
	CtrlLayout(*this, "Busqueda");
	
	//sliders color de fondo
	bg_rojo.MinMax(0,255);
	bg_verde.MinMax(0,255);
	bg_azul.MinMax(0,255);
	
	
	
	//leyendo archivo configuracion
	ifstream archivo_config( "config" );
	string str_temp;
	getline (archivo_config, str_temp);
	bg_rojo.SetData(stoi(str_temp));
	
	
	
	
	
	//bg_verde.SetData(v);
	//bg_azul.SetData(a);
	
	
	
	
	
	Icon(IconoPrograma::mi_icono());//icono del programa
	
	//configurando propiedades del columnlist
	clist_archivos.Mode(Upp::ColumnList::MODE_COLUMN);
	clist_archivos.ClickKill(true);
	clist_archivos.MultiSelect(true);
	clist_archivos.PopUpEx(false);
	
	//configurando propiedades del tree
	tree_resultado.PopUpEx(false);
	tree_resultado.OpenDeep(0);
	//tree_resultado.Open(0);
	//tree_resultado.SetRoot(0, Null, clist_archivos.GetValue(i));
	
	
	
	
	
	//sacando colores del archivo config
	//int r,v,a;
	//cargar_configuracion(&r,&v,&a);
	//bg_rojo.SetData(r);
	//bg_verde.SetData(v);
	//bg_azul.SetData(a);
	
	//barra de progreso, configuracion inicial
	progreso.SetTotal(100);
	progreso.Set(0);
	
	
	
	
	btn_buscar << [=] { buscar(); };
}



void ProgramaBusqueda::DragAndDrop(Point p, PasteClip& d)
{
	//struct para guardar las coordenadas del widget
	coordenadasWidget coordenadas;
	coordenadas.x0 = clist_archivos.GetRect().TopLeft().x;
	coordenadas.y0 = clist_archivos.GetRect().TopLeft().y;
	coordenadas.x1 = clist_archivos.GetRect().BottomRight().x;
	coordenadas.y1 = clist_archivos.GetRect().BottomRight().y;
	
	//Condicional para que solo permita arrastrar y soltar dentro del widget esperado (de archivos MML's)
	if(p.x>=coordenadas.x0 && p.y>=coordenadas.y0 && p.x<=coordenadas.x1 && p.y<=coordenadas.y1){
		if(IsDragAndDropSource())
			return;
		if(AcceptFiles(d)) {
			files = GetFiles(d);
			
			//añadiendo archivos a columnList
			for(int i=0;i<files.GetCount();i++){
				clist_archivos.Add(files[i]);
				
				//Bar clickDerecho;
				//= clist_archivos.WhenBar;
			}
			
			Refresh();
		}
	}
	
	coordenadas.x0 = lbl_ips.GetRect().TopLeft().x;
	coordenadas.y0 = lbl_ips.GetRect().TopLeft().y;
	coordenadas.x1 = lbl_ips.GetRect().BottomRight().x;
	coordenadas.y1 = lbl_ips.GetRect().BottomRight().y;
	
	//Condicional para que solo permita arrastrar y soltar dentro del widget esperado (de archivo de IPs)
	if(p.x>=coordenadas.x0 && p.y>=coordenadas.y0 && p.x<=coordenadas.x1 && p.y<=coordenadas.y1){
		if(IsDragAndDropSource())
			return;
		
		if(AcceptFiles(d)) {
			
			//añadiendo archivo de IPs a variable y mostrando la ruta en el label "lbl_ips"
			files_ips = GetFiles(d);
			lbl_ips.SetText(files_ips[0]);
			
			
			//lbl_ips.SetText("funciona");
			Refresh();
		}
		
	}
	
}


void ProgramaBusqueda::LeftDrag(Point p, dword keyflags)
{
	if(files.GetCount()>0) {
		VectorMap<String, ClipData> data;
		AppendFiles(data, files);
	}
}


void ProgramaBusqueda::buscar(){
	
	
	//Color(StrInt(AsString(~bg_rojo))
	//StrInt(AsString(~bg_rojo)
	//PromptOK((String)bg_rojo.GetData());
	//lbl_2.SetText(AsString(~bg_rojo));
	
	if(clist_archivos.GetCount()!=0){
		
		bool encontrado=false; //cambia a true cuando se encuentra por lo menos en alguna linea de texto de los archivos cargados
		int contador=0; //para mostrar la cantidad de veces que se encontró el resultado
		
		string str_aux_text=""; // variable temporal para usar en la lectura de lineas de los archivos de texto cargados
		
		string str_aux_text_ips="";
		
		ofstream archivo_resultado("resultado_busqueda.txt", std::ios::trunc);
		
		for(int i=0;i<clist_archivos.GetCount();i++){
			ifstream ifstream_archivo( (clist_archivos.GetValue(i)).ToStd() );
			archivo_resultado<<"["<<(clist_archivos.GetValue(i)).ToStd()<<"]\n";
			
			//añadiendo a tree
			int x = tree_resultado.Add(0, Null, clist_archivos.GetValue(i));
			//tree_resultado.SetRoot(0, Null, clist_archivos.GetValue(i));
			
			
			
			
			ifstream ifstream_archivoIPs( ( files_ips[0] ).ToStd() );
			
			
			String aux_1;
			
			
			//lectura de cada linea de texto del archivo de IP's para cada uno de los archivos
			//cargados
			while (getline (ifstream_archivoIPs, str_aux_text_ips)) {
				while (getline (ifstream_archivo, str_aux_text)) {
					
					if (str_aux_text.find(str_aux_text_ips) != std::string::npos) {
						//archivo_resultado<<str_aux_text<<"\n";
						//tree_resultado.Add(x, Null, str_aux_text);
						//tree_resultado.Add(x, Null, contador);
						//tree_resultado.Add(x, Null, "insertando en pruebaX");// nivel 2 dentro de pruebaX
						//contador++;
						tree_resultado.Add(x, Null, contador);
						encontrado=true;
						contador++;
					}
				}
				archivo_resultado<<"\n";
			}
			
			archivo_resultado.close();
			
		}
		
		//tree_resultado.OpenDeep(0);
		
		progreso.Set(100);//la barra de progreso de la interfaz grafica se cambia al maximo, para indicar que ya finalizó la busqueda
		
		if(encontrado){
			string respuesta;
			respuesta = "Resultado Generado, encontrado ";
			respuesta += to_string(contador);
			respuesta += " veces";
			
			PromptOK((String)respuesta);
		}
		else{
			PromptOK("No se encontró en ningun archivo");
		}
	}
	else{
		PromptOK("Suba algún archivo");
	}
	
	
}


void ProgramaBusqueda::Paint(Draw &w) {
	
	//w.DrawRect(GetSize(),SColorPaper);
	w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)), StrInt(AsString(~bg_verde)), StrInt(AsString(~bg_azul))));//RGB
	tree_resultado.OpenDeep(0);
	Refresh();

}

//retorna nombre de tecla presionada
String GetKeyDescEx(int key){
	String desc = GetKeyDesc(key & ~K_KEYUP);
	if(key & K_KEYUP)
		desc << " UP";
	return desc;
}


GUI_APP_MAIN
{
	ProgramaBusqueda().Zoomable().Sizeable().Run();
}

