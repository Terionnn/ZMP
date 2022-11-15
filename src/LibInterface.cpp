#include "LibInterface.hh"
#include <string>
#include "Vector3D.hh"
#include "geomVector.hh"
#include "MobileObj.hh"
#include "Interp4Command.hh"

using namespace std;

int LibInterface::Load(string name)
{
  LibHandler = dlopen(name.c_str(), RTLD_LAZY);

  if (!LibHandler)
  {
    cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
    return 1;
  }

  pFun = dlsym(LibHandler, "CreateCmd");
  if (!pFun)
  {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
    return 1;
  }
  pCreateCmd = *reinterpret_cast<Interp4Command *(**)(void)>(&pFun);

  pCmd = pCreateCmd();

  CmdName = pCmd->GetCmdName();
}

LibInterface::LibInterface()
{
}

LibInterface::~LibInterface()
{
  dlclose(LibHandler);
}
