#include <luaocct/LODoc_ObjectTable.hxx>

#include <BRepBuilderAPI_MakeVertex.hxx>
#include <MeshVS_DisplayModeFlags.hxx>
#include <TDataXtd_Triangulation.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs_AISObject.hxx>

#include <luaocct/LODoc_Attribute.hxx>
#include <luaocct/LODoc_Document.hxx>
#include <luaocct/LODoc_ObjectTable.hxx>
#include <luaocct/LOUtil_AIS.hxx>

#define LO_OPEN_COMMAND(R)                                                     \
  if (myDoc->Document()->HasOpenCommand())                                     \
    return R;                                                                  \
  myDoc->Document()->OpenCommand();

#define LO_COMMIT_COMMAND()                                                    \
  myDoc->Document()->CommitCommand();                                          \
  if (theToUpdate)                                                             \
    myDoc->UpdateView();

IMPLEMENT_STANDARD_RTTIEXT(LODoc_ObjectTable, Standard_Transient)

LODoc_ObjectTable::LODoc_ObjectTable(LODoc_Document *theDoc) : myDoc(theDoc) {}

const Handle(AIS_InteractiveContext) & LODoc_ObjectTable::Context() const {
  return myDoc->Context();
}

LODoc_Id LODoc_ObjectTable::AddShape(const TopoDS_Shape &theShape,
                                     Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND({});

  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());
  TDF_Label aLabel = anAsm->AddShape(theShape, Standard_True);
  anAsm->UpdateAssemblies();
  // TODO: Driver map.
  auto aPrs = TPrsStd_AISPresentation::Set(aLabel, Standard_GUID());
  aPrs->SetMode(AIS_Shaded);
  aPrs->Display();

  LO_COMMIT_COMMAND();

  myDoc->AddObjectEvent(myDoc);

  return aLabel;
}

LODoc_Id LODoc_ObjectTable::AddMesh(const Handle(Poly_Triangulation) & theMesh,
                                    Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND({});

  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());
  // TODO: Shape?
  TDF_Label aLabel =
      anAsm->AddShape(BRepBuilderAPI_MakeVertex({}), Standard_True);
  TDataXtd_Triangulation::Set(aLabel, theMesh);
  anAsm->UpdateAssemblies();
  // TODO: Driver map.
  auto aPrs = TPrsStd_AISPresentation::Set(aLabel, Standard_GUID());
  aPrs->SetMode(MeshVS_DMF_Shading);
  aPrs->Display();

  LO_COMMIT_COMMAND();

  myDoc->AddObjectEvent(myDoc);

  return {};
}

void LODoc_ObjectTable::Clear(Standard_Boolean theToUpdate) {}

Handle(LODoc_Object) LODoc_ObjectTable::Find(const LODoc_Id &theId) const {
  Handle(TPrsStd_AISPresentation) aPrs = LODoc_Attribute::GetPrs(theId);
  if (aPrs.IsNull())
    return nullptr;

  return aPrs->GetAIS();
}

Standard_Boolean LODoc_ObjectTable::DeleteObject(const LODoc_Id &theId,
                                                 Standard_Boolean theToUpdate) {
  return DeleteObjects({theId}, theToUpdate) == 1;
}

Standard_Boolean LODoc_ObjectTable::DeleteObject(const Handle(LODoc_Object) &
                                                     theObject,
                                                 Standard_Boolean theToUpdate) {
  return DeleteObjects({theObject}, theToUpdate) == 1;
}

Standard_Integer
LODoc_ObjectTable::DeleteObjects(const LODoc_IdList &theIds,
                                 Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbDelete = 0;
  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());

  for (const LODoc_Id &theId : theIds) {
    auto aPrs = LODoc_Attribute::GetPrs(theId);
    if (aPrs.IsNull())
      continue;

    aPrs->Erase(Standard_True);
    anAsm->RemoveComponent(theId);
    ++nbDelete;
  }

  anAsm->UpdateAssemblies();

  LO_COMMIT_COMMAND();

  return nbDelete;
}

