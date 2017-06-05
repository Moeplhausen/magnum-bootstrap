//
// Created by mattis on 28.05.17.
//

#ifndef TRANSTANKS_RECTANGLEOBJECT_H
#define TRANSTANKS_RECTANGLEOBJECT_H

#include "../Types.h"
#include <Magnum/ResourceManager.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Shaders/Phong.h>

#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>

namespace EMTypes {



        class RectangleObject: public Object3D, SceneGraph::Drawable3D {
        public:
            explicit RectangleObject(const Vector3& color, Object3D* parent, SceneGraph::DrawableGroup3D* group);

            void draw(const Matrix4& transformationMatrix, SceneGraph::Camera3D& camera) override;

        private:
            Resource<Shaders::Phong> _shaderCube;
            Resource<Mesh> _cube;
            Color3 color;
        };


}
#endif //TRANSTANKS_RECTANGLEOBJECT_H
