#include <luaocct/LODoc_ObjectTable.hxx>

#include <BRep_Builder.hxx>
#include <MeshVS_DisplayModeFlags.hxx>
#include <TDataXtd_Triangulation.hxx>
#include <TNaming_Builder.hxx>
#include <TNaming_NamedShape.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <TopoDS_Compound.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs_AISObject.hxx>

#include <luaocct/LODoc_Attribute.hxx>
#include <luaocct/LODoc_Document.hxx>
#include <luaocct/LODoc_DocumentExplorer.hxx>
#include <luaocct/LODoc_ObjectTable.hxx>
#include <luaocct/LOUtil_AIS.hxx>

#define LO_OPEN_COMMAND(...)                                                   \
  if (myDoc->Document()->HasOpenCommand())                                     \
    return __VA_ARGS__;                                                        \
  myDoc->Document()->OpenCommand();

#define LO_COMMIT_COMMAND()                                                    \
  myDoc->Document()->CommitCommand();                                          \
  if (theToUpdate)                                                             \
    myDoc->UpdateView();

IMPLEMENT_STANDARD_RTTIEXT(LODoc_ObjectTable, Standard_Transient)

LODoc_ObjectTable::LODoc_ObjectTable(LODoc_Document *theDoc) : myDoc(theDoc) {}

const Handle(AIS_InteractiveContext) & LODoc_ObjectTable::context() const {
  return myDoc->Context();
}

TDF_Label LODoc_ObjectTable::AddShape(const TopoDS_Shape &theShape,
                                      const Handle(LODoc_Attribute) & theAttr,
                                      Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND({});

  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());
  TDF_Label aLabel = anAsm->AddShape(theShape, Standard_True);
  anAsm->UpdateAssemblies();
  /* FIXME: `TPrsStd_DriverTable` should be initialized. */
  auto aPrs = TPrsStd_AISPresentation::Set(
      aLabel, myDoc->GetDriverID(LODoc_IBRepDriver));
  aPrs->SetMode(AIS_Shaded);
  aPrs->Display();

  LO_COMMIT_COMMAND();

  myDoc->AddObjectEvent();

  return aLabel;
}

TDF_Label LODoc_ObjectTable::AddMesh(const Handle(Poly_Triangulation) & theMesh,
                                     const Handle(LODoc_Attribute) & theAttr,
                                     Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND({});

  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());
  /* TODO: Better solution? */
  TopoDS_Compound aCompound{};
  BRep_Builder aBuilder{};
  aBuilder.MakeCompound(aCompound);
  TDF_Label aLabel = anAsm->AddShape(aCompound, Standard_True);
  TDataXtd_Triangulation::Set(aLabel, theMesh);
  anAsm->UpdateAssemblies();
  auto aPrs = TPrsStd_AISPresentation::Set(
      aLabel, myDoc->GetDriverID(LODoc_IMeshDriver));
  aPrs->SetMode(MeshVS_DMF_Shading);
  aPrs->Display();

  LO_COMMIT_COMMAND();

  myDoc->AddObjectEvent();

  return {};
}

void LODoc_ObjectTable::Clear(Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND();

  for (auto anIter = myDoc->DocumentExplorer(0); anIter->More();
       anIter->Next()) {
    const XCAFPrs_DocumentNode &aNode = anIter->Current();
    deleteObjectRaw(aNode.Label);
  }

  LO_COMMIT_COMMAND();
}

Handle(LODoc_Object) LODoc_ObjectTable::Find(const TDF_Label &theId) const {
  Handle(TPrsStd_AISPresentation) aPrs = LODoc_Attribute::GetPrs(theId);
  if (aPrs.IsNull())
    return nullptr;

  return aPrs->GetAIS();
}

Standard_Boolean LODoc_ObjectTable::DeleteObject(const TDF_Label &theId,
                                                 Standard_Boolean theToUpdate) {
  TDF_LabelList aList{};
  aList.Append(theId);
  return DeleteObjects(aList, theToUpdate) == 1;
}

Standard_Boolean LODoc_ObjectTable::DeleteObject(const Handle(LODoc_Object) &
                                                     theObject,
                                                 Standard_Boolean theToUpdate) {
  return DeleteObjects({theObject}, theToUpdate) == 1;
}

