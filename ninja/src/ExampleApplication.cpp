#include "ExampleApplication.h"

class TutorialApplication : public ExampleApplication
{
protected:
public:
    TutorialApplication()
    {
    }

    ~TutorialApplication() 
    {
    }
protected:
    virtual void createCamera(void)
    {
        mCamera = mSceneMgr->createCamera("PlayerCam");
        mCamera->setPosition(Vector3(0,10,500));
        mCamera->lookAt(Vector3(0,0,0));
        mCamera->setNearClipDistance(5);
    }

    virtual void createViewports(void)
    {
        Viewport* vp = mWindow->addViewport(mCamera);
        vp->setBackgroundColour(ColourValue(0,0,0));
        mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));   
    }

    void createScene(void)
    {
        Entity *ent;
        Light *light;

        mSceneMgr->setAmbientLight( ColourValue( 0, 0, 0 ) );
        mSceneMgr->setShadowTechnique( SHADOWTYPE_STENCIL_ADDITIVE );
        
        ent = mSceneMgr->createEntity("Ninja", "ninja.mesh");
        ent->setCastShadows(true);
        mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

        Plane plane(Vector3::UNIT_Y, 0);

        MeshManager::getSingleton().createPlane("ground",
            ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            1500,1500,20,20,true,1,5,5,Vector3::UNIT_Z);

        ent = mSceneMgr->createEntity("GroundEntity", "ground");
        mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

        ent->setMaterialName("Examples/Rockwall");
        ent->setCastShadows(false);

        light = mSceneMgr->createLight("Light1");
        light->setType(Light::LT_POINT);
        light->setPosition(Vector3(0, 150, 250));

        light->setDiffuseColour(1.0, 0.0, 0.0);
        light->setSpecularColour(1.0, 0.0, 0.0);

        light = mSceneMgr->createLight("Light3");
        light->setType(Light::LT_DIRECTIONAL);
        light->setDiffuseColour(ColourValue(.25, .25, 0));
        light->setSpecularColour(ColourValue(.25, .25, 0));

        light->setDirection(Vector3( 0, -1, 1 )); 

        light = mSceneMgr->createLight("Light2");
        light->setType(Light::LT_SPOTLIGHT);
        light->setDiffuseColour(0, 0, 1.0);
        light->setSpecularColour(0, 0, 1.0);

        light->setDirection(-1, -1, 0);
        light->setPosition(Vector3(300, 300, 0));

        light->setSpotlightRange(Degree(35), Degree(50));
    }
};

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char **argv)
#endif
{
    // Create application object
    TutorialApplication app;

    try {
        app.go();
    } catch(Exception& e) {
#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        fprintf(stderr, "An exception has occurred: %s\n",
            e.getFullDescription().c_str());
#endif
    }

    return 0;
}

