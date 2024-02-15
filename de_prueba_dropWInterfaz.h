#ifndef _de_prueba_dropWInterfaz_de_prueba_dropWInterfaz_h
#define _de_prueba_dropWInterfaz_de_prueba_dropWInterfaz_h

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#define LAYOUTFILE <Ver_si_existen_IPS/de_prueba_dropWInterfaz.lay>
#include <CtrlCore/lay.h>

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
	//void Slider();
	void Slider();
	
	//mis variables
	std::string archivoMML="";
	//Color colorBG;
	
	Color cc;
	//	virtual void Paint(Draw& w) override
	//	{
      //                  auto r = GetRect();
		//	w.DrawRect(r, cc);
          //      }
	
	

	//constructor
	de_prueba_dropWInterfaz();
};

#endif
