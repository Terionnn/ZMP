#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH



#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"
#include "dlfcn.h"


class LibInterface {

	void* LibHandler;
	void* pFun;

	public: 
	LibInterface();
	~LibInterface();
	int Load(std::string name);
	Interp4Command* pCmd;
	Interp4Command *(*pCreateCmd)(void);	
	std::string CmdName;

};


#endif
