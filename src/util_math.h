#ifndef _LuaOCCT_util_math_HeaderFile
#define _LuaOCCT_util_math_HeaderFile

#include <Precision.hxx>

namespace luaocct {
namespace util {
namespace Math {

Standard_EXPORT Standard_Boolean
EpsilonEquals(Standard_Real theX, Standard_Real theY,
              Standard_Real theEpsilon = Precision::Confusion());

} // namespace Math
} // namespace util
} // namespace luaocct

#endif
