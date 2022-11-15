#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"
#include "Set4LibInterfaces.hh"

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
  string str;
  LibInterface *Lib_;
  Interp4Command *cmd;

  while (stream >> str)
  {
    map<string, LibInterface *>::iterator iterator = Lib.Lib.find(str);
    cout << "Wczytano polecenie " << str << endl;
    if (iterator == Lib.Lib.end())
    {
      cout << "Nie znaleziono wtyczki " << str << endl;
      return 1;
    }

    Lib_ = iterator->second;
    cmd = Lib_->pCreateCmd();
    cmd->ReadParams(stream);
    cmd->PrintCmd();
    // cmd->ExecCmd();
  }
  delete cmd;
  delete Lib_;
  return 0;
}

int main()
{
  Set4LibInterfaces Lib;
  istringstream stream;
  ExecPreprocesor("polecenia.cmd", stream);
  interpret(stream, Lib);
}
