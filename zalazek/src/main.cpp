#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <sstream>
#include "Interp4Command.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"

#define name_move "libInterp4Move.so"
#define name_rotate "libInterp4Rotate.so"

#define LINE_SIZE 100

using namespace std;

bool ExecPreprocesor(const char * NazwaPliku, istringstream &IStrm4Cmds )
{
string Cmd4Preproc = "cpp -P";
char Line[LINE_SIZE];
ostringstream OTmpStrm;
Cmd4Preproc += NazwaPliku;
FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

if (!pProc)
{
  return false;
}

while (fgets(Line,LINE_SIZE,pProc)) 
{
  OTmpStrm << Line;
}
IStrm4Cmds.str(OTmpStrm.str());

return pclose(pProc) == 0;
}


int main()
{
  LibInterface move;
  move.Load(name_move);

  LibInterface rotate;
  rotate.Load(name_rotate);

  cout << endl;
  cout << move.CmdName << endl;
  cout << endl;
  move.pCmd->PrintSyntax();
  cout << endl;
  move.pCmd->PrintCmd();
  cout << endl;
  
  
}
