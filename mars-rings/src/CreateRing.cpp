//
// (c) by Joachim Schiele
//     all code in this file is public domain!
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "CreateRing.h"

//      strName: the name of the object (WARNING: name must be unique)
//    mSceneMgr: the scene you want to circle be added to
//       origin: is the source point, the center of the circle
//           up: used for orientation, since the circle is drawn on a plane, up is the orthogonal vector to that plane
//               (WARNING: must not be 0,0,0)
//       radius: how big the circle should be
//               (WARNING: must not be 0)
// samplePoints: how many line semgments are used to approximate the circle, the more the merrier ;-)

void CreateRing::create(const std::string& strName,  SceneManager *mSceneMgr, Vector3 origin, Vector3 up,
                        unsigned int radius, unsigned int samplePoints) {
    DynamicLines *lines = new DynamicLines(RenderOperation::OT_LINE_STRIP);
    // 0. finding an orthogonal Vector3 to 'up'
//     std::cout << " UP: " << up << std::endl;
    Vector3 orthoToUp;
    // thanks very much to Christian Reitwiessner (reitwiessner.de) for the next 4 lines of code!
    if (up.x / up.length() < 0.5) {
        orthoToUp=Vector3(0, up.z, -up.y);
    } else {
        orthoToUp=Vector3(-up.z, 0, up.x);
    }
//         std::cout << orthoToUp.normalisedCopy()<< std::endl;
//         exit(0);
    // 1. n_orthoToUp := norm(orthoToUp)
    Vector3 n_orthoToUp = orthoToUp.normalisedCopy();
    // 2. expand n_orthoToUp by the radius setting
    n_orthoToUp *= radius;
    // 3. find out the rotation angle per step
    float angle = (float)360/samplePoints;
//     std::cout << "rotation by: " << angle << " with " << samplePoints << " sample points";
    Vector3 renderedPoint = n_orthoToUp;
    lines->addPoint(renderedPoint+origin);
    // 5. create the rotation matrix q which rotates by 'angle' degrees, see
    //   http://www.ogre3d.org/wiki/index.php/Quaternion_and_Rotation_Primer
    Quaternion q(Degree(angle), up.normalisedCopy());
    for (int i=0; i < samplePoints; ++i) {
        // 6.   finally sample all points
        renderedPoint = q * renderedPoint;
//         std::cout << renderedPoint << std::endl;
        lines->addPoint(renderedPoint+origin);
    }
    lines->update();
    SceneNode *linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(strName);
    linesNode->attachObject(lines);
}
