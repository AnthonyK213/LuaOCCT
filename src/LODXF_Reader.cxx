#include <luaocct/LODXF_Reader.hxx>

LODXF_Reader::LODXF_Reader() {}

IFSelect_ReturnStatus
LODXF_Reader::ReadFile(const Standard_CString theFileName) {
  return IFSelect_RetDone;
}

Standard_Boolean
LODXF_Reader::Transfer(Handle(TDocStd_Document) & theDoc,
                       const Message_ProgressRange &theProgress) {
  return Standard_True;
}
