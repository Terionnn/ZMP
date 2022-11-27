#include "Scene.hh"
#include <vector>

Scene::Scene(Configuration &config)
{
    std::vector<std::string> names = config.getNames();
    std::vector<Vector3D> scales = config.getScales();
    std::vector<Vector3D> rgb = config.getRgbs();
    std::vector<Vector3D> shift = config.getShift();
    std::vector<Vector3D> rot = config.getRot();
    std::vector<Vector3D> trans = config.getTrans();

    for (int i = 0; i < names.size(); i++)
    {
        MobileObj tmp;
        tmp.SetName(names[i].c_str());
        tmp.SetAng_Roll_deg(rot[i][0]);
        tmp.SetAng_Pitch_deg(rot[i][1]);
        tmp.SetAng_Yaw_deg(rot[i][2]);
        tmp.SetPosition_m(shift[i]);
        tmp.setRgb(rgb[i]);
        tmp.setScale(scales[i]);
        tmp.setTranslation(trans[i]);

        AddMobileObj(&tmp);
        std::cout << "dodano obiekt " << tmp.GetName() << std::endl;
    }
}

MobileObj *Scene::FindMobileObj(const char *sName)
{
    MobileObj *pointer_to_object = NULL;
    std::map<std::string, MobileObj>::iterator iterator = _Container4Objects.find(sName);
    if (iterator == _Container4Objects.end())
    {
        std::cout << "Nie znaleziono wtyczki dla polecenia: " << sName << std::endl;
    }
    pointer_to_object = &(iterator->second);
    return pointer_to_object;
}

void Scene::AddMobileObj(MobileObj *pMobObj)
{
    _Container4Objects.insert(std::make_pair(pMobObj->GetName(), *pMobObj));
}
