#ifndef _header_principal_h
#define _header_principal_h

#include <CtrlLib/CtrlLib.h>
#include <Core/Core.h>

using namespace Upp;

#include <fstream>
#include <string>
#include <iostream>

using namespace std;




#define LAYOUTFILE <BusquedaIPs/GUI.lay>
#include <CtrlCore/lay.h>

//Otras Funciones
void guardar_configuracion(int* rojo, int *verde, int *azul){
	ifstream configuracion("config");
	string str_aux_text;
	
	//leyendo primera linea del archivo
	//getline(configuracion,str_aux_text);
	
	/*
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
	}*/
}




//Clase
class ProgramaBusqueda : public Withlayout_principal<TopWindow> {
public:
	
	virtual void DragAndDrop(Point p, PasteClip& d) override;
	virtual void LeftDrag(Point p, dword keyflags) override;
	virtual void Paint(Draw &w) override;
	//virtual void WhenBar() ;
	virtual bool Key(dword key, int count) override;
	
	
	//para manejar submenu al hacer click derecho
	//virtual void RightDown(Point p, dword keyflags) override;
	
	//variable para gestionar archivos de drag & drop (de MMML's)
	Vector<String> files;
	
	//variable para gestionar archivo de ips (mas concretamente, solo para guardar la ruta del mismo)
	Vector<String> files_ips;
	//string archivo_ips;
	
	//mis metodos
	void buscar();
	void configuracion();
	
	
	//progress
	//mis variables
	std::string archivoMML="";
	
	//archivo resultado
	//ofstream archivo_resultado("resultado_busqueda.txt", std::ios::app);

	//constructor
	ProgramaBusqueda();

};

#endif
