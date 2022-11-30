#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Sender.hh"
#include "Scene.hh"
#include "Reader.hh"

using namespace std;

int main()
{
  Set4LibInterfaces Lib;
  istringstream stream;
  Configuration config;
  Reader reader;

  reader.execPreprocesor("polecenia.cmd", stream);
  reader.interpret(stream, Lib);
  reader.ReadFile("config/config.xml", config);
  

  Scene scene(config);
  Sender sender(&scene);
  sender.OpenConnection();

  const char *sConfigCmds =
      "Clear\n"
      "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
      "AddObj Name=Podstawa1.Ramie1 RGB=(100,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
      "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"
      "AddObj Name=Podstawa2 RGB=(20,200,10) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
      "AddObj Name=Podstawa2.Ramie1 RGB=(100,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
      "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,240,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";

  sender.Send(sConfigCmds);
  shared_ptr<LibInterface> tmpLib;

  map<string, MobileObj>::iterator iterator = scene._Container4Objects.begin();
  //tmpLib = iterator->second;
  //string str = scene.Send(tmpLib, "AddObj");
  const char* cst = str.c_str();
  sender.Send(cst);
  sender.Send("Close\n");

}      

