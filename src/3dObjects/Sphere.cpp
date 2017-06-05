//
// Created by mattis on 01.06.17.
//

#include "Sphere.h"


#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/Primitives/Icosphere.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Trade/MeshData3D.h>
namespace EMTypes {



        Sphere::Sphere(const Vector3& color, Object3D* parent, SceneGraph::DrawableGroup3D* group): Object3D(parent), SceneGraph::Drawable3D(*this, group),  color(color) {
            ViewerResourceManager& manager = ViewerResourceManager::instance();

            /* Cube mesh */
            if(!(_mesh = manager.get<Mesh>("sphere"))) {


                const Trade::MeshData3D data = Primitives::Icosphere::solid(4);
                Buffer* buffer=new Buffer(Buffer::TargetHint::Array);
                buffer->setData(MeshTools::interleave(data.positions(0), data.normals(0)), BufferUsage::StaticDraw);

                Containers::Array<char> indexData;
                Mesh::IndexType indexType;
                UnsignedInt indexStart, indexEnd;
                std::tie(indexData, indexType, indexStart, indexEnd) = MeshTools::compressIndices(data.indices());
                Buffer* indexBuffer=new Buffer(Buffer::TargetHint::ElementArray);
                indexBuffer->setData(indexData, BufferUsage::StaticDraw);
                Mesh* mesh = new Mesh;

                mesh->setPrimitive(data.primitive())
                        .setCount(data.indices().size())
                        .addVertexBuffer(*buffer, 0, Shaders::Phong::Position{}, Shaders::Phong::Normal{})
                        .setIndexBuffer(*indexBuffer, 0, indexType, indexStart, indexEnd);

                manager.set("sphere-buffer", buffer, ResourceDataState::Final, ResourcePolicy::Resident)
                        .set("sphere-index-buffer", indexBuffer, ResourceDataState::Final, ResourcePolicy::Resident)
                        .set(_mesh.key(), mesh, ResourceDataState::Final, ResourcePolicy::Resident);

            }


            /* Shader */
            if(!(_shader = manager.get<Shaders::Phong>("sphereShader")))
                manager.set<Shaders::Phong>(_shader.key(), new Shaders::Phong, ResourceDataState::Final, ResourcePolicy::Resident);

        }

        void Sphere::draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) {
            _shader->setDiffuseColor(color)
                    .setSpecularColor(Color3(1.0f))
                    .setShininess(20)
                    .setLightPosition({3.0f, -3.0f, 3.0f})
                    .setTransformationMatrix(transformationMatrix)
                    .setNormalMatrix(transformationMatrix.rotationScaling())
                    .setProjectionMatrix(camera.projectionMatrix());

            _mesh->draw(*_shader);
        }



}
