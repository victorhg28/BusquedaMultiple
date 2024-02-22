#include "header_principal.h"

#include <iostream>
#include <fstream>
#include <string>

#define IMAGECLASS IconoPrograma
#define  IMAGEFILE <BusquedaIPs/icono_principal.iml>
#include <Draw/iml.h>

using namespace std;

String GetKeyDescEx(int key){
	
	String desc = GetKeyDesc(key & ~K_KEYUP);
	if(key & K_KEYUP)
		desc << " UP";
	return desc;
	
	//return "tecla presionada";
}

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
			clist_archivos.Remove(clist_archivos.GetCursor());
		}
	}
	return false;
}

//constructor
ProgramaBusqueda::ProgramaBusqueda()
{
	CtrlLayout(*this, "Busqueda");
	
	Icon(IconoPrograma::mi_icono());//icono del programa
	
	clist_archivos.Mode(Upp::ColumnList::MODE_COLUMN);
	
	
	//Event<> ev1;
	
	//tree_resultado.WhenOpen = THISFN(InicioTree);
	
	
	//AddFrame(menu);
	//AddFrame(menu);
	//menu.Set([=](Bar& bar) { MainMenu(bar); });
	//this->AddFrame(menu);
	//menu.Set([=](Bar& bar) { MainMenu(bar); });
	
	//sliders color de fondo
	//bg_rojo.MinMax(0,255);
	//bg_verde.MinMax(0,255);
	//bg_azul.MinMax(0,255);
	
	//barra de progreso, configuracion inicial
	progreso.SetTotal(100);
	progreso.Set(0);
	
	//ColumnList
	//clist_archivos.Mode(Upp::ColumnList::MODE_COLUMN);
	//clist_archivos.RightDown(Point(12,12), "asdad");
	
	
	
	btn_buscar << [=] { buscar(); };
	//clist_archivos.WhenBar() << [=] { buscar(); };
	//Event
	//PromptOK((String)clist_archivos.WhenBar);
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
	if(files.GetCount()) {
		VectorMap<String, ClipData> data;
		AppendFiles(data, files);
		DoDragAndDrop(data, Null, DND_COPY);
	}
}


void ProgramaBusqueda::buscar(){
	
	if(clist_archivos.GetCount()!=0){
		
		bool encontrado=false; //cambia a true cuando se encuentra por lo menos en alguna linea de texto de los archivos cargados
		int contador=0; //para mostrar la cantidad de veces que se encontró el resultado
		
		string str_aux_text=""; // variable temporal para usar en la lectura de lineas de los archivos de texto cargados
		
		string str_aux_text_ips="";
		
		ofstream archivo_resultado("resultado_busqueda.txt", std::ios::trunc);
		
		for(int i=0;i<clist_archivos.GetCount();i++){
			ifstream ifstream_archivo( (clist_archivos.GetValue(i)).ToStd() );
			archivo_resultado<<"["<<(clist_archivos.GetValue(i)).ToStd()<<"]\n";
			
			
			int x = tree_resultado.Add(0, Null, clist_archivos.GetValue(i));
			
			
			ifstream ifstream_archivoIPs( ( files_ips[0] ).ToStd() );
			
			
			String aux_1;
			
			//tree_resultado.Add(0,aux_1);
			//tree_resultado.Add(,"asd");
			
			
			//tree_resultado.Add(0,Node());
			
			/* primera version de lectura
			while (getline (ifstream_archivo, str_aux_text)) {
				//104.239.146.23
				if (str_aux_text.find("a") != std::string::npos) {
					archivo_resultado<<str_aux_text<<"\n";
					encontrado=true;
					contador++;
				}
			}
			archivo_resultado<<"\n";
			*/
			
			
			//lectura de cada linea de texto del archivo de IP's para cada uno de los archivos
			//cargados
			while (getline (ifstream_archivoIPs, str_aux_text_ips)) {
				while (getline (ifstream_archivo, str_aux_text)) {
					
					if (str_aux_text.find(str_aux_text_ips) != std::string::npos) {
						archivo_resultado<<str_aux_text<<"\n";
						encontrado=true;
						contador++;
					}
				}
				archivo_resultado<<"\n";
			}
			
		}
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
	
	w.DrawRect(GetSize(),SColorPaper);
	Refresh();

}

GUI_APP_MAIN
{
	ProgramaBusqueda().Zoomable().Sizeable().Run();
}
