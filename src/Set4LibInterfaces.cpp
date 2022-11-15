#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"

#include <string>
#include <map>
using namespace std;
Set4LibInterfaces::Set4LibInterfaces()
{

  rotate->Load("libs/libInterp4Rotate.so");
  pause->Load("libs/libInterp4Pause.so");
  set->Load("libs/libInterp4Set.so");
  move->Load("libs/libInterp4Move.so");

  Library.insert(make_pair("Rotate", rotate));
  Library.insert(make_pair("Pause", pause));
  Library.insert(make_pair("Set", set));
  Library.insert(make_pair("Move", move));
}