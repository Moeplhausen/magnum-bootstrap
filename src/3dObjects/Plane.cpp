#include "Plane.h"
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Primitives/Plane.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Trade/MeshData3D.h>
namespace EMTypes {

        Plane::Plane(const Magnum::Color3& color, Object3D* parent, SceneGraph::DrawableGroup3D* group): Object3D(parent), SceneGraph::Drawable3D(*this, group),  color(color) {
            ViewerResourceManager& manager = ViewerResourceManager::instance();

            _plane = manager.get<Mesh>("plane");
            if(_plane.state() == ResourceState::NotLoaded || _plane.state() == ResourceState::NotLoadedFallback) {


                Mesh* mesh = new Mesh;
                Trade::MeshData3D data = Primitives::Plane::solid();

                Buffer* _planeVertices=new Buffer(Buffer::TargetHint::Array);
                _planeVertices->setData(MeshTools::interleave(data.positions(0), data.normals(0)), BufferUsage::StaticDraw);
                mesh->setCount(data.positions(0).size())
                        .setPrimitive(data.primitive())
                        .addVertexBuffer(*_planeVertices, 0, Shaders::Phong::Position{}, Shaders::Phong::Normal{});

                manager.set("plane-buffer", _planeVertices, ResourceDataState::Final, ResourcePolicy::Resident)
                        .set(_plane.key(), mesh, ResourceDataState::Final, ResourcePolicy::Resident);


            }


            /* Shader */
            if(!(_shaderPlane = manager.get<Shaders::Phong>("planeShader")))
                manager.set<Shaders::Phong>(_shaderPlane.key(), new Shaders::Phong, ResourceDataState::Final, ResourcePolicy::Resident);

        }

        void Plane::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {

            _shaderPlane->setDiffuseColor(color)
                    .setSpecularColor(Color3(1.0f))
                    .setShininess(80)
                    .setLightPosition({3.0f, -3.0f, 3.0f})
                    .setTransformationMatrix(transformationMatrix)
                    .setNormalMatrix(transformationMatrix.rotationScaling())
                    .setProjectionMatrix(camera.projectionMatrix());

            _plane->draw(*_shaderPlane);
        }


    }
