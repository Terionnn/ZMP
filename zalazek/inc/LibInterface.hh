#ifndef LIBINTERFACE_HH
#define LIBINTERFACE_HH



#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"
#include "dlfcn.h"


class LibInterface {

	public: 
	LibInterface(std::string name);
	~LibInterface();
	void* LibHandler;
	void* pFun;
	Interp4Command* pCmd;
	std::string CmdName;
	Interp4Command *(*pCreateCmd)(void);	
};


#endif
