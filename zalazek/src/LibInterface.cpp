#include "LibInterface.hh"
#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"

using namespace std;

LibInterface::LibInterface(string name)
{
  LibHandler = dlopen(name.c_str(), RTLD_LAZY);

  if (!LibHandler) {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
   
  }


  pFun = dlsym(LibHandler,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
   
  }
  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
 
   pCmd = pCreateCmd();
   
   CmdName=pCmd->GetCmdName();
}

LibInterface::~LibInterface()
{
dlclose(LibHandler);
}
