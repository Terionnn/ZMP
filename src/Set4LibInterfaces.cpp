#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include <memory>
#include <string>
#include <map>
using namespace std;
Set4LibInterfaces::Set4LibInterfaces()
{
 Load("libs/libInterp4Rotate.so");
 Load("libs/libInterp4Pause.so");
 Load("libs/libInterp4Set.so");
 Load("libs/libInterp4Move.so");
}

void Set4LibInterfaces::Load(string sciezka)
{
  shared_ptr Lib =make_shared<LibInterface>();
  Lib->Load(sciezka);
  Library.insert({Lib->CmdName,Lib});
}