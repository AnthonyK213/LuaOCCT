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
#include "LODoc_DocumentExplorer.hxx"
#include "LODoc_Object.hxx"
#include "LODoc_ObjectTable.hxx"

#include <map>

enum {
  LODoc_IDefaultDriver = 0,
  LODoc_IBRepDriver,
  LODoc_IMeshDriver,
};

using LODoc_DocumentNode = XCAFPrs_DocumentNode;

class LODoc_Document : public Standard_Transient {
public:
  Standard_EXPORT LODoc_Document();

public:
  Standard_EXPORT const Handle(LODoc_ObjectTable) & Objects() const {
    return myObjects;
  }

  Standard_EXPORT const Handle(AIS_InteractiveContext) & Context() const {
    return myContext;
  }

  Standard_EXPORT void SetContext(const Handle(AIS_InteractiveContext) &
                                  theContext);

  Standard_EXPORT const Handle(TDocStd_Document) & Document() const {
    return myDoc;
  }

  Standard_EXPORT Standard_Boolean ImportStep(Standard_CString theFilePath);

  Standard_EXPORT Standard_Boolean ExportStep(Standard_CString theFilePath);

  Standard_EXPORT Handle(Poly_Triangulation)
      ImportStl(Standard_CString theFilePath);

  Standard_EXPORT Standard_Boolean ExportStl(Standard_CString theFilePath,
                                             const Handle(Poly_Triangulation) &
                                                 theMesh);

  Standard_EXPORT void Undo();

  Standard_EXPORT void Redo();

  Standard_EXPORT void UpdateView();

  Standard_EXPORT void Close();

  Standard_EXPORT void DumpXcafDocumentTree() const;

  Standard_EXPORT Handle(LODoc_DocumentExplorer)
      DocumentExplorer(const Standard_Integer theFlags) const;

  Standard_EXPORT const Standard_GUID &
  GetDriverID(const Standard_Integer theDriverIndex) const;

  DEFINE_STANDARD_RTTIEXT(LODoc_Document, Standard_Transient)

public:
  Standard_EXPORT virtual void AddObjectEvent(const Handle(LODoc_Document) &
                                              theDoc) {}

  Standard_EXPORT virtual void DeleteObjectEvent() {}

  Standard_EXPORT virtual void UndeleteObjectEvent() {}

protected:
  Standard_EXPORT Standard_Boolean createXcafApp();

  Standard_EXPORT Handle(TDocStd_Document)
      newDocument(Standard_Boolean theEmpty = Standard_False);

  Standard_EXPORT void
  closeDocument(Handle(TDocStd_Document) & theDoc,
                Standard_Boolean theToUpdate = Standard_False);

  Standard_EXPORT void displayXcafDoc();

  Standard_EXPORT virtual void initDriverID();

protected:
  Handle(LOApp_Application) myApp;
  Handle(TDocStd_Document) myDoc;
  Handle(AIS_InteractiveContext) myContext;
  Handle(LODoc_ObjectTable) myObjects;
  std::map<Standard_Integer, Standard_GUID> myDriverIDMap{};
};

DEFINE_STANDARD_HANDLE(LODoc_Document, Standard_Transient)

#endif
