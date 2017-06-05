//
// Created by mattis on 22.04.17.
//

#ifndef TRANSTANKS_TYPES_H
#define TRANSTANKS_TYPES_H

#include <Magnum/Magnum.h>
#include <Magnum/SceneGraph/SceneGraph.h>
#include <Magnum/Text/Text.h>


#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/Trade.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Texture.h>
#include <Magnum/Mesh.h>
#include <Magnum/ResourceManager.h>
#include <Magnum/Buffer.h>

namespace EMTypes {
    using namespace Magnum;
/** @brief Base 3D object */
    typedef SceneGraph::Object<SceneGraph::MatrixTransformation3D> Object3D;

/** @brief Base 3D scene */
    typedef SceneGraph::Scene<SceneGraph::MatrixTransformation3D> Scene3D;

    typedef ResourceManager<Buffer, Mesh, Texture2D, Shaders::Phong, Trade::PhongMaterialData> ViewerResourceManager;

}

namespace Magnum{

    /** @brief Resource manager */
    extern template class ResourceManager<Buffer, Mesh, Texture2D, Shaders::Phong, Trade::PhongMaterialData>;

}

#endif //TRANSTANKS_TYPES_H
