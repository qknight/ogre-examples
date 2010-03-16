#include "ExampleApplication.h"
#include "CreateSphere.h"
#include "DynamicLines.h"
#include "CreateRing.h"

class TutorialFrameListener : public ExampleFrameListener, public OIS::MouseListener, public OIS::KeyListener
{
public:
    TutorialFrameListener(RenderWindow* win, Camera* cam, SceneManager *sceneMgr)
            : ExampleFrameListener(win, cam, true, true)
    {
        // Populate the camera and scene manager containers
        mCamNode = cam->getParentSceneNode();
        mSceneMgr = sceneMgr;

        // set the rotation and move speed
        mRotate = 0.13;
        mMove = 250;

        // continue rendering
        mContinue = true;

        mMouse->setEventCallback(this);
        mKeyboard->setEventCallback(this);

        mDirection = Vector3::ZERO;

    }

    bool frameStarted(const FrameEvent &evt)
    {
        if (mMouse)
            mMouse->capture();
        if (mKeyboard)
            mKeyboard->capture();
        mCamNode->translate(mDirection * evt.timeSinceLastFrame, Node::TS_LOCAL);

        return mContinue;
    }

    // MouseListener
    bool mouseMoved(const OIS::MouseEvent &e) {
        //if (e.state.buttonDown(OIS::MB_Right))
        {
            mCamNode->yaw(Degree(-mRotate * e.state.X.rel), Node::TS_WORLD);
            mCamNode->pitch(Degree(-mRotate * e.state.Y.rel), Node::TS_LOCAL);
        }

        return true;
    }
    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
        Light *light = mSceneMgr->getLight("Light1");
        switch (id)
        {
        case OIS::MB_Left:
            light->setVisible(! light->isVisible());
            break;
        default:
            break;
        }
        return true;
    }
    bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
        return true;
    }

    // KeyListener
    bool keyPressed(const OIS::KeyEvent &e)
    {
        switch (e.key)
        {
        case OIS::KC_ESCAPE:
            mContinue = false;
            break;
        case OIS::KC_1:
            mCamera->getParentSceneNode()->detachObject(mCamera);
            mCamNode = mSceneMgr->getSceneNode("CamNode1");
            mCamNode->attachObject(mCamera);
            break;

        case OIS::KC_2:
            mCamera->getParentSceneNode()->detachObject(mCamera);
            mCamNode = mSceneMgr->getSceneNode("CamNode2");
            mCamNode->attachObject(mCamera);
            break;
        case OIS::KC_UP:
        case OIS::KC_W:
            mDirection.z = -mMove;
            break;

        case OIS::KC_DOWN:
        case OIS::KC_S:
            mDirection.z = mMove;
            break;

        case OIS::KC_LEFT:
        case OIS::KC_A:
            mDirection.x = -mMove;
            break;

        case OIS::KC_RIGHT:
        case OIS::KC_D:
            mDirection.x = mMove;
            break;

        case OIS::KC_PGDOWN:
        case OIS::KC_E:
            mDirection.y = -mMove;
            break;

        case OIS::KC_PGUP:
        case OIS::KC_Q:
            mDirection.y = mMove;
            break;



        default:
            break;
        }
        return mContinue;
    }

    bool keyReleased(const OIS::KeyEvent &e) {
        switch (e.key)
        {
        case OIS::KC_UP:
        case OIS::KC_W:
            mDirection.z = 0;
            break;

        case OIS::KC_DOWN:
        case OIS::KC_S:
            mDirection.z = 0;
            break;

        case OIS::KC_LEFT:
        case OIS::KC_A:
            mDirection.x = 0;
            break;

        case OIS::KC_RIGHT:
        case OIS::KC_D:
            mDirection.x = 0;
            break;

        case OIS::KC_PGDOWN:
        case OIS::KC_E:
            mDirection.y = 0;
            break;

        case OIS::KC_PGUP:
        case OIS::KC_Q:
            mDirection.y = 0;
            break;

        default:
            break;
        } // switch
        return true;
    }
protected:
    Real mRotate;          // The rotate constant
    Real mMove;            // The movement constant

    SceneManager *mSceneMgr;   // The current SceneManager
    SceneNode *mCamNode;   // The SceneNode the camera is currently attached to

    bool mContinue;        // Whether to continue rendering or not
    Vector3 mDirection;     // Value to move in the correct direction
};

