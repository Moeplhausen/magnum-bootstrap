#include <Corrade/PluginManager/Manager.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/SceneGraph/Camera.h>
#include "Types.h"

#include "3dObjects/RectangleObject.h"
#include "3dObjects/Sphere.h"
#include "3dObjects/Plane.h"


#include <Magnum/Trade/AbstractImporter.h>
#include "configure.h"
#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Text/GlyphCache.h>

using namespace Magnum;
using namespace EMTypes;


#ifdef MAGNUM_BUILD_STATIC
/* Import plugins in static build */
static int importStaticPlugins() {
    CORRADE_PLUGIN_IMPORT(StbTrueTypeFont)
    return 0;
} CORRADE_AUTOMATIC_INITIALIZER(importStaticPlugins)
#endif


class MyApplication: public Platform::Application {
    public:
        explicit MyApplication(const Arguments& arguments);

    private:
    ViewerResourceManager _resourceManager;

    SceneGraph::Camera3D* _camera;

    Matrix4 _cameraTransformation;
    Object3D *_rootobj, *_cameraObject;

    Scene3D _scene;
    SceneGraph::DrawableGroup3D _drawables;




    void drawEvent() override;
};

MyApplication::MyApplication(const Arguments& arguments): Platform::Application{arguments}
                                   {






    /* Camera setup */
    Matrix4 projectionMatrix = Matrix4::perspectiveProjection(35.0_degf, 1.333f, 0.001f, 3000.0f);
    //Matrix4 projectionMatrix = Matrix4::orthographicProjection({4.0f,3.0f}, 3.0f, 100.0f);
    (_cameraObject = new Object3D(&_scene));

    _cameraTransformation = Matrix4::translation({0, 0, 80.0f});
    _cameraObject->setTransformation(_cameraTransformation);


    (_camera = new SceneGraph::Camera3D(*_cameraObject))
            ->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
            .setProjectionMatrix(projectionMatrix)
            .setViewport(defaultFramebuffer.viewport().size());
    Renderer::enable(Renderer::Feature::DepthTest);
    Renderer::enable(Renderer::Feature::FaceCulling);


    _rootobj=new Object3D(&_scene);

    _rootobj->translate(Vector3::yAxis(-1.0f))
            .setTransformation(Matrix4::rotationX(-10.0_degf));

    Matrix4 transformationMatrix1 = Matrix4::translation({-2, 0, 0});
    Matrix4 transformationMatrix2 = Matrix4::translation({2, 0, 0});


    (new RectangleObject({0.0f, 0.0f, 1.0f}, _rootobj, &_drawables))->setTransformation(transformationMatrix1);
    //(new Sphere({1.0f, 0.0f, 0.0f}, _rootobj, &_drawables))->setTransformation(transformationMatrix2);
    (new Plane({1.0f, 0.0f, 0.0f}, _rootobj, &_drawables))->setTransformation(transformationMatrix2);


}

void MyApplication::drawEvent() {
    defaultFramebuffer.clear(FramebufferClear::Color | FramebufferClear::Depth);

    _cameraObject->setTransformation(_cameraTransformation);

    _camera->draw(_drawables);
    swapBuffers();
    redraw();
}

MAGNUM_APPLICATION_MAIN(MyApplication)
