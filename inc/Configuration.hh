#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include <vector>
#include <string>
#include "Vector3D.hh"


class Configuration {
  
  private:
  std::vector<std::string> libraries_vector;
  std::vector<std::string> object_names_vector;
  std::vector<Vector3D> object_scales_vector;
  std::vector<Vector3D> object_rgbs_vector;
  std::vector<Vector3D> object_shift_vector;
  std::vector<Vector3D> object_rot_vector;
  std::vector<Vector3D> object_trans_vector;

public:
  void addLibrary(std::string name) { libraries_vector.push_back(name); };
  void addName(std::string name) { object_names_vector.push_back(name); };
  void addScale(Vector3D scale) { object_scales_vector.push_back(scale); };
  void addRgb(Vector3D rgb) { object_rgbs_vector.push_back(rgb); };
  void addShift(Vector3D shift) { object_shift_vector.push_back(shift); };
  void addRot(Vector3D rot) { object_rot_vector.push_back(rot); };
  void addTrans(Vector3D trans) { object_trans_vector.push_back(trans); };
  std::vector<std::string> getLibraries() { return libraries_vector; };
  std::vector<std::string> getNames() { return object_names_vector; };
  std::vector<Vector3D> getScales() { return object_scales_vector; };
  std::vector<Vector3D> getRgbs() { return object_rgbs_vector; };
  std::vector<Vector3D> getShift() { return object_shift_vector; };
  std::vector<Vector3D> getRot() { return object_rot_vector; };
  std::vector<Vector3D> getTrans() { return object_trans_vector; };
  
};


#endif
