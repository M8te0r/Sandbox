#pragma once
#include "asset_system/mesh/Mesh.h"
namespace Elysian
{
    class Cube : public Mesh
    {
    public:
        Cube();
        Cube(float length, float width, float height);
    };
} // namespace Elysian
