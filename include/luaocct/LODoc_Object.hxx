#ifndef _LuaOCCT_LODoc_Obejct_HeaderFile
#define _LuaOCCT_LODoc_Obejct_HeaderFile

#include <AIS_InteractiveObject.hxx>
#include <TDF_Label.hxx>

using LODoc_Object = AIS_InteractiveObject;
using LODoc_ObjectList = std::vector<Handle(LODoc_Object)>;
using LODoc_Id = TDF_Label;
using LODoc_IdList = std::vector<TDF_Label>;

#endif
