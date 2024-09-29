#include <luaocct/LODoc_Document.hxx>
#include <luaocct/LODoc_DocumentExplorer.hxx>

IMPLEMENT_STANDARD_RTTIEXT(LODoc_DocumentExplorer, Standard_Transient)

LODoc_DocumentExplorer::LODoc_DocumentExplorer() {}

LODoc_DocumentExplorer::LODoc_DocumentExplorer(const Handle(LODoc_Document) &
                                                   theDocument,
                                               const Standard_Integer theFlags)
    : myE(theDocument->Document(), theFlags) {
  if (theDocument.IsNull())
    return;
  Handle(TDocStd_Document) aDoc = theDocument->Document();
  if (aDoc.IsNull())
    return;
  Handle(XCAFDoc_ShapeTool) aST = XCAFDoc_DocumentTool::ShapeTool(aDoc->Main());
  TDF_LabelSequence aRootLabels;
  aST->GetFreeShapes(aRootLabels);

  /* NOTE: **DO NOT** use copy ctor/assignment of `XCAFPrs_DocumentExplorer`! */

  myE.Init(aDoc, aRootLabels, theFlags, XCAFPrs_Style());
}

void LODoc_DocumentExplorer::init(const Handle(LODoc_Document) & theDocument,
                                  const TDF_Label &theRoot,
                                  const Standard_Integer theFlags) {
  if (!theDocument.IsNull())
    myE.Init(theDocument->Document(), theRoot, theFlags);
}

Standard_Boolean LODoc_DocumentExplorer::More() const { return myE.More(); }

const XCAFPrs_DocumentNode &LODoc_DocumentExplorer::Current() const {
  return myE.Current();
}

Standard_Integer LODoc_DocumentExplorer::CurrentDepth() const {
  return myE.CurrentDepth();
}

void LODoc_DocumentExplorer::Next() { myE.Next(); }
