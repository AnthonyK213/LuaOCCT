#include <luaocct/LODoc_Document.hxx>

#include <TDF_LabelMap.hxx>
#include <TDataStd_Name.hxx>
#include <TNaming_NamedShape.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <TPrsStd_DriverTable.hxx>
#include <TPrsStd_NamedShapeDriver.hxx>
#include <V3d_Viewer.hxx>
#include <XCAFPrs_AISObject.hxx>
#include <XCAFPrs_Driver.hxx>

#include <luaocct/LODoc_Attribute.hxx>
#include <luaocct/LODoc_Document.hxx>
#include <luaocct/LODoc_ObjectTable.hxx>
#include <luaocct/LOUtil_OCAF.hxx>

IMPLEMENT_STANDARD_RTTIEXT(LODoc_Document, Standard_Transient)

LODoc_Document::LODoc_Document() {
  createXcafApp();
  initDriverID();
  myDoc = newDocument();
  myObjects = new LODoc_ObjectTable(this);
}

void LODoc_Document::SetContext(const Handle(AIS_InteractiveContext) &
                                theContext) {
  myContext = theContext;
  LOUtil_OCAF::InitAISViewer(myDoc, myContext);
}

static Standard_Boolean importStep(Handle(TDocStd_Document) & aDoc,
                                   Standard_CString theFilePath) {
  if (aDoc.IsNull()) {
    std::cout << "Error: The document is null\n";
    return Standard_False;
  }

  STEPCAFControl_Controller::Init();
  STEPControl_Controller::Init();
  STEPCAFControl_Reader aReader;
  aReader.SetColorMode(Standard_True);
  aReader.SetNameMode(Standard_True);
  aReader.SetLayerMode(Standard_True);
  aReader.SetSHUOMode(Standard_True);

  try {
    if (aReader.ReadFile(theFilePath) != IFSelect_RetDone) {
      std::cout << "Error: On reading STEP file " << theFilePath << '\n';
      return Standard_False;
    }

    if (!aReader.Transfer(aDoc)) {
      std::cout << "Error: On transferring STEP file " << theFilePath << '\n';
      return Standard_False;
    }
  } catch (const Standard_Failure &theFailure) {
    std::cout << "Exception raised during STEP import: "
              << theFailure.GetMessageString() << '\n';
    return Standard_False;
  }

  return Standard_True;
}

Standard_Boolean LODoc_Document::ImportStep(Standard_CString theFilePath) {
  createXcafApp();
  Handle(TDocStd_Document) aDoc = newDocument(Standard_True);
  Standard_Boolean ok = importStep(aDoc, theFilePath);

  if (ok) {
    std::swap(myDoc, aDoc);
    displayXcafDoc();
  }

  closeDocument(aDoc);
  return ok;
}

Standard_Boolean LODoc_Document::ExportStep(Standard_CString theFilePath) {
  STEPCAFControl_Writer aWriter;
  aWriter.SetColorMode(Standard_True);
  aWriter.SetNameMode(Standard_True);
  aWriter.SetLayerMode(Standard_True);
  aWriter.SetSHUOMode(Standard_True);

  try {
    if (!aWriter.Transfer(myDoc)) {
      std::cout << "Error: On transferring STEP file " << theFilePath << '\n';
      return Standard_False;
    }

    if (aWriter.Write(theFilePath) != IFSelect_RetDone) {
      std::cout << "Error: On writing STEP file " << theFilePath << '\n';
      return Standard_False;
    }
  } catch (const Standard_Failure &theFailure) {
    std::cout << "Exception raised during STEP export: "
              << theFailure.GetMessageString() << '\n';
    return Standard_False;
  }

  return Standard_True;
}

Handle(Poly_Triangulation)
    LODoc_Document::ImportStl(Standard_CString theFilePath) {
  try {
    Handle(Poly_Triangulation) aStlMesh = RWStl::ReadFile(theFilePath);
    return aStlMesh;
  } catch (const Standard_Failure &theFailure) {
    std::cout << "Exception raised during STL import: "
              << theFailure.GetMessageString() << '\n';
    return nullptr;
  }
}

Standard_Boolean LODoc_Document::ExportStl(Standard_CString theFilePath,
                                           const Handle(Poly_Triangulation) &
                                               theMesh) {
  try {
    OSD_Path aPath{theFilePath};
    return RWStl::WriteAscii(theMesh, aPath);
  } catch (const Standard_Failure &theFailure) {
    std::cout << "Exception raised during STL export: "
              << theFailure.GetMessageString() << '\n';
    return Standard_False;
  }
}

void LODoc_Document::DumpXcafDocumentTree() const {
  if (myDoc.IsNull())
    return;

  for (XCAFPrs_DocumentExplorer aDocExpl(myDoc, 0); aDocExpl.More();
       aDocExpl.Next()) {
    TCollection_AsciiString aName = LOUtil_OCAF::GetXcafNodePathNames(
        aDocExpl, Standard_False, aDocExpl.CurrentDepth());
    aName = TCollection_AsciiString(aDocExpl.CurrentDepth() * 2, ' ') + aName +
            " @" + aDocExpl.Current().Id;
    std::cout << aName << '\n';
  }

  std::cout << std::endl;
}

