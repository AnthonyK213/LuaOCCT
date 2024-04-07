#ifndef _LuaOCCT_LODoc_Attribute_HeaderFile
#define _LuaOCCT_LODoc_Attribute_HeaderFile

#include <TPrsStd_AISPresentation.hxx>
#include <TopLoc_Location.hxx>

#include "LODoc_Object.hxx"

class LODoc_Attribute : public Standard_Transient {
public:
  LODoc_Attribute();

  DEFINE_STANDARD_RTTIEXT(LODoc_Attribute, Standard_Transient)

public:
  Standard_EXPORT static TDF_Label GetId(const Handle(LODoc_Object) & theObj);

  Standard_EXPORT static TCollection_ExtendedString
  GetName(const TDF_Label &theId,
          Standard_Boolean theIsInstanceName = Standard_False);

  Standard_EXPORT static TCollection_ExtendedString
  GetName(const Handle(LODoc_Object) & theObj,
          Standard_Boolean theIsInstanceName = Standard_False);

  Standard_EXPORT static Handle(TPrsStd_AISPresentation)
      GetPrs(const TDF_Label &theId);

  Standard_EXPORT static Handle(TPrsStd_AISPresentation)
      GetPrs(const Handle(LODoc_Object) & theObj);

  Standard_EXPORT static TopoDS_Shape GetShape(const TDF_Label &theId);

  Standard_EXPORT static TopoDS_Shape
  GetShape(const Handle(LODoc_Object) & theObj, TopLoc_Location &theLoc);

  Standard_EXPORT static Standard_Boolean
  GetInteger(const TDF_Label &theObj, const Standard_GUID &theGuid,
             Standard_Integer &theValue);

  Standard_EXPORT static Standard_Boolean
  GetInteger(const Handle(LODoc_Object) & theObj, const Standard_GUID &theGuid,
             Standard_Integer &theValue);

  Standard_EXPORT static Standard_Boolean
  SetInteger(const TDF_Label &theId, const Standard_GUID &theGuid,
             Standard_Integer theValue);

  Standard_EXPORT static Standard_Boolean
  SetInteger(const Handle(LODoc_Object) & theObj, const Standard_GUID &theGuid,
             Standard_Integer theValue);

protected:
  TCollection_ExtendedString aName;
  Quantity_Color aColor;
};

DEFINE_STANDARD_HANDLE(LODoc_Attribute, Standard_Transient)

#endif
