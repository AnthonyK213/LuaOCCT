#ifndef _LuaOCCT_LODoc_DocumentExplorer_HeaderFile
#define _LuaOCCT_LODoc_DocumentExplorer_HeaderFile

#include <XCAFPrs_DocumentExplorer.hxx>

class LODoc_Document;

class LODoc_DocumentExplorer : public Standard_Transient {
  friend class LODoc_Document;

public:
  Standard_EXPORT LODoc_DocumentExplorer();

  Standard_EXPORT Standard_Boolean More() const;

  Standard_EXPORT const XCAFPrs_DocumentNode &Current() const;

  Standard_EXPORT Standard_Integer CurrentDepth() const;

  Standard_EXPORT void Next();

  DEFINE_STANDARD_RTTIEXT(LODoc_DocumentExplorer, Standard_Transient)

private:
  Standard_EXPORT LODoc_DocumentExplorer(const Handle(LODoc_Document) &
                                             theDocument,
                                         const Standard_Integer theFlags);

  Standard_EXPORT void init(const Handle(LODoc_Document) & theDocument,
                            const TDF_Label &theRoot,
                            const Standard_Integer theFlags);

private:
  Handle(LODoc_Document) myDoc;
  XCAFPrs_DocumentExplorer myE;
};

DEFINE_STANDARD_HANDLE(LODoc_DocumentExplorer, Standard_Transient)

#endif
