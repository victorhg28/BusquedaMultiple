#include "header_principal.h"

#include <iostream>
#include <fstream>
#include <string>

#define IMAGECLASS IconoPrograma
#define  IMAGEFILE <BusquedaIPs/icono_principal.iml>
#include <Draw/iml.h>

using namespace std;

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
			clist_archivos.RemoveSelection();
		}
	}
	return false;
}

//constructor
void ProgramaBusqueda::Close(){
	
	//Guardando configuracion de colores
	ofstream exp_config("config", std::ios::trunc);
	exp_config<<AsString(~bg_rojo).ToStd()<<"\n";
	exp_config<<AsString(~bg_verde).ToStd()<<"\n";
	exp_config<<AsString(~bg_azul).ToStd();
	exp_config.close();
	
	//cerrando el programa
	delete this;
}

void ProgramaBusqueda::SliderColorFondo() {

        //dynarect.SetRectX(50, ~slider);

        //text = "\1[C6*/@b " + AsString(~slider);
        //PromptOK("asdaa");
        miPicture.Background(Color(StrInt(AsString(~bg_rojo)), StrInt(AsString(~bg_verde)), StrInt(AsString(~bg_azul))));

    }

ProgramaBusqueda::ProgramaBusqueda()
{
	
	int v_rojo=0;
	int v_verde=0;
	int v_azul=0;
	
	CtrlLayout(*this, "Busqueda");
	
	//leyendo archivo configuracion (para color de fondo)
	ifstream archivo_config( "config" );
	string str_temp;
		getline (archivo_config, str_temp);//leyendo primera linea (color rojo)
		bg_rojo.SetData(stoi(str_temp));
		v_rojo=stoi(str_temp);
		
		getline (archivo_config, str_temp);//leyendo segunda linea (color verde)
		bg_verde.SetData(stoi(str_temp));
		v_verde=stoi(str_temp);
		
		getline (archivo_config, str_temp);//leyendo segunda linea (color azul)
		bg_azul.SetData(stoi(str_temp));
		v_azul=stoi(str_temp);
		
		//actualizando en interfaz
		miPicture.Background(Color(v_rojo,v_verde,v_azul));
		
	//cerrando archivo
	archivo_config.close();
	
	//icono del programa
	Icon(IconoPrograma::mi_icono());
	
	//configurando algunas propiedades de los widgets usados
	configuracionInicialWidgets();
	
	//lambdas para botones
	btn_buscar << [=] { buscar(); };
	
	bg_rojo << [=] { SliderColorFondo(); };
	bg_azul << [=] { SliderColorFondo(); };
	bg_verde << [=] { SliderColorFondo(); };
	
	//bg_rojo << THISFN(SliderRojo);
	
	//DrawDrawingOp();
	
	//DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)), StrInt(AsString(~bg_verde)), StrInt(AsString(~bg_azul))));//RGB	
	
	
}



void ProgramaBusqueda::DragAndDrop(Point p, PasteClip& d)
{
	//struct para guardar las coordenadas del widget
	coordenadasWidget coordenadas;
	coordenadas.x0 = clist_archivos.GetRect().TopLeft().x;
	coordenadas.y0 = clist_archivos.GetRect().TopLeft().y;
	coordenadas.x1 = clist_archivos.GetRect().BottomRight().x;
	coordenadas.y1 = clist_archivos.GetRect().BottomRight().y;
	
	//Condicional para que solo permita arrastrar y soltar dentro del widget esperado (de "archivo(s) donde se realizará la busqueda")
	if(p.x>=coordenadas.x0 && p.y>=coordenadas.y0 && p.x<=coordenadas.x1 && p.y<=coordenadas.y1){
		if(IsDragAndDropSource())
			return;
		if(AcceptFiles(d)) {
			files = GetFiles(d);
			
			//añadiendo archivos a columnList
			for(int i=0;i<files.GetCount();i++){
				clist_archivos.Add(files[i]);
			}
			
			Refresh();
		}
	}
	
	coordenadas.x0 = lbl_ips.GetRect().TopLeft().x;
	coordenadas.y0 = lbl_ips.GetRect().TopLeft().y;
	coordenadas.x1 = lbl_ips.GetRect().BottomRight().x;
	coordenadas.y1 = lbl_ips.GetRect().BottomRight().y;
	
	//Condicional para que solo permita arrastrar y soltar dentro del widget esperado (de "archivo con texto a buscar")
	if(p.x>=coordenadas.x0 && p.y>=coordenadas.y0 && p.x<=coordenadas.x1 && p.y<=coordenadas.y1){
		if(IsDragAndDropSource())
			return;
		
		if(AcceptFiles(d)) {
			
			//añadiendo archivo a variable y mostrando la ruta en el label "lbl_ips"
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
	
	//PromptOK((String)bg_rojo.GetData());
	//SliderCtrl
	
	//Borra datos anteriores del resultado
	tree_resultado.Clear();
	tree_resultado.Set(0,"Resultados");
	progreso.Set(0);
	
	
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
	
	//Refresh()
}


void ProgramaBusqueda::Paint(Draw &w) {
	
	//Pintando el fondo del color escogido
	//miPicture.Background(Color(StrInt(AsString(~bg_rojo)), StrInt(AsString(~bg_verde)), StrInt(AsString(~bg_azul))));
	//Promptbg_rojo.GetData();
}

//retorna nombre de tecla presionada
String GetKeyDescEx(int key){
	String desc = GetKeyDesc(key & ~K_KEYUP);
	if(key & K_KEYUP)
		desc << " UP";
	return desc;
}


void ProgramaBusqueda::configuracionInicialWidgets(){
	//sliders color de fondo
	bg_rojo.MinMax(0,255);
	bg_verde.MinMax(0,255);
	bg_azul.MinMax(0,255);
	
	//configurando propiedades del columnlist
	clist_archivos.Mode(Upp::ColumnList::MODE_COLUMN);
	clist_archivos.ClickKill(false);
	clist_archivos.MultiSelect(true);
	clist_archivos.PopUpEx(false);
	
	//configurando propiedades del tree (Resultado)
	tree_resultado.PopUpEx(false);
	
	//barra de progreso, configuracion inicial
	progreso.SetTotal(100);
	progreso.Set(0);
};

GUI_APP_MAIN
{
	ProgramaBusqueda().Zoomable().Sizeable().Run();
}




































