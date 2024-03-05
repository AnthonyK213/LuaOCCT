#include <luaocct/util_math.h>

#include <cmath>
#include <limits>

namespace luaocct {
namespace util {
namespace Math {

Standard_Boolean EpsilonEquals(Standard_Real theX, Standard_Real theY,
                               Standard_Real theEpsilon) {
  if (std::isnan(theX) || std::isnan(theY))
    return Standard_False;

  if (theX == std::numeric_limits<double>::infinity())
    return theY == std::numeric_limits<double>::infinity();

  if (theX == -std::numeric_limits<double>::infinity())
    return theY == -std::numeric_limits<double>::infinity();

  if (std::abs(theX) < theEpsilon && std::abs(theY) < theEpsilon)
    return std::abs(theX - theY) < theEpsilon;

  if (theX >= theY - theEpsilon)
    return theX <= theY + theEpsilon;

  return Standard_False;
}

} // namespace Math
} // namespace util
} // namespace luaocct