class TutorialApplication : public ExampleApplication
{
public:
    void createCamera(void)
    {
        // create camera, but leave at default position
        mCamera = mSceneMgr->createCamera("PlayerCam");
        mCamera->setNearClipDistance(5);
    }

    void createScene(void)
    {
        mSceneMgr->setAmbientLight(ColourValue(0.25, 0.25, 0.25));

        Entity *ent;
        SceneNode *node;

        // create the light
        Light *light = mSceneMgr->createLight("Light1");
        light->setType(Light::LT_POINT);
        light->setPosition(Vector3(250, 150, 250));
        light->setDiffuseColour(ColourValue::White);
        light->setSpecularColour(ColourValue::White);

        // Create the scene node
        node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode1", Vector3(-400, 200, 400));

        // Make it look towards the ninja
        node->yaw(Degree(-45));

        // Create the pitch node
        node = node->createChildSceneNode("PitchNode1");
        node->attachObject(mCamera);

        // create the second camera node/pitch node
        node = mSceneMgr->getRootSceneNode()->createChildSceneNode("CamNode2", Vector3(0, 200, 400));
        node = node->createChildSceneNode("PitchNode2");

        // this is basically the same code as in the 'ninja-camera-texture' example
        CreateSphere::create("myMarsMesh", 50,64,64);
        Entity *ent_mars = mSceneMgr->createEntity("MARS", "myMarsMesh");
        SceneNode *node_mars = mSceneMgr->getRootSceneNode()->createChildSceneNode("NodeMars");
        node_mars->attachObject(ent_mars);
        node_mars->translate(0, 0, 0);
        ent_mars->setMaterialName("myExamples/myMars");

        //  http://www.ogre3d.org/forums/viewtopic.php?p=304338
        //
        // this is just a little example how to use the DynamicLines
//         DynamicLines *lines = new DynamicLines(RenderOperation::OT_LINE_LIST);
//         lines->addPoint(Vector3(0,-50,-1000));
//         lines->addPoint(Vector3(0,-50,1000));
//
//         lines->addPoint(Vector3(-1000,-50,0));
//         lines->addPoint(Vector3(1000,-50,0));
//         lines->update();
//         SceneNode *linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("lines");
//         linesNode->attachObject(lines);

        // now we are going to create the green rings
        CreateRing::create("ring0", mSceneMgr, Vector3(0,0,0), Vector3(0,1,0), 250, 128);
        CreateRing::create("ring1", mSceneMgr, Vector3(0,0,0), Vector3(0,1,0), 500, 128);
        CreateRing::create("ring2", mSceneMgr, Vector3(0,0,0), Vector3(0,1,0), 750, 128);
        CreateRing::create("ring3", mSceneMgr, Vector3(0,0,0), Vector3(0,1,0), 1000, 128);
        CreateRing::create("ring4", mSceneMgr, Vector3(0,0,0), Vector3(0,1,0), 1250, 128);

        std::vector<std::string> ringnames;
        ringnames.push_back("ring0");
        ringnames.push_back("ring1");
        ringnames.push_back("ring2");
        ringnames.push_back("ring3");
        ringnames.push_back("ring4");

        for (int i=0; i < ringnames.size(); ++i) {
            SceneNode* sn = mSceneMgr->getSceneNode(ringnames[i]);
            if (sn->numAttachedObjects()) {
                MovableObject* mo = sn->getAttachedObject(0);
                DynamicRenderable* r = dynamic_cast<DynamicRenderable*>( mo );
                
                // don't forget to add 'Plugin=Plugin_CgProgramManager.so' to your plugins.cfg
                // if you want to use a cg program
                // but since this is the glsl example you don't need to use the cg extension
                // at all
                // see cg.material vs glsl.material
                r->setMaterial("glsl/glow");

                // this one seems not to work here
//                 r->setMaterial("cg/alpha_glow");

                // works here
//                 r->setMaterial("cg/no_depth_check_glow");
            }
        }
    }

    void createFrameListener(void)
    {
        // Create the FrameListener
        mFrameListener = new TutorialFrameListener(mWindow, mCamera, mSceneMgr);
        mRoot->addFrameListener(mFrameListener);

        // Show the frame stats overlay
        mFrameListener->showDebugOverlay(true);
    }
};

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
    // Create application object
    TutorialApplication app;

    try {
        app.go();
    } catch (Exception& e) {
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n",
                e.getFullDescription().c_str());
#endif
    }

    return 0;
}

