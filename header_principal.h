#ifndef _header_principal_h
#define _header_principal_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#define LAYOUTFILE <Ver_si_existen_IPS/GUI.lay>
#include <CtrlCore/lay.h>


//class ProgramaBusqueda
class de_prueba_dropWInterfaz : public Withde_prueba_dropWInterfazLayout<TopWindow> {
//class de_prueba_dropWInterfaz : public WithVer_si_existen_IPSLayout<TopWindow> {
public:
	
	virtual void DragAndDrop(Point p, PasteClip& d) override;
	virtual void LeftDrag(Point p, dword keyflags) override;
	virtual void Paint(Draw &w) override;
	
	//variable para gestionar archivos de drag & drop
	Vector<String> files;
	
	//mis metodos
	void buscar();
	void configuracion();
	
	//progress
	//mis variables
	std::string archivoMML="";
	
	//archivo resultado
	//ofstream archivo_resultado("resultado_busqueda.txt", std::ios::app);

	//constructor
	de_prueba_dropWInterfaz();

};

#endif
