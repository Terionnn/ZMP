#include "Reader.hh"

using namespace std;

bool Reader::execPreprocesor(std::string cmdFile, std::istringstream &IStrm4Cmds)
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINE_SIZE];
    std::ostringstream OTmpStrm;
    Cmd4Preproc += cmdFile;
    FILE *pProc = popen(Cmd4Preproc.c_str(), "r");

    if (!pProc)
        return false;

    while (fgets(Line, LINE_SIZE, pProc))
    {
        OTmpStrm << Line;
    }

    IStrm4Cmds.str(OTmpStrm.str());
    return pclose(pProc) == 0;
}


bool Reader::ReadFile(const char *sFileName, Configuration &rConfig)
{
    try
    {
        xercesc::XMLPlatformUtils::Initialize();
    }
    catch (const xercesc::XMLException &toCatch)
    {
        char *message = xercesc::XMLString::transcode(toCatch.getMessage());
        std::cerr << "Error during initialization! :\n";
        std::cerr << "Exception message is: \n"
                  << message << "\n";
        xercesc::XMLString::release(&message);
        return 1;
    }

    xercesc::SAX2XMLReader *pParser = xercesc::XMLReaderFactory::createXMLReader();

    pParser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
    pParser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
    pParser->setFeature(xercesc::XMLUni::fgXercesDynamic, false);
    pParser->setFeature(xercesc::XMLUni::fgXercesSchema, true);
    pParser->setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking, true);

    pParser->setFeature(xercesc::XMLUni::fgXercesValidationErrorAsFatal, true);

    xercesc::DefaultHandler *pHandler = new XMLInterp4Config(rConfig);
    pParser->setContentHandler(pHandler);
    pParser->setErrorHandler(pHandler);

    try
    {

        if (!pParser->loadGrammar("config/config.xsd",
                                  xercesc::Grammar::SchemaGrammarType, true))
        {
            std::cerr << "!!! Plik grammar/actions.xsd, '" << std::endl
                      << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
                      << std::endl;
            return false;
        }
        pParser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse, true);
        pParser->parse(sFileName);
    }
    catch (const xercesc::XMLException &Exception)
    {
        char *sMessage = xercesc::XMLString::transcode(Exception.getMessage());
        std::cerr << "Informacja o wyjatku: \n"
                  << "   " << sMessage << "\n";
        xercesc::XMLString::release(&sMessage);
        return false;
    }
    catch (const xercesc::SAXParseException &Exception)
    {
        char *sMessage = xercesc::XMLString::transcode(Exception.getMessage());
        char *sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

        std::cerr << "Blad! " << std::endl
                  << " Plik:  " << sSystemId << std::endl
                  << " Linia: " << Exception.getLineNumber() << std::endl
                  << " Kolumna: " << Exception.getColumnNumber() << std::endl
                  << " Informacja: " << sMessage
                  << std::endl;

        xercesc::XMLString::release(&sMessage);
        xercesc::XMLString::release(&sSystemId);
        return false;
    }
    catch (...)
    {
        std::cout << "Zgloszony zostal nieoczekiwany wyjatek!\n";
        return false;
    }

    delete pParser;
    delete pHandler;
    return true;
}

bool Reader::interpret(istringstream &stream, Set4LibInterfaces Lib)
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

        if (!command->ReadParams(stream))
        {
            cout << "Wystapil blad podczas wczytywania danych" << endl;
            return 1;
        }
        command->PrintCmd();
        // command->ExecCmd();
    }
    delete command;
    return 0;
}