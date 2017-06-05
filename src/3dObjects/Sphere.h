//
// Created by mattis on 01.06.17.
//

#ifndef TRANSTANKS_SPHERE_H
#define TRANSTANKS_SPHERE_H

#include "../Types.h"
#include <Magnum/ResourceManager.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Shaders/Phong.h>

#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>

namespace EMTypes {



        class Sphere: public Object3D, SceneGraph::Drawable3D {
        public:
            explicit Sphere(const Vector3& color, Object3D* parent, SceneGraph::DrawableGroup3D* group);

            void draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) override;

        private:
            Resource<Shaders::Phong> _shader;
            Resource<Mesh> _mesh;
            Color3 color;
        };


}
#endif //TRANSTANKS_SPHERE_H
