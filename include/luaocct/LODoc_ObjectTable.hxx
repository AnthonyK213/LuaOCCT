#ifndef _LuaOCCT_LODoc_ObjectTable_HeaderFile
#define _LuaOCCT_LODoc_ObjectTable_HeaderFile

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <Poly_Triangulation.hxx>
#include <Standard.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelList.hxx>
#include <TopoDS_Shape.hxx>

#include "LODoc_Object.hxx"

class LODoc_Document;

class LODoc_ObjectTable : public Standard_Transient {
  friend class LODoc_Document;

protected:
  Standard_EXPORT explicit LODoc_ObjectTable(LODoc_Document *theDoc = nullptr);

  Standard_EXPORT const Handle(AIS_InteractiveContext) & context() const;

public:
  Standard_EXPORT TDF_Label AddShape(const TopoDS_Shape &theShape,
                                     Standard_Boolean theToUpdate);

  Standard_EXPORT TDF_Label AddMesh(const Handle(Poly_Triangulation) & theMesh,
                                    Standard_Boolean theToUpdate);

  Standard_EXPORT void Clear(Standard_Boolean theToUpdate);

  Standard_EXPORT Handle(LODoc_Object) Find(const TDF_Label &theId) const;

  Standard_EXPORT Standard_Boolean DeleteObject(const TDF_Label &theId,
                                                Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean DeleteObject(const Handle(LODoc_Object) &
                                                    theObject,
                                                Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer DeleteObjects(const TDF_LabelList &theIds,
                                                 Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer DeleteObjects(
      const LODoc_ObjectList &theObjects, Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean ShowObject(const TDF_Label &theId,
                                              Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean ShowObject(const Handle(LODoc_Object) &
                                                  theObject,
                                              Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer ShowObjects(const TDF_LabelList &theIds,
                                               Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer
  ShowObjects(const LODoc_ObjectList &theObjects, Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer ShowAll(Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean HideObject(const TDF_Label &theId,
                                              Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean HideObject(const Handle(LODoc_Object) &
                                                  theObject,
                                              Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer HideObjects(const TDF_LabelList &theIds,
                                               Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer
  HideObjects(const LODoc_ObjectList &theObjects, Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean PurgeObject(const Handle(LODoc_Object) &
                                                   theObject,
                                               Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer PurgeObjects(
      const LODoc_ObjectList &theObjects, Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean SelectObject(const TDF_Label &theId,
                                                Standard_Boolean theSelect,
                                                Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Boolean SelectObject(const Handle(LODoc_Object) &
                                                    theObject,
                                                Standard_Boolean theSelect,
                                                Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer SelectObjects(const TDF_LabelList &theIds,
                                                 Standard_Boolean theSelect,
                                                 Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer
  SelectObjects(const LODoc_ObjectList &theObjects, Standard_Boolean theSelect,
                Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer SelectAll(Standard_Boolean theToUpdate);

  Standard_EXPORT Standard_Integer UnselectAll(Standard_Boolean theToUpdate);

  Standard_EXPORT LODoc_ObjectList SelectedObjects() const;

  DEFINE_STANDARD_RTTIEXT(LODoc_ObjectTable, Standard_Transient)

protected:
  LODoc_Document *myDoc;
};

DEFINE_STANDARD_HANDLE(LODoc_ObjectTable, Standard_Transient)

#endif
