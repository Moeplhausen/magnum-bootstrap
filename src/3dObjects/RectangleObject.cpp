//
// Created by mattis on 28.05.17.
//

#include "RectangleObject.h"



#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Trade/MeshData3D.h>
namespace EMTypes {


        RectangleObject::RectangleObject(const Vector3& color, Object3D* parent, SceneGraph::DrawableGroup3D* group): Object3D(parent), SceneGraph::Drawable3D(*this, group),  color(color) {
            ViewerResourceManager& manager = ViewerResourceManager::instance();

            _cube = manager.get<Mesh>("cube");
            if(_cube.state() == ResourceState::NotLoaded || _cube.state() == ResourceState::NotLoadedFallback) {


                const Trade::MeshData3D cubeData = Primitives::Cube::solid();
                Buffer* buffer=new Buffer(Buffer::TargetHint::Array);
                buffer->setData(MeshTools::interleave(cubeData.positions(0), cubeData.normals(0)), BufferUsage::StaticDraw);
                Containers::Array<char> indexData;
                Mesh::IndexType indexType;
                UnsignedInt indexStart, indexEnd;
                std::tie(indexData, indexType, indexStart, indexEnd) = MeshTools::compressIndices(cubeData.indices());
                Buffer* indexBuffer=new Buffer(Buffer::TargetHint::ElementArray);
                indexBuffer->setData(indexData, BufferUsage::StaticDraw);
                Mesh* mesh = new Mesh;

                mesh->setPrimitive(cubeData.primitive())
                        .setCount(cubeData.indices().size())
                        .addVertexBuffer(*buffer, 0, Shaders::Phong::Position{}, Shaders::Phong::Normal{})
                        .setIndexBuffer(*indexBuffer, 0, indexType, indexStart, indexEnd);

                manager.set("cube-buffer", buffer, ResourceDataState::Final, ResourcePolicy::Resident)
                        .set("cube-index-buffer", indexBuffer, ResourceDataState::Final, ResourcePolicy::Resident)
                        .set(_cube.key(), mesh, ResourceDataState::Final, ResourcePolicy::Resident);

            }


            /* Shader */
            if(!(_shaderCube = manager.get<Shaders::Phong>("rectangleShader")))
                manager.set<Shaders::Phong>(_shaderCube.key(), new Shaders::Phong, ResourceDataState::Final, ResourcePolicy::Resident);

        }

        void RectangleObject::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
            _shaderCube->setDiffuseColor(color)
                    .setSpecularColor(Color3(1.0f))
                    .setShininess(20)
                    .setLightPosition({3.0f, -3.0f, 3.0f})
                    .setTransformationMatrix(transformationMatrix)
                    .setNormalMatrix(transformationMatrix.rotationScaling())
                    .setProjectionMatrix(camera.projectionMatrix());

            _cube->draw(*_shaderCube);
        }



}
