#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "LibInterface.hh"
#include "Interp4Command.hh"
#include <memory>


class Set4LibInterfaces
{
public:

   Set4LibInterfaces();
  std::map<std::string, std::shared_ptr<LibInterface>>Library;
  void Load(std::string sciezka);


};