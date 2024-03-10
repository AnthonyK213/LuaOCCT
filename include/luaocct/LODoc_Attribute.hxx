#ifndef _LuaOCCT_LODoc_Attribute_HeaderFile
#define _LuaOCCT_LODoc_Attribute_HeaderFile

#include <TPrsStd_AISPresentation.hxx>
#include <TopLoc_Location.hxx>

#include "LODoc_Object.hxx"

class LODoc_Attribute {
public:
  Standard_EXPORT static LODoc_Id GetId(const Handle(LODoc_Object) & theObj);

  Standard_EXPORT static TCollection_ExtendedString
  GetName(const LODoc_Id &theId,
          Standard_Boolean theIsInstanceName = Standard_False);

  Standard_EXPORT static TCollection_ExtendedString
  GetName(const Handle(LODoc_Object) & theObj,
          Standard_Boolean theIsInstanceName = Standard_False);

  Standard_EXPORT static Handle(TPrsStd_AISPresentation)
      GetPrs(const LODoc_Id &theId);

  Standard_EXPORT static Handle(TPrsStd_AISPresentation)
      GetPrs(const Handle(LODoc_Object) & theObj);

  Standard_EXPORT static TopoDS_Shape GetShape(const LODoc_Id &theId);

  Standard_EXPORT static TopoDS_Shape
  GetShape(const Handle(LODoc_Object) & theObj, TopLoc_Location &theLoc);

  Standard_EXPORT static Standard_Boolean
  GetInteger(const LODoc_Id &theObj, const Standard_GUID &theGuid,
             Standard_Integer &theValue);

  Standard_EXPORT static Standard_Boolean
  GetInteger(const Handle(LODoc_Object) & theObj, const Standard_GUID &theGuid,
             Standard_Integer &theValue);

  Standard_EXPORT static Standard_Boolean
  SetInteger(const LODoc_Id &theId, const Standard_GUID &theGuid,
             Standard_Integer theValue);

  Standard_EXPORT static Standard_Boolean
  SetInteger(const Handle(LODoc_Object) & theObj, const Standard_GUID &theGuid,
             Standard_Integer theValue);
};

#endif
