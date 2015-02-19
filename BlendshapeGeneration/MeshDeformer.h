#pragma once
#include "common.h"
#include "BasicMesh.h"
#include "PointCloud.h"
#include "SparseMatrix.hpp"

struct ICPCorrespondence {
  int tidx;             // triangle index
  double bcoords[3];     // bary-centric coordinates
  double hit[3];         // point on triangle
  double d;
  double weight;         // weight of this point
};

class MeshDeformer
{
public:
  MeshDeformer();
  ~MeshDeformer();
  
  void setSource(const BasicMesh &src) { S = src; }
  void setLandmarks(const vector<int> &lms) { landmarks = lms; }
  BasicMesh deformWithMesh(const BasicMesh &T, const PointCloud &lm_points);
  BasicMesh deformWithPoints(const PointCloud &P, const PointCloud &lm_points);

protected:
  vector<ICPCorrespondence> findClosestPoints_bruteforce(const PointCloud &P, const BasicMesh &mesh);
  ICPCorrespondence findClosestPoint_triangle(double px, double py, double pz,
                                              const double *v0, const double *v1, const double *v2);

private:
  BasicMesh S;
  vector<int> landmarks;
};

