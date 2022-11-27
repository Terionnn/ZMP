#pragma once

#include <map>
#include <string>
#include "MobileObj.hh"
#include "AccessControl.hh"
#include "Configuration.hh"

class Scene : public AccessControl
{
private:
    /*!
     * \brief Prosta kolekcja obiektów sceny
     */
    std::map<std::string, MobileObj> _Container4Objects;

public:
    Scene(Configuration &config);
    MobileObj *FindMobileObj(const char *sName);
    void AddMobileObj(MobileObj *pMobObj);
    std::map<std::string, MobileObj> getMobileObjects() { return _Container4Objects; }
};
