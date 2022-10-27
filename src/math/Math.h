#pragma once

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"

#include <math.h>

namespace Math
{
  inline float toRadians(float degrees)
  {
    return degrees * (M_PI / 180);
  }
}