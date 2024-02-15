#include "header_principal.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

de_prueba_dropWInterfaz::de_prueba_dropWInterfaz()
{
	
	CtrlLayout(*this, "Window title");
	
	//sliders color de fondo
	bg_rojo.MinMax(0,255);
	bg_verde.MinMax(0,255);
	bg_azul.MinMax(0,255);
	
	
	
	
	//bg_rojo << THISFN(Slider());
	
	bg_rojo << [=] { Slider(); };
	
	//Slider();
	
	//bg_rojo << THISFN(Slider);
    //slider.Range(700);
    //slider <<= 250;
	
	//this.DrawRect(GetSize(),Color(bg_rojo.GetData(),bg_verde.GetData(),bg_azul.GetData()));
	
	
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

void de_prueba_dropWInterfaz::Slider(){
	//dynarect.SetRectX(50, ~slider);
	//text = "\1[C6*/@b " + AsString(~slider);
	//Color c(~bg_rojo,0,0);
	//colorBG = Color(~bg_rojo,0,0);
	
	static_text.SetText(AsString(~bg_rojo));
	//static_text.SetText((String)bg_rojo.GetData());
	//Upp:Value
	
	//SliderCtrl
	
	//static_text.SetText("asdas");
	
	//Color c;
	//c = Color(0,0,0);
	
	//DrawRect(GetSize(),Color(bg_rojo.GetData(),bg_verde.GetData(),bg_azul.GetData()));
	//return c;
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
			
		
		PromptOK("Resultado Generado");
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
	
	
	
	//Slider();
	
	//Update();
	
	//w.DrawRect(GetSize(),Color(StrInt(AsString(~bg_rojo)),0,0));//RGB
	//w.DrawRect(GetSize(),Color(29,21,34));//RGB
	//w.DrawRect(GetSize(),Color(0,0,0));
	//w.DrawRect(GetSize(),Color(bg_rojo.GetData(),bg_verde.GetData(),bg_azul.GetData()));//RGB
	

	
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
