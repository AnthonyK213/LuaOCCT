#ifndef _LuaOCCT_LODoc_ObjectTable_HeaderFile
#define _LuaOCCT_LODoc_ObjectTable_HeaderFile

#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <Poly_Triangulation.hxx>
#include <Standard.hxx>
#include <Standard_Transient.hxx>
#include <Standard_Type.hxx>
#include <TopoDS_Shape.hxx>

#include "LODoc_Object.hxx"

class LODoc_Document;

class LODoc_ObjectTable : public Standard_Transient {
  // friend class LODoc_Document;

public:
  explicit LODoc_ObjectTable(LODoc_Document *theDoc = nullptr);

public:
  const Handle(AIS_InteractiveContext) & Context() const;

  LODoc_Id AddShape(const TopoDS_Shape &theShape,
                       Standard_Boolean theToUpdate);

  LODoc_Id AddMesh(const Handle(Poly_Triangulation) & theMesh,
                      Standard_Boolean theToUpdate);

  void Clear(Standard_Boolean theToUpdate);

  Handle(LODoc_Object) Find(const LODoc_Id &theId) const;

  Standard_Boolean DeleteObject(const LODoc_Id &theId,
                                Standard_Boolean theToUpdate);

  Standard_Boolean DeleteObject(const Handle(LODoc_Object) & theObject,
                                Standard_Boolean theToUpdate);

  Standard_Integer DeleteObjects(const LODoc_IdList &theIds,
                                 Standard_Boolean theToUpdate);

  Standard_Integer DeleteObjects(const LODoc_ObjectList &theObjects,
                                 Standard_Boolean theToUpdate);

  Standard_Boolean ShowObject(const LODoc_Id &theId,
                              Standard_Boolean theToUpdate);

  Standard_Boolean ShowObject(const Handle(LODoc_Object) & theObject,
                              Standard_Boolean theToUpdate);

  Standard_Integer ShowObjects(const LODoc_IdList &theIds,
                               Standard_Boolean theToUpdate);

  Standard_Integer ShowObjects(const LODoc_ObjectList &theObjects,
                               Standard_Boolean theToUpdate);

  Standard_Integer ShowAll(Standard_Boolean theToUpdate);

  Standard_Boolean HideObject(const LODoc_Id &theId,
                              Standard_Boolean theToUpdate);

  Standard_Boolean HideObject(const Handle(LODoc_Object) & theObject,
                              Standard_Boolean theToUpdate);

  Standard_Integer HideObjects(const LODoc_IdList &theIds,
                               Standard_Boolean theToUpdate);

  Standard_Integer HideObjects(const LODoc_ObjectList &theObjects,
                               Standard_Boolean theToUpdate);

  Standard_Boolean PurgeObject(const Handle(LODoc_Object) & theObject,
                               Standard_Boolean theToUpdate);

  Standard_Integer PurgeObjects(const LODoc_ObjectList &theObjects,
                                Standard_Boolean theToUpdate);

  Standard_Boolean SelectObject(const LODoc_Id &theId,
                                Standard_Boolean theSelect,
                                Standard_Boolean theToUpdate);

  Standard_Boolean SelectObject(const Handle(LODoc_Object) & theObject,
                                Standard_Boolean theSelect,
                                Standard_Boolean theToUpdate);

  Standard_Integer SelectObjects(const LODoc_IdList &theIds,
                                 Standard_Boolean theSelect,
                                 Standard_Boolean theToUpdate);

  Standard_Integer SelectObjects(const LODoc_ObjectList &theObjects,
                                 Standard_Boolean theSelect,
                                 Standard_Boolean theToUpdate);

  Standard_Integer SelectAll(Standard_Boolean theToUpdate);

  Standard_Integer UnselectAll(Standard_Boolean theToUpdate);

  LODoc_ObjectList SelectedObjects() const;

  DEFINE_STANDARD_RTTIEXT(LODoc_ObjectTable, Standard_Transient)

private:
  LODoc_Document *myDoc;
};

DEFINE_STANDARD_HANDLE(LODoc_ObjectTable, Standard_Transient)

#endif
