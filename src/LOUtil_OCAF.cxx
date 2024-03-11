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
