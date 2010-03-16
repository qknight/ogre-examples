/*
    see 
    http://www.ogre3d.org/wiki/index.php/ManualSphereMeshes

*/

#ifndef CREATESPHERE_H
#define CREATESPHERE_H

#include <Ogre.h>
#include <OgreMesh.h>
#include <OgreMeshManager.h>
#include <OgreSubMesh.h>

class CreateSphere {
  public: 
  // http://www.exforsys.com/tutorials/c-plus-plus/c-plus-plus-static-functions.html
  static void create(const std::string& strName, const float r, const int nRings = 16, const int nSegments = 16);
};

#endif // CREATESPHERE_H
