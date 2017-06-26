//
// Created by mattis on 23.06.17.
//

#ifndef EMSCRIPTENISSUES_PLANE_H
#define EMSCRIPTENISSUES_PLANE_H

#include "../Types.h"
#include <Magnum/ResourceManager.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/Shaders/Phong.h>

#include <Magnum/SceneGraph/Drawable.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>


namespace EMTypes {
    class Plane : public Object3D, SceneGraph::Drawable3D {
    public:
        explicit Plane(const Magnum::Color3 &color, Object3D *parent, SceneGraph::DrawableGroup3D *group);

        void draw(const Matrix4 &transformationMatrix, SceneGraph::Camera3D &camera) override;

    private:
        Resource<Shaders::Phong> _shaderPlane;
        Resource<Mesh> _plane;
        Color3 color;
    };
}

#endif //EMSCRIPTENISSUES_PLANE_H