Standard_Boolean LODoc_Document::createXcafApp() {
  if (!myApp.IsNull())
    return Standard_True;

  try {
    myApp = new TDocStd_Application();
    BinXCAFDrivers::DefineFormat(myApp);
    return Standard_True;
  } catch (const Standard_Failure &theFailure) {
    std::cout << "Error: " << theFailure.GetMessageString() << '\n';
    return Standard_False;
  }
}

Handle(TDocStd_Document)
    LODoc_Document::newDocument(Standard_Boolean theEmpty) {
  Handle(TDocStd_Document) aDoc;

  if (!myApp.IsNull())
    myApp->NewDocument(TCollection_ExtendedString("BinXCAF"), aDoc);

  if (!aDoc.IsNull()) {
    aDoc->SetUndoLimit(100);

    if (!theEmpty) {
      Handle(XCAFDoc_ShapeTool) anAsm =
          XCAFDoc_DocumentTool::ShapeTool(aDoc->Main());
      TDF_Label aLabel = anAsm->NewShape();
      TDataStd_Name::Set(aLabel, "0");
    }

    LOUtil_OCAF::InitAISViewer(aDoc, myContext);
  }

  return aDoc;
}

void LODoc_Document::closeDocument(Handle(TDocStd_Document) & theDoc,
                                   Standard_Boolean theToUpdate) {
  if (!theDoc.IsNull()) {
    if (theDoc->HasOpenCommand())
      theDoc->AbortCommand();

    /// To keep the TPrsStd_AISViewer alive while removing the
    /// LODoc_Objects, do ForgetAllAttributes on children before
    /// the root.
    theDoc->Main().ForgetAllAttributes(Standard_True);
    theDoc->Main().Root().ForgetAllAttributes(Standard_True);
    myApp->Close(theDoc);
    theDoc.Nullify();
  }
}

void LODoc_Document::displayXcafDoc() {
  Handle(TPrsStd_AISViewer) aViewer =
      LOUtil_OCAF::InitAISViewer(myDoc, myContext);

  if (aViewer.IsNull())
    return;

  TDF_LabelMap anAsmMap{};
  Standard_Boolean skip = Standard_False;
  Standard_Integer skipDepth = 0;

  for (XCAFPrs_DocumentExplorer aDocExpl(myDoc, 0); aDocExpl.More();
       aDocExpl.Next()) {
    Standard_Integer aDepth = aDocExpl.CurrentDepth();

    /// To skip assembly instances which have already been visited.
    /// It seems that FreeCAD makes new copies for the assembly instances, but
    /// this breaks down the connections between the identical instances.
    /// The solution below is, at the first time visit one instance, visit its
    /// children normally; for the rest visits, just display the assembly
    /// instance and visit its siblings.
    /// Maybe there is a better solution? Never visit the instance's children
    /// unless the user enters "assembly editing mode"? This might make more
    /// sense.

    if (skip) {
      if (aDepth > skipDepth)
        continue;
      else
        skip = Standard_False;
    }

    const LODoc_DocumentNode &aNode = aDocExpl.Current();

    if (aNode.IsAssembly) {
      if (anAsmMap.Contains(aNode.RefLabel)) {
        skip = Standard_True;
        skipDepth = aDepth;
      } else {
        anAsmMap.Add(aNode.RefLabel);
        continue;
      }
    }

    Handle(TPrsStd_AISPresentation) aPrs;
    if (!aNode.Label.FindAttribute(TPrsStd_AISPresentation::GetID(), aPrs)) {
      aPrs = TPrsStd_AISPresentation::Set(aNode.Label, XCAFPrs_Driver::GetID());
    }

    aPrs->SetMode(AIS_Shaded);
    aPrs->Display();
    Handle(LODoc_Object) anObj = aPrs->GetAIS();

    if (anObj.IsNull())
      continue;

    if (aDepth > 0) {
      const LODoc_DocumentNode &aFather = aDocExpl.Current(aDepth - 1);
      anObj->SetLocalTransformation(aFather.Location);
    }
  }
}

void LODoc_Document::Undo() {
  if (myDoc->Undo())
    UpdateView();
}

void LODoc_Document::Redo() {
  if (myDoc->Redo())
    UpdateView();
}

void LODoc_Document::UpdateView() { Context()->UpdateCurrentViewer(); }

void LODoc_Document::Close() { closeDocument(myDoc); }

Handle(LODoc_DocumentExplorer)
    LODoc_Document::DocumentExplorer(const Standard_Integer theFlags) const {
  return new LODoc_DocumentExplorer(this, theFlags);
}

const Standard_GUID &
LODoc_Document::GetDriverID(const Standard_Integer theDriverIndex) const {
  auto it = myDriverIDMap.find(theDriverIndex);
  if (it == myDriverIDMap.end())
    return XCAFPrs_Driver::GetID();
  return it->second;
}

void LODoc_Document::initDriverID() {}
