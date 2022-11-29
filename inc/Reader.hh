#pragma once

#include <cstdio>
#include <sstream>
#include <string>
#include <iostream>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Configuration.hh"
#include "xmlinterp.hh"

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "Set4LibInterfaces.hh"
#include "Interp4Command.hh"
#include <memory>

#define LINE_SIZE 500

class Reader
{
public:
    
    bool execPreprocesor(std::string cmdFile, std::istringstream &IStrm4Cmds);
    bool ReadFile(const char* sFileName, Configuration &rConfig);
    bool interpret(std::istringstream &stream, Set4LibInterfaces Lib);
};
