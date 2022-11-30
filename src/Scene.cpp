#include "Scene.hh"
#include <vector>
using namespace std;
Scene::Scene(Configuration &config)
{
    vector<string> names = config.getNames();

    vector<Vector3D> scale = config.getScales();
    vector<Vector3D> rgb = config.getRgbs();
    vector<Vector3D> rotation = config.getRotation();
    vector<Vector3D> shift = config.getShift();
    vector<Vector3D> translation = config.getTrans();
    for (int i = 0; i < (int)names.size(); i++)
    {
        cout << "ok";
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

string Scene::Send(MobileObj obj, std::string mode)
{
    string name = obj.GetName();
    Vector3D scale = obj.scale;
    Vector3D translation = obj.translation;
    Vector3D rgb = obj.rgb;
    Vector3D shift = obj.GetPositoin_m();
    string sh = "(" + to_string(shift[0]) + "," + to_string(shift[1]) + "," + to_string(shift[2]) + ")";
    string sc = "(" + to_string(scale[0]) + "," + to_string(scale[1]) + "," + to_string(scale[2]) + ")";
    string rot = "(" + to_string(obj.GetAng_Roll_deg()) + "," + to_string(obj.GetAng_Pitch_deg()) + "," + to_string(obj.GetAng_Yaw_deg()) + ")";
    string tr= "(" + to_string(translation[0]) + "," + to_string(translation[1]) + "," + to_string(translation[2]) + ")";
    string rgb_ = "(" + to_string(rgb[0]) + "," + to_string(rgb[1]) + "," + to_string(rgb[2]) + ")";

    string all = mode + " Name=" + name + " Shift=" + sh + " Scale" + sc + " RotXYZ_deg=" + rot + " Trans_m=" + tr + " RGB=" + rgb_ + "\n";
return all;
}
