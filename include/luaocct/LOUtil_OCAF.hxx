#ifndef _LuaOCCT_LOUtil_OCAF_HeaderFile
#define _LuaOCCT_LOUtil_OCAF_HeaderFile

#include <TDF_Tool.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Document.hxx>
#include <TPrsStd_AISPresentation.hxx>
#include <TPrsStd_AISViewer.hxx>
#include <XCAFPrs_DocumentExplorer.hxx>
#include <XCAFPrs_DocumentNode.hxx>
#include <XCAFPrs_Driver.hxx>

class LOUtil_OCAF {
public:
  Standard_EXPORT static TCollection_AsciiString
  GetXcafNodeName(const XCAFPrs_DocumentNode &theNode,
                  Standard_Boolean theIsInstanceName);

  Standard_EXPORT static TCollection_AsciiString
  GetXcafNodePathNames(const XCAFPrs_DocumentExplorer &theExpl,
                       Standard_Boolean theIsInstanceName,
                       Standard_Integer theLowerDepth);

  Standard_EXPORT static Standard_Boolean
  ImportStep(Handle(TDocStd_Document) & theDoc, Standard_CString theFilePath);

  Standard_EXPORT static Handle(TPrsStd_AISViewer)
      InitAISViewer(const Handle(TDocStd_Document) & theDoc,
                    const Handle(AIS_InteractiveContext) & theCtx);
};

#endif
