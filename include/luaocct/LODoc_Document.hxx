#ifndef _LuaOCCT_LODoc_Document_HeaderFile
#define _LuaOCCT_LODoc_Document_HeaderFile

#include <BinXCAFDrivers.hxx>
#include <OSD_Path.hxx>
#include <RWStl.hxx>
#include <STEPCAFControl_Controller.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <STEPCAFControl_Writer.hxx>
#include <STEPControl_Controller.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <StlAPI_Reader.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDF_Tool.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Application.hxx>
#include <TDocStd_Document.hxx>
#include <V3d_View.hxx>
#include <V3d_Viewer.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFPrs_DocumentExplorer.hxx>
#include <XCAFPrs_DocumentNode.hxx>

#include "LOApp_Application.hxx"
#include "LODoc_Object.hxx"
#include "LODoc_ObjectTable.hxx"

using LODoc_DocumentNode = XCAFPrs_DocumentNode;

class LODoc_Document : public Standard_Transient {
public:
  LODoc_Document();

public:
  const Handle(LODoc_ObjectTable) & Objects() const { return myObjects; }

  const Handle(AIS_InteractiveContext) & Context() const { return myContext; }

  void SetContext(const Handle(AIS_InteractiveContext) & theContext);

  const Handle(TDocStd_Document) & Document() const { return myDoc; }

  Standard_Boolean ImportStep(Standard_CString theFilePath);

  Standard_Boolean ExportStep(Standard_CString theFilePath);

  Handle(Poly_Triangulation) ImportStl(Standard_CString theFilePath);

  Standard_Boolean ExportStl(Standard_CString theFilePath,
                             const Handle(Poly_Triangulation) & theMesh);

  void DumpXcafDocumentTree() const;

  void Undo();

  void Redo();

  void UpdateView();

  XCAFPrs_DocumentExplorer
  GetXcafExplorer(const XCAFPrs_DocumentExplorerFlags theFlags =
                      XCAFPrs_DocumentExplorerFlags_None) const;

  DEFINE_STANDARD_RTTIEXT(LODoc_Document, Standard_Transient)

public:
  virtual void AddObjectEvent(const Handle(LODoc_Document) & theDoc) {}

  virtual void DeleteObjectEvent() {}

  virtual void UndeleteObjectEvent() {}

protected:
  Standard_Boolean createXcafApp();

  Handle(TDocStd_Document)
      newDocument(Standard_Boolean theEmpty = Standard_False);

  void closeDocument(Handle(TDocStd_Document) & theDoc,
                     Standard_Boolean theToUpdate = Standard_False);

  void displayXcafDoc();

protected:
  Handle(LOApp_Application) myApp;
  Handle(TDocStd_Document) myDoc;
  Handle(AIS_InteractiveContext) myContext;
  Handle(LODoc_ObjectTable) myObjects;
};

DEFINE_STANDARD_HANDLE(LODoc_Document, Standard_Transient)

#endif
