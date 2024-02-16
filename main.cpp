#include "header_principal.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//struct para coordenadas de widget
struct coordenadasWidget{
	int x0;
	int y0;
	int x1;
	int y1;
};

//constructor
de_prueba_dropWInterfaz::de_prueba_dropWInterfaz()
{
	CtrlLayout(*this, "Window title");
	
	//sliders color de fondo
	bg_rojo.MinMax(0,255);
	bg_verde.MinMax(0,255);
	bg_azul.MinMax(0,255);
	
	bg_rojo << [=] { Slider(); };
	btn_buscar << [=] { buscar(); };
}

void de_prueba_dropWInterfaz::Slider(){
	
	static_text.SetText(AsString(~bg_rojo));
	
}

void de_prueba_dropWInterfaz::DragAndDrop(Point p, PasteClip& d)
{
	//struct para guardar las coordenadas del widget
	coordenadasWidget coordenadas;
	coordenadas.x0 = label1.GetRect().TopLeft().x;
	coordenadas.y0 = label1.GetRect().TopLeft().y;
	coordenadas.x1 = label1.GetRect().BottomRight().x;
	coordenadas.y1 = label1.GetRect().BottomRight().y;
	
	//if(p.x>=112 && p.y>=24 && p.x<=360 && p.y<=72){
	if(p.x>=coordenadas.x0 && p.y>=coordenadas.y0 && p.x<=coordenadas.x1 && p.y<=coordenadas.y1){
		if(IsDragAndDropSource())
			return;
		if(AcceptFiles(d)) {
			files = GetFiles(d);
			Refresh();
		}
	}
}

void de_prueba_dropWInterfaz::LeftDrag(Point p, dword keyflags)
{
	if(files.GetCount()) {
		VectorMap<String, ClipData> data;
		AppendFiles(data, files);
		DoDragAndDrop(data, Null, DND_COPY);
	}
}


void de_prueba_dropWInterfaz::buscar(){
	
	bool encontrado=false;
	int contador=0; //para mostrar la cantidad de veces que se encontró el resultado
	
	string str_aux_text="";
	
	ofstream archivo_resultado("resultado_busqueda.txt", std::ios::trunc);
	
	int contador_progreso=0;
	
	for(int i=0;i<files.GetCount();i++){
		
		ifstream ifstream_archivo(files[i]);
		archivo_resultado<<"["<<to_string(files[i])<<"]\n";
		
		//progreso.Set(25);
		
		while (getline (ifstream_archivo, str_aux_text)) {
			//104.239.146.23
			if (str_aux_text.find("104.239.146.23") != std::string::npos) {
				archivo_resultado<<str_aux_text<<"\n";
				encontrado=true;
				contador++;
			}
		}
		archivo_resultado<<"\n";
	}
	
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


void de_prueba_dropWInterfaz::Paint(Draw &w) {
	//String
	//cc= color_rgb_Sliders(StrInt(AsString(~bg_rojo)),0,0);
	
	//auto r = GetRect();
	//w.DrawRect(r, color_rgb_Sliders);
	//LAYOUTFILE.changeColor(Color(0,0,0));
	w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)),0,0));//RGB
	Refresh();
	
	for(int i=0;i<files.GetCount();i++){
		//label1.SetText(files[i]);
		//archivoMML = files[i];
		//label1.SetText(files[i]+"\n");
		label1.SetText((String)to_string(files.GetCount())+" archivos cargados");
		
	}

}

GUI_APP_MAIN
{
	de_prueba_dropWInterfaz().Run();
}
