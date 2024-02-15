#include "de_prueba_dropWInterfaz.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

de_prueba_dropWInterfaz::de_prueba_dropWInterfaz()
{
	
	CtrlLayout(*this, "Window title");
	
	btn_buscar << [=] { buscar(); };
	
	//ofstream archivo_resultado("script_generado.txt", std::ios::trunc);
	
	//archivo_resultado<< "// Filtros ////////////////////////////////////////////////////////";
	//archivo_resultado<< "\n";
	
	/*
	if(files.GetCount()){
		//w.DrawText(2, 2 * Draw::GetStdFontCy(), files[0]);
		label1.SetText(files[0]);
	}
	*/
	//label1.SetText("asdasd");
}


void de_prueba_dropWInterfaz::DragAndDrop(Point p, PasteClip& d)
{
	if(IsDragAndDropSource())
		return;
	if(AcceptFiles(d)) {
		files = GetFiles(d);
		Refresh();
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
	string str_aux_text="";
		
	ifstream ifstream_archivo(archivoMML);
		
	ofstream archivo_resultado("resultado_busqueda.txt", std::ios::trunc);
		
	while (getline (ifstream_archivo, str_aux_text)) {
			//label1.SetText((String)str_aux_text);
			
			if (str_aux_text.find("aaaa") != std::string::npos) {
				//std::cout << "found!" << '\n';
				archivo_resultado<<str_aux_text<<"\n";
			}
			
			
			//logica para encontrar texto exacto
			//if (str_aux_text=="aaaa"){
			//	archivo_resultado<<str_aux_text<<"\n";
			//}
		}
		
		
		
		//ofstream archivo_resultado(valor, std::ios::trunc);
	
		//archivo_resultado<< "// Filtros ////////////////////////////////////////////////////////";
		//archivo_resultado<<valor;
		
		
		//ifstream ifstream_archivo(files[0].ToStd());
		
		PromptOK("Resultado Generado");
}


void de_prueba_dropWInterfaz::Paint(Draw &w)
{
	/*
	w.DrawText(2, 2, "None");
	if(files.GetCount()){
		w.DrawText(2, 2 * Draw::GetStdFontCy(), files[0]);
	}
	*/
	//label1.SetText("antes");
	
	
	
	
	
	
	if(files.GetCount()){
		//w.DrawText(2, 2 * Draw::GetStdFontCy(), files[0]);
		label1.SetText(files[0]);
		archivoMML = files[0];
		
		//static_text.SetText((String)files[0].ToStd());
		
	}else{
		label1.SetText("*arrastre y suelte el archivo aquí*");
	}
	
	//label1.SetText("despues");
	
}






GUI_APP_MAIN
{
	de_prueba_dropWInterfaz().Run();
}