Standard_Integer
LODoc_ObjectTable::DeleteObjects(const LODoc_ObjectList &theObjects,
                                 Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbDelete = 0;
  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());

  for (const auto &theObject : theObjects) {
    LODoc_Id anId = LODoc_Attribute::GetId(theObject);
    if (anId.IsNull())
      continue;

    auto aPrs = LODoc_Attribute::GetPrs(anId);
    if (aPrs.IsNull())
      continue;

    aPrs->Erase(Standard_True);
    anAsm->RemoveComponent(anId);
    ++nbDelete;
  }

  anAsm->UpdateAssemblies();

  LO_COMMIT_COMMAND();

  return nbDelete;
}

Standard_Boolean LODoc_ObjectTable::ShowObject(const LODoc_Id &theId,
                                               Standard_Boolean theToUpdate) {
  return ShowObjects({theId}, theToUpdate) == 1;
}

Standard_Boolean LODoc_ObjectTable::ShowObject(const Handle(LODoc_Object) &
                                                   theObject,
                                               Standard_Boolean theToUpdate) {
  return ShowObjects({theObject}, theToUpdate) == 1;
}

Standard_Integer LODoc_ObjectTable::ShowObjects(const LODoc_IdList &theIds,
                                                Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbShow = 0;

  for (const LODoc_Id &theId : theIds) {
    auto aPrs = LODoc_Attribute::GetPrs(theId);
    if (aPrs.IsNull())
      continue;

    if (aPrs->IsDisplayed())
      continue;

    aPrs->Display();
    ++nbShow;
  }

  LO_COMMIT_COMMAND();

  return nbShow;
}

Standard_Integer
LODoc_ObjectTable::ShowObjects(const LODoc_ObjectList &theObjects,
                               Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbShow = 0;

  for (const auto &theObject : theObjects) {
    auto aPrs = LODoc_Attribute::GetPrs(theObject);
    if (aPrs.IsNull())
      continue;

    if (aPrs->IsDisplayed())
      continue;

    aPrs->Display();
    ++nbShow;
  }

  LO_COMMIT_COMMAND();

  return nbShow;
}

Standard_Integer LODoc_ObjectTable::ShowAll(Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbShow = 0;

  for (auto anIter = myDoc->GetXcafExplorer(); anIter.More(); anIter.Next()) {
    auto aPrs = LODoc_Attribute::GetPrs(anIter.Current().Label);
    if (aPrs.IsNull())
      continue;

    if (aPrs->IsDisplayed())
      continue;

    aPrs->Display();
    ++nbShow;
  }

  LO_COMMIT_COMMAND();

  return nbShow;
}

Standard_Boolean LODoc_ObjectTable::HideObject(const LODoc_Id &theId,
                                               Standard_Boolean theToUpdate) {
  LODoc_IdList anIdList{theId};
  return HideObjects(anIdList, theToUpdate) == 1;
}

Standard_Boolean LODoc_ObjectTable::HideObject(const Handle(LODoc_Object) &
                                                   theObject,
                                               Standard_Boolean theToUpdate) {
  LODoc_ObjectList anObjectList{theObject};
  return HideObjects(anObjectList, theToUpdate) == 1;
}

Standard_Integer LODoc_ObjectTable::HideObjects(const LODoc_IdList &theIds,
                                                Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbHide = 0;

  for (const LODoc_Id &anId : theIds) {
    Handle(TPrsStd_AISPresentation) aPrs = LODoc_Attribute::GetPrs(anId);
    if (aPrs.IsNull())
      continue;

    aPrs->Erase();
    ++nbHide;
  }

  LO_COMMIT_COMMAND();

  return nbHide;
}

