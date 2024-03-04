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
	exp_config<<AsString(~bg_rojo).ToStd()<<"\n";
	exp_config<<AsString(~bg_verde).ToStd()<<"\n";
	exp_config<<AsString(~bg_azul).ToStd();
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
		//leyendo primera linea (color rojo)
		getline (archivo_config, str_temp);
		bg_rojo.SetData(stoi(str_temp));
		//leyendo segunda linea (color verde)
		getline (archivo_config, str_temp);
		bg_verde.SetData(stoi(str_temp));
		//leyendo segunda linea (color azul)
		getline (archivo_config, str_temp);
		bg_azul.SetData(stoi(str_temp));
	//cerrando archivo
	archivo_config.close();
	
	
	//bg_verde.SetData(v);
	//bg_azul.SetData(a);
	
	

	
	//tree_resultado.SetScrollBarStyle(ScrollBar::StyleDefault());
	
	
	
	Icon(IconoPrograma::mi_icono());//icono del programa
	
	//configurando propiedades del columnlist
	clist_archivos.Mode(Upp::ColumnList::MODE_COLUMN);
	clist_archivos.ClickKill(true);
	clist_archivos.MultiSelect(true);
	clist_archivos.PopUpEx(false);
	
	//configurando propiedades del tree
	tree_resultado.PopUpEx(false);
	
	
	
	
	//tree_resultado.OpenDeep(0);
	//tree_resultado.Open(0);
	//tree_resultado.SetRoot(0, Null, clist_archivos.GetValue(i));
	//tree_resultado.SetRoot(0, Null, "rootu");
	
	
	
	
	
	
	
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
	
	//Borra datos anteriores del resultado
	tree_resultado.Clear();
	tree_resultado.Set(0,"Resultados");
	progreso.Set(0);
	
	//tree_resultado.SetScrollBarStyl(StyleNormal());
	//TreeCtrl
	//doc_busqueda.
	//DocEdit
	
	//verificando que se hayan cargado archivos
	if(clist_archivos.GetCount()!=0){
		
		bool encontrado=false; //cambia a true cuando se encuentra por lo menos en alguna linea de texto de los archivos cargados
		int contador=0; //para mostrar la cantidad de veces que se encontró el resultado
		int x=0;
		
		
		//strings temporales para guardar lineas leídas
		string str_aux_text="";
		string str_aux_text_ips="";
		
		
		for(int i=0;i<clist_archivos.GetCount();i++){
			//PromptOK((String)to_string(i));
			ifstream ifstream_archivo( (clist_archivos.GetValue(i)).ToStd() );
			ifstream ifstream_archivoIPs( ( files_ips[0] ).ToStd() );
			
			
			//añadiendo a tree
			x=tree_resultado.Add(0, Null, clist_archivos.GetValue(i));
		
			//lectura de cada linea
			while (getline (ifstream_archivoIPs, str_aux_text_ips)) {
				while (getline (ifstream_archivo, str_aux_text)) {
				
		
					if (str_aux_text.find(str_aux_text_ips) != std::string::npos) {
						
						//tree_resultado.Add(i+1, Null, str_aux_text);
						tree_resultado.Add(x, Null, str_aux_text);
						encontrado=true;
						contador++;
					}
				}
			}
			
			
			
			//cerrando archivos
			ifstream_archivoIPs.close();
			ifstream_archivo.close();
			
		}
		
		//TreeCtrl 
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
	
	Refresh();
}


void ProgramaBusqueda::Paint(Draw &w) {
	
	
	w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)), StrInt(AsString(~bg_verde)), StrInt(AsString(~bg_azul))));//RGB
	
	//Refresh();

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

