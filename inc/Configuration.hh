#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <string>
#include "Vector3D.hh"

class Configuration
{

private:
  std::vector<std::string> libraries;
  std::vector<std::string> names;
  std::vector<Vector3D> rgb;
  std::vector<Vector3D> scale;
  std::vector<Vector3D> shift;
  std::vector<Vector3D> translation;
  std::vector<Vector3D> rotation;

public:
  void addLibrary(std::string name)
  {
    libraries.push_back(name);
  };
  void addName(std::string name)
  {
    names.push_back(name);
  };
  void addRgb(Vector3D rgb2)
  {
    rgb.push_back(rgb2);
  };
  void addShift(Vector3D shift2)
  {
    shift.push_back(shift2);
  };
  void addScale(Vector3D scale2)
  {
    scale.push_back(scale2);
  };
  void addRot(Vector3D rotation2)
  {
    rotation.push_back(rotation2);
  };
  void addTrans(Vector3D translation2)
  {
    translation.push_back(translation2);
  };
  std::vector<std::string> getLibraries()
  {
    return libraries;
  };
  std::vector<std::string> getNames()
  {
    return names;
  };
  std::vector<Vector3D> getScales()
  {
    return scale;
  };
  std::vector<Vector3D> getShift()
  {
    return shift;
  };
  std::vector<Vector3D> getRgbs()
  {
    return rgb;
  };
  std::vector<Vector3D> getTrans()
  {
    return translation;
  };
  std::vector<Vector3D> getRotation()
  {
    return rotation;
  };
};

#endif