Standard_Integer
LODoc_ObjectTable::HideObjects(const LODoc_ObjectList &theObjects,
                               Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbHide = 0;

  for (const auto &anObj : theObjects) {
    Handle(TPrsStd_AISPresentation) aPrs = LODoc_Attribute::GetPrs(anObj);
    if (aPrs.IsNull())
      continue;

    /// https://tracker.dev.opencascade.org/view.php?id=30142
    /// The AISObject is recreated during UNDO even if this is an ERASE
    /// operation?
    aPrs->Erase();
    ++nbHide;
  }

  LO_COMMIT_COMMAND();

  return nbHide;
}

Standard_Boolean LODoc_ObjectTable::PurgeObject(const Handle(LODoc_Object) &
                                                    theObject,
                                                Standard_Boolean theToUpdate) {
  LODoc_ObjectList anObjectList{theObject};
  return PurgeObjects(anObjectList, theToUpdate) == 1;
}

Standard_Integer
LODoc_ObjectTable::PurgeObjects(const LODoc_ObjectList &theObjects,
                                Standard_Boolean theToUpdate) {
  return 0;
}

Standard_Boolean LODoc_ObjectTable::SelectObject(const LODoc_Id &theId,
                                                 Standard_Boolean theSelect,
                                                 Standard_Boolean theToUpdate) {
  return SelectObject(Find(theId), theSelect, theToUpdate);
}

Standard_Boolean LODoc_ObjectTable::SelectObject(const Handle(LODoc_Object) &
                                                     theObject,
                                                 Standard_Boolean theSelect,
                                                 Standard_Boolean theToUpdate) {
  if (theObject.IsNull() || !Context()->IsDisplayed(theObject))
    return Standard_False;

  if (Context()->IsSelected(theObject) != theSelect)
    Context()->AddOrRemoveSelected(theObject, theToUpdate);

  return Standard_True;
}

Standard_Integer
LODoc_ObjectTable::SelectObjects(const LODoc_IdList &theIds,
                                 Standard_Boolean theSelect,
                                 Standard_Boolean theToUpdate) {
  Standard_Integer aCount = 0;

  for (const LODoc_Id &anId : theIds) {
    if (SelectObject(anId, theSelect, Standard_False))
      aCount++;
  }

  if (theToUpdate)
    myDoc->UpdateView();

  return aCount;
}

Standard_Integer
LODoc_ObjectTable::SelectObjects(const LODoc_ObjectList &theObjects,
                                 Standard_Boolean theSelect,
                                 Standard_Boolean theToUpdate) {
  Standard_Integer aCount = 0;

  for (const auto &anObj : theObjects) {
    if (SelectObject(anObj, theSelect, Standard_False))
      aCount++;
  }

  if (theToUpdate)
    myDoc->UpdateView();

  return aCount;
}

Standard_Integer LODoc_ObjectTable::SelectAll(Standard_Boolean theToUpdate) {
  Context()->ClearSelected(Standard_False);
  Standard_Integer nbSelect = 0;

  for (auto anIter = myDoc->GetXcafExplorer(); anIter.More(); anIter.Next()) {
    auto aPrs = LODoc_Attribute::GetPrs(anIter.Current().Label);
    if (aPrs.IsNull())
      continue;
    Handle(LODoc_Object) anObj = aPrs->GetAIS();
    if (anObj.IsNull())
      continue;
    Context()->AddOrRemoveSelected(anObj, Standard_False);
    ++nbSelect;
  }

  if (theToUpdate)
    myDoc->UpdateView();

  return nbSelect;
}

Standard_Integer LODoc_ObjectTable::UnselectAll(Standard_Boolean theToUpdate) {
  Standard_Integer nbSelected = Context()->NbSelected();

  for (Context()->InitSelected(); Context()->MoreSelected();
       Context()->NextSelected()) {
    Context()->AddOrRemoveSelected(Context()->SelectedInteractive(),
                                   Standard_False);
  }

  if (theToUpdate)
    myDoc->UpdateView();

  return nbSelected;
}

LODoc_ObjectList LODoc_ObjectTable::SelectedObjects() const {
  return LOUtil_AIS::GetSelections(Context());
}
