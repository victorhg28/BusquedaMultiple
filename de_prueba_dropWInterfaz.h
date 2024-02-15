#ifndef _de_prueba_dropWInterfaz_de_prueba_dropWInterfaz_h
#define _de_prueba_dropWInterfaz_de_prueba_dropWInterfaz_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <Ver_si_existen_IPS/de_prueba_dropWInterfaz.lay>
#include <CtrlCore/lay.h>

class de_prueba_dropWInterfaz : public Withde_prueba_dropWInterfazLayout<TopWindow> {
//class de_prueba_dropWInterfaz : public WithVer_si_existen_IPSLayout<TopWindow> {
public:
	
	virtual void DragAndDrop(Point p, PasteClip& d);
	virtual void LeftDrag(Point p, dword keyflags);
	virtual void Paint(Draw &w);
	Vector<String> files;
	
	void buscar();
	
	std::string archivoMML="";

	de_prueba_dropWInterfaz();
};

#endif
