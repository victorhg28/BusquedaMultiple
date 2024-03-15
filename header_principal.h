#ifndef _header_principal_h
#define _header_principal_h

#include <CtrlLib/CtrlLib.h>
#include <Core/Core.h>

using namespace Upp;

#include <fstream>
#include <string>
#include <iostream>

using namespace std;




#define LAYOUTFILE <BusquedaMultiple/GUI.lay>
#include <CtrlCore/lay.h>


//Clase
class ProgramaBusqueda : public Withlayout_principal<TopWindow> {
public:
	
	virtual void DragAndDrop(Point p, PasteClip& d) override;
	virtual void LeftDrag(Point p, dword keyflags) override;
	virtual void Paint(Draw &w) override;
	virtual bool Key(dword key, int count) override;
	virtual void Close() override;
	
	
	
	//variable para gestionar archivos de drag & drop (de MMML's)
	Vector<String> files;
	
	//variable para gestionar archivo de ips (mas concretamente, solo para guardar la ruta del mismo)
	Vector<String> files_ips;
	
	//mis metodos
	void buscar();
	void configuracion();
	void configuracionInicialWidgets();
	
	
	//mis variables
	//std::string archivoMML="";
	
	void SliderColorFondo();
	

	//constructor
	ProgramaBusqueda();

};

#endif
