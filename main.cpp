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
	CtrlLayout(*this, "Busqueda");
	
	//AddFrame(menu);
	//AddFrame(menu);
	//menu.Set([=](Bar& bar) { MainMenu(bar); });
	//this->AddFrame(menu);
	//menu.Set([=](Bar& bar) { MainMenu(bar); });
	
	//sliders color de fondo
	bg_rojo.MinMax(0,255);
	bg_verde.MinMax(0,255);
	bg_azul.MinMax(0,255);
	
	//barra de progreso, configuracion inicial
	progreso.SetTotal(100);
	progreso.Set(0);
	
	btn_buscar << [=] { buscar(); };
	btn_config << [=] { configuracion(); };
}

void de_prueba_dropWInterfaz::configuracion(){
	PromptOK("asdasd");
	/*
	TabDlg dlg;
	WithConfigTab1Layout<ParentCtrl> tab1;
	WithTab2Layout<ParentCtrl> tab2;
	dlg(tab1, "Tab1")(tab2, "Tab2")
	   .OKCancel()
	   .Title("Tab dialog");
	dlg.Run();*/
}



void de_prueba_dropWInterfaz::DragAndDrop(Point p, PasteClip& d)
{
	//struct para guardar las coordenadas del widget
	coordenadasWidget coordenadas;
	coordenadas.x0 = clist_archivos.GetRect().TopLeft().x;
	coordenadas.y0 = clist_archivos.GetRect().TopLeft().y;
	coordenadas.x1 = clist_archivos.GetRect().BottomRight().x;
	coordenadas.y1 = clist_archivos.GetRect().BottomRight().y;
	
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
	
	//int contador_progreso=0;
	
	//tip TabCtrl
	//busqueda desde archivos de column list
	//PromptOK((String)clist_archivos.GetValue(0));
	
	for(int i=0;i<clist_archivos.GetCount();i++){
		ifstream ifstream_archivo( (clist_archivos.GetValue(i)).ToStd() );
		archivo_resultado<<"["<<(clist_archivos.GetValue(i)).ToStd()<<"]\n";
		
		//progreso.Set(25);
		
		while (getline (ifstream_archivo, str_aux_text)) {
			//104.239.146.23
			if (str_aux_text.find("a") != std::string::npos) {
				archivo_resultado<<str_aux_text<<"\n";
				encontrado=true;
				contador++;
			}
		}
		archivo_resultado<<"\n";
		
		//*******
		//contador_progreso+=1000/clist_archivos.GetCount();
		//contador++;
		//contador_progreso+=25;
		//if(contador_progreso==1000){contador_progreso=0;}
		//progreso.Set(contador_progreso);
		//Refresh();
		
		//contador_progreso+=1;
		//if(contador_progreso==100){contador_progreso=0;}
		//lbl_progreso.SetText((String)to_string(contador_progreso));
		//Refresh();
	}
	progreso.Set(100);
	
	//String asd = clist_archivos.GetValue(0);
	//lbl_mml.SetText(asd);
	
	//busqueda directamente de clipboard
	/*
	for(int i=0;i<files.GetCount();i++){
		
		ifstream ifstream_archivo(files[i]);
		archivo_resultado<<"["<<to_string(files[i])<<"]\n";
		
		//progreso.Set(25);
		
		while (getline (ifstream_archivo, str_aux_text)) {
			//104.239.146.23
			if (str_aux_text.find("1") != std::string::npos) {
				archivo_resultado<<str_aux_text<<"\n";
				encontrado=true;
				contador++;
			}
		}
		archivo_resultado<<"\n";
	}
	*/
	
	
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
	
	//w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)),0,0));//RGB
	//w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)),0,0));//RGB
	w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)), StrInt(AsString(~bg_verde)), StrInt(AsString(~bg_azul))));//RGB
	
	Refresh();

}

GUI_APP_MAIN
{
	de_prueba_dropWInterfaz().Zoomable().Sizeable().Run();
	//de_prueba_dropWInterfaz
}
