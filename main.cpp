#include "de_prueba_dropWInterfaz.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

de_prueba_dropWInterfaz::de_prueba_dropWInterfaz()
{
	CtrlLayout(*this, "Window title");
	
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
		
		//static_text.SetText((String)files[0].ToStd());
		
		string str_aux_text="";
		
		ifstream ifstream_archivo(files[0]);
		
		ofstream archivo_resultado("salida.txt", std::ios::trunc);
		
		while (getline (ifstream_archivo, str_aux_text)) {
		//archivo_resultado << comandoCreacionFiltro(creacionNombreDeFiltro(i_auxNum),  (String)(func_sacar_ip(str_aux_text))     ).ToStd();
			label1.SetText((String)str_aux_text);
			if (str_aux_text=="aaaa"){
				archivo_resultado<<str_aux_text<<"\n";
			}
		}
		
		
		
		//ofstream archivo_resultado(valor, std::ios::trunc);
	
		//archivo_resultado<< "// Filtros ////////////////////////////////////////////////////////";
		//archivo_resultado<<valor;
		
		
		//ifstream ifstream_archivo(files[0].ToStd());
		
		
	}else{
		label1.SetText("*arrastre y suelte el archivo aquí*");
	}
	
	//label1.SetText("despues");
	
}






GUI_APP_MAIN
{
	de_prueba_dropWInterfaz().Run();
}
