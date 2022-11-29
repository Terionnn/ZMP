#include "Scene.hh"
#include <vector>
using namespace std;
Scene::Scene(Configuration &config)
{
    vector<string> names = config.getNames();
    //cout << names[0];
    vector<Vector3D> scale = config.getScales();
    vector<Vector3D> rgb = config.getRgbs();
    vector<Vector3D> rotation = config.getRotation();
    vector<Vector3D> shift = config.getShift();
    vector<Vector3D> translation = config.getTrans();
    for (int i = 0; i < (int)names.size(); i++)
    {

        MobileObj obj;
        obj.setRgb(rgb[i]);
        obj.SetPosition_m(shift[i]);
        obj.setScale(scale[i]);
        obj.setTranslation(translation[i]);
        obj.SetName(names[i].c_str());
        obj.SetAng_Roll_deg(rotation[i][0]);
        obj.SetAng_Pitch_deg(rotation[i][1]);
        obj.SetAng_Yaw_deg(rotation[i][2]);
        AddMobileObj(&obj);
        cout << "Dodano " << obj.GetName() << endl;
    }
}

void Scene::AddMobileObj(MobileObj *pMobObj)
{
    _Container4Objects.insert(std::make_pair(pMobObj->GetName(), *pMobObj));
}
