#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"
#include "Sender.hh"
#include "Scene.hh"
#include "Reader.hh"


#define name_move "libInterp4Move.so"
#define name_rotate "libInterp4Rotate.so"
#define name_pause "libInterp4Pause.so"
#define name_set "libInterp4Set.so"

#define LINE_SIZE 100

using namespace std;

bool ExecPreprocesor(const char *NazwaPliku, istringstream &IStrm4Cmds)
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINE_SIZE];
  ostringstream OTmpStrm;
  Cmd4Preproc += NazwaPliku;
  FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

  if (!pProc)
  {
    return false;
  }

  while (fgets(Line, LINE_SIZE, pProc))
  {
    OTmpStrm << Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());

  return pclose(pProc) == 0;
}

bool interpret(istringstream &stream, Set4LibInterfaces Lib)
{
  shared_ptr<LibInterface> tmpLib;
  Interp4Command *command;
  string tmp;

  while (stream >> tmp)
  {
    map<string, shared_ptr<LibInterface>>::iterator iterator = Lib.Library.find(tmp);
    cout << "Wczytano polecenie " << tmp << endl;
    if (iterator == Lib.Library.end())
    {
      cout << "Nie znaleziono wtyczki " << tmp << endl;
      return 1;
    }
    tmpLib = iterator->second;

    command = tmpLib->pCreateCmd();
    
    if(!command->ReadParams(stream)){
    cout << "Wystapil blad podczas wczytywania danych" <<  endl;
    return 1;
    }
    command->PrintCmd();
    // command->ExecCmd();
  }
  delete command;
    return 0;
}

int main()
{
  Configuration Config;
  Reader reader;
  Set4LibInterfaces Lib;
  istringstream stream;
  reader.init("polecenia.cmd");
  reader.execPreprocesor(stream);
  interpret(stream, Lib);

  reader.ReadFile("config/config.xml", Config);
  Scene scene(Config);
  Sender sender(&scene);
  sender.OpenConnection();
  
   const char *sConfigCmds =
      "Clear\n"
      "AddObj Name=Podstawa1 RGB=(20,200,200) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,20) Trans_m=(-1,3,0)\n"
      "AddObj Name=Podstawa1.Ramie1 RGB=(100,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
      "AddObj Name=Podstawa1.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n"
      "AddObj Name=Podstawa2 RGB=(20,200,10) Scale=(4,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(-1,-3,0)\n"
      "AddObj Name=Podstawa2.Ramie1 RGB=(100,0,0) Scale=(3,3,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(4,0,0)\n"
      "AddObj Name=Podstawa2.Ramie1.Ramie2 RGB=(100,200,0) Scale=(2,2,1) Shift=(0.5,0,0) RotXYZ_deg=(0,-45,0) Trans_m=(3,0,0)\n";

  sender.Send(sConfigCmds);
  sender.Send("Close\n");

}
