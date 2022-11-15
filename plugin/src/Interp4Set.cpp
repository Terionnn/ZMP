#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"
#include "LibInterface.hh"

using std::cout;
using std::endl;

extern "C"
{
  Interp4Command *CreateCmd(void);
  const char *GetCmdName() { return "Set"; }
}

/*!
 * \brief
 *
 *
 */
Interp4Command *CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}

/*!
 *
 */
Interp4Set::Interp4Set() : _Name("A"), _X(10), _Y(10), _OZ(5)
{
}

/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Name << " " << _X << " " << _Y << " " << _OZ << endl;
}

/*!
 *
 */
const char *Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}

/*!
 *
 */
bool Interp4Set::ExecCmd(MobileObj *pMobObj, int Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
  return true;
}

/*!
 *
 */
bool Interp4Set::ReadParams(std::istream &Strm_CmdsList)
{
  Strm_CmdsList >> _Name;
  Strm_CmdsList >> _X;
  Strm_CmdsList >> _Y;
  Strm_CmdsList >> _OZ;

  return true;
}

/*!
 *
 */
Interp4Command *Interp4Set::CreateCmd()
{
  return new Interp4Set();
}

/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  X  Y OZ" << endl;
}
