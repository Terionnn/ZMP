#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"



class Set4LibInterfaces
{

public:
Set4LibInterfaces();
  std::map<std::string, LibInterface *> Library;
  LibInterface *move = new LibInterface();
  LibInterface *rotate = new LibInterface();
  LibInterface *set = new LibInterface();
  LibInterface *pause = new LibInterface();

};