Standard_Integer
LODoc_ObjectTable::DeleteObjects(const TDF_LabelList &theIds,
                                 Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbDelete = 0;
  auto anAsm = XCAFDoc_DocumentTool::ShapeTool(myDoc->Document()->Main());

  for (const TDF_Label &anId : theIds) {
    if (deleteObjectRaw(anId))
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

  for (const auto &anObject : theObjects) {
    TDF_Label anId = LODoc_Attribute::GetId(anObject);
    if (deleteObjectRaw(anId))
      ++nbDelete;
  }

  anAsm->UpdateAssemblies();

  LO_COMMIT_COMMAND();

  return nbDelete;
}

Standard_Boolean LODoc_ObjectTable::ShowObject(const TDF_Label &theId,
                                               Standard_Boolean theToUpdate) {
  TDF_LabelList aList{};
  aList.Append(theId);
  return ShowObjects(aList, theToUpdate) == 1;
}

Standard_Boolean LODoc_ObjectTable::ShowObject(const Handle(LODoc_Object) &
                                                   theObject,
                                               Standard_Boolean theToUpdate) {
  return ShowObjects({theObject}, theToUpdate) == 1;
}

Standard_Integer LODoc_ObjectTable::ShowObjects(const TDF_LabelList &theIds,
                                                Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbShow = 0;

  for (const TDF_Label &anId : theIds) {
    if (showObjectRaw(anId))
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

  for (const auto &anObject : theObjects) {
    TDF_Label anId = LODoc_Attribute::GetId(anObject);
    if (showObjectRaw(anId))
      ++nbShow;
  }

  LO_COMMIT_COMMAND();

  return nbShow;
}

Standard_Integer LODoc_ObjectTable::ShowAll(Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbShow = 0;

  for (auto anIter = myDoc->DocumentExplorer(0); anIter->More();
       anIter->Next()) {
    if (showObjectRaw(anIter->Current().Label))
      ++nbShow;
  }

  LO_COMMIT_COMMAND();

  return nbShow;
}

Standard_Boolean LODoc_ObjectTable::HideObject(const TDF_Label &theId,
                                               Standard_Boolean theToUpdate) {
  TDF_LabelList aList{};
  aList.Append(theId);
  return HideObjects(aList, theToUpdate) == 1;
}

Standard_Boolean LODoc_ObjectTable::HideObject(const Handle(LODoc_Object) &
                                                   theObject,
                                               Standard_Boolean theToUpdate) {
  LODoc_ObjectList anObjectList{theObject};
  return HideObjects(anObjectList, theToUpdate) == 1;
}

Standard_Integer LODoc_ObjectTable::HideObjects(const TDF_LabelList &theIds,
                                                Standard_Boolean theToUpdate) {
  LO_OPEN_COMMAND(0);

  Standard_Integer nbHide = 0;

  for (const TDF_Label &anId : theIds) {
    if (hideObjectRaw(anId))
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

  for (const auto &anObject : theObjects) {
    TDF_Label anId = LODoc_Attribute::GetId(anObject);
    if (hideObjectRaw(anId))
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

Standard_Boolean LODoc_ObjectTable::SelectObject(const TDF_Label &theId,
                                                 Standard_Boolean theSelect,
                                                 Standard_Boolean theToUpdate) {
  return SelectObject(Find(theId), theSelect, theToUpdate);
}

Standard_Boolean LODoc_ObjectTable::SelectObject(const Handle(LODoc_Object) &
                                                     theObject,
                                                 Standard_Boolean theSelect,
                                                 Standard_Boolean theToUpdate) {
  if (theObject.IsNull() || !context()->IsDisplayed(theObject))
    return Standard_False;

  if (context()->IsSelected(theObject) != theSelect)
    context()->AddOrRemoveSelected(theObject, theToUpdate);

  return Standard_True;
}

Standard_Integer
LODoc_ObjectTable::SelectObjects(const TDF_LabelList &theIds,
                                 Standard_Boolean theSelect,
                                 Standard_Boolean theToUpdate) {
  Standard_Integer aCount = 0;

  for (const TDF_Label &anId : theIds) {
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
  context()->ClearSelected(Standard_False);
  Standard_Integer nbSelect = 0;

  for (auto anIter = myDoc->DocumentExplorer(0); anIter->More();
       anIter->Next()) {
    auto aPrs = LODoc_Attribute::GetPrs(anIter->Current().Label);
    if (aPrs.IsNull())
      continue;
    Handle(LODoc_Object) anObj = aPrs->GetAIS();
    if (anObj.IsNull())
      continue;
    context()->AddOrRemoveSelected(anObj, Standard_False);
    ++nbSelect;
  }

  if (theToUpdate)
    myDoc->UpdateView();

  return nbSelect;
}

Standard_Integer LODoc_ObjectTable::UnselectAll(Standard_Boolean theToUpdate) {
  Standard_Integer nbSelected = context()->NbSelected();

  for (context()->InitSelected(); context()->MoreSelected();
       context()->NextSelected()) {
    context()->AddOrRemoveSelected(context()->SelectedInteractive(),
                                   Standard_False);
  }

  if (theToUpdate)
    myDoc->UpdateView();

  return nbSelected;
}

LODoc_ObjectList LODoc_ObjectTable::SelectedObjects() const {
  return LOUtil_AIS::GetSelections(context());
}

Standard_Boolean LODoc_ObjectTable::deleteObjectRaw(const TDF_Label &theId) {
  if (theId.IsNull())
    return Standard_False;

  auto aPrs = LODoc_Attribute::GetPrs(theId);
  Standard_Boolean hasDisp = !aPrs.IsNull();
  if (hasDisp)
    aPrs->Erase(Standard_True);

  theId.ForgetAllAttributes();
  return hasDisp;
}

Standard_Boolean LODoc_ObjectTable::showObjectRaw(const TDF_Label &theId) {
  auto aPrs = LODoc_Attribute::GetPrs(theId);
  if (aPrs.IsNull())
    return Standard_False;

  if (aPrs->IsDisplayed())
    return Standard_False;

  aPrs->Display();
  return Standard_True;
}

Standard_Boolean LODoc_ObjectTable::hideObjectRaw(const TDF_Label &theId) {
  Handle(TPrsStd_AISPresentation) aPrs = LODoc_Attribute::GetPrs(theId);
  if (aPrs.IsNull())
    return Standard_False;

  /* https://tracker.dev.opencascade.org/view.php?id=30142
   * The AISObject is recreated during UNDO even if this is an ERASE operation?
   */

  aPrs->Erase();
  return Standard_True;
}
