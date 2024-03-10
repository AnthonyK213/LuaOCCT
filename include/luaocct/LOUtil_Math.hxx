#ifndef _LuaOCCT_LOUtil_Math_HeaderFile
#define _LuaOCCT_LOUtil_Math_HeaderFile

#include <Precision.hxx>

class LOUtil_Math {
public:
  Standard_EXPORT static Standard_Boolean
  EpsilonEquals(Standard_Real theX, Standard_Real theY,
                Standard_Real theEpsilon = Precision::Confusion());
};

#endif
