#ifndef _header_principal_h
#define _header_principal_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#define LAYOUTFILE <BusquedaIPs/GUI.lay>
#include <CtrlCore/lay.h>

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
