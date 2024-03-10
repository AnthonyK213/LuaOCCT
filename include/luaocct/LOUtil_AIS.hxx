#ifndef _LuaOCCT_LOUtil_AIS_HeaderFile
#define _LuaOCCT_LOUtil_AIS_HeaderFile

#include <AIS_InteractiveContext.hxx>
#include <AIS_InteractiveObject.hxx>

#include <vector>

class LOUtil_AIS {
public:
  Standard_EXPORT static std::vector<Handle(AIS_InteractiveObject)>
  GetSelections(const Handle(AIS_InteractiveContext) & theCtx);
};

#endif
