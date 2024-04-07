#include <luaocct/LODoc_Attribute.hxx>

#include <TDataStd_Integer.hxx>
#include <TDataStd_Name.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs_AISObject.hxx>

IMPLEMENT_STANDARD_RTTIEXT(LODoc_Attribute, Standard_Transient)

LODoc_Attribute::LODoc_Attribute() {}

TDF_Label LODoc_Attribute::GetId(const Handle(LODoc_Object) & theObj) {
  Handle(TPrsStd_AISPresentation) aPrs = GetPrs(theObj);
  if (aPrs.IsNull())
    return {};

  return aPrs->Label();
}

TCollection_ExtendedString
LODoc_Attribute::GetName(const TDF_Label &theId,
                         Standard_Boolean theIsInstanceName) {
  if (theId.IsNull())
    return {};

  Handle(TDataStd_Name) aNodeName;
  TDF_Label aRef = theId;

  if (!theIsInstanceName)
    XCAFDoc_ShapeTool::GetReferredShape(theId, aRef);

  if (aRef.FindAttribute(TDataStd_Name::GetID(), aNodeName)) {
    return aNodeName->Get();
  }

  return {};
}

TCollection_ExtendedString
LODoc_Attribute::GetName(const Handle(LODoc_Object) & theObj,
                         Standard_Boolean theIsInstanceName) {
  return GetName(GetId(theObj), theIsInstanceName);
}

Handle(TPrsStd_AISPresentation)
    LODoc_Attribute::GetPrs(const TDF_Label &theId) {
  if (theId.IsNull())
    return nullptr;

  Handle(TPrsStd_AISPresentation) aPrs;
  theId.FindAttribute(TPrsStd_AISPresentation::GetID(), aPrs);
  return aPrs;
}

Handle(TPrsStd_AISPresentation)
    LODoc_Attribute::GetPrs(const Handle(LODoc_Object) & theObj) {
  if (theObj.IsNull() || !theObj->HasOwner())
    return nullptr;

  return Handle(TPrsStd_AISPresentation)::DownCast(theObj->GetOwner());
}

TopoDS_Shape LODoc_Attribute::GetShape(const TDF_Label &theId) {
  return XCAFDoc_ShapeTool::GetShape(theId);
}

TopoDS_Shape LODoc_Attribute::GetShape(const Handle(LODoc_Object) & theObj,
                                       TopLoc_Location &theLoc) {
  Handle(AIS_Shape) anObj = Handle(AIS_Shape)::DownCast(theObj);
  if (anObj.IsNull())
    return TopoDS_Shape();

  theLoc = anObj->Transformation();
  return anObj->Shape();
}

Standard_Boolean LODoc_Attribute::GetInteger(const TDF_Label &theId,
                                             const Standard_GUID &theGuid,
                                             Standard_Integer &theValue) {
  if (theId.IsNull())
    return Standard_False;

  Handle(TDataStd_Integer) aData;
  if (!theId.FindAttribute(theGuid, aData))
    return Standard_False;

  theValue = aData->Get();
  return Standard_True;
}

Standard_Boolean LODoc_Attribute::GetInteger(const Handle(LODoc_Object) &
                                                 theObj,
                                             const Standard_GUID &theGuid,
                                             Standard_Integer &theValue) {
  return GetInteger(GetId(theObj), theGuid, theValue);
}

Standard_Boolean LODoc_Attribute::SetInteger(const TDF_Label &theId,
                                             const Standard_GUID &theGuid,
                                             Standard_Integer theValue) {
  if (theId.IsNull())
    return Standard_False;

  Handle(TDataStd_Integer) aData;
  if (theId.FindAttribute(theGuid, aData)) {
    if (theValue != aData->Get())
      aData->Set(theValue);

    return Standard_True;
  }

  TDataStd_Integer::Set(theId, theGuid, theValue);
  return Standard_True;
}

Standard_Boolean LODoc_Attribute::SetInteger(const Handle(LODoc_Object) &
                                                 theObj,
                                             const Standard_GUID &theGuid,
                                             Standard_Integer theValue) {
  return SetInteger(GetId(theObj), theGuid, theValue);
}
