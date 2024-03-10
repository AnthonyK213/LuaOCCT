#include <luaocct/LOUtil_Math.hxx>

#include <cmath>
#include <limits>

Standard_Boolean LOUtil_Math::EpsilonEquals(Standard_Real theX,
                                            Standard_Real theY,
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
