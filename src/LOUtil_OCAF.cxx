#include <luaocct/LOUtil_OCAF.hxx>

#include <STEPCAFControl_Controller.hxx>
#include <STEPCAFControl_Reader.hxx>

TCollection_AsciiString
LOUtil_OCAF::GetXcafNodeName(const XCAFPrs_DocumentNode &theNode,
                             Standard_Boolean theIsInstanceName) {
  Handle(TDataStd_Name) aNodeName;

  if (theIsInstanceName) {
    if (theNode.Label.FindAttribute(TDataStd_Name::GetID(), aNodeName)) {
      return aNodeName->Get();
    }
  } else {
    if (theNode.RefLabel.FindAttribute(TDataStd_Name::GetID(), aNodeName)) {
      return aNodeName->Get();
    }
  }

  return {};
}

TCollection_AsciiString
LOUtil_OCAF::GetXcafNodePathNames(const XCAFPrs_DocumentExplorer &theExpl,
                                  Standard_Boolean theIsInstanceName,
                                  Standard_Integer theLowerDepth) {
  TCollection_AsciiString aPath;

  for (Standard_Integer aDepth = theLowerDepth;
       aDepth <= theExpl.CurrentDepth(); ++aDepth) {
    const XCAFPrs_DocumentNode &aNode = theExpl.Current(aDepth);
    TCollection_AsciiString aName = GetXcafNodeName(aNode, theIsInstanceName);

    if (aName.IsEmpty()) {
      TDF_Tool::Entry(aNode.Label, aName);
    }

    if (aNode.IsAssembly) {
      aName += "$";
    }

    aPath += aName;
  }

  return aPath;
}

Standard_Boolean LOUtil_OCAF::ImportStep(Handle(TDocStd_Document) & theDoc,
                                         Standard_CString theFilePath) {
  if (theDoc.IsNull()) {
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

    if (!aReader.Transfer(theDoc)) {
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

Handle(TPrsStd_AISViewer)
    LOUtil_OCAF::InitAISViewer(const Handle(TDocStd_Document) & theDoc,
                               const Handle(AIS_InteractiveContext) & theCtx) {
  if (theDoc.IsNull() || theCtx.IsNull())
    return nullptr;

  Handle(TPrsStd_AISViewer) aViewer;
  if (TPrsStd_AISViewer::Find(theDoc->Main(), aViewer)) {
    aViewer->SetInteractiveContext(theCtx);
  } else {
    aViewer = TPrsStd_AISViewer::New(theDoc->Main(), theCtx);
  }

  return aViewer;
}
