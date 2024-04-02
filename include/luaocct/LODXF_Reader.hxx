#ifndef _LuaOCCT_LODXF_Reader_HeaderFile
#define _LuaOCCT_LODXF_Reader_HeaderFile

#include <Geom_Line.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <Message_ProgressRange.hxx>
#include <TDocStd_Document.hxx>
#include <gp_Pnt.hxx>

typedef enum {
  LODXF_Units_Unspecified = 0,
  LODXF_Units_Inches,
  LODXF_Units_Feet,
  LODXF_Units_Miles,
  LODXF_Units_Millimeters,
  LODXF_Units_Centimeters,
  LODXF_Units_Meters,
  LODXF_Units_Kilometers,
  LODXF_Units_Microinches,
  LODXF_Units_Mils,
  LODXF_Units_Yards,
  LODXF_Units_Angstroms,
  LODXF_Units_Nanometers,
  LODXF_Units_Microns,
  LODXF_Units_Decimeters,
  LODXF_Units_Dekameters,
  LODXF_Units_Hectometers,
  LODXF_Units_Gigameters,
  LODXF_Units_AstronomicalUnits,
  LODXF_Units_LightYears,
  LODXF_Units_Parsecs,
} LODXF_Units;

typedef enum {
  LODXF_Version_Unknown = 0,
  LODXF_Version_Older,
  LODXF_Version_R10,
  LODXF_Version_R11_12,
  LODXF_Version_R13,
  LODXF_Version_R14,
  LODXF_Version_R2000,
  LODXF_Version_R2004,
  LODXF_Version_R2007,
  LODXF_Version_R2010,
  LODXF_Version_R2013,
  LODXF_Version_R2018,
  LODXF_Version_Newer,
} LODXF_Version;

class LODXF_Reader {
public:
  Standard_EXPORT LODXF_Reader();

  Standard_EXPORT IFSelect_ReturnStatus
  ReadFile(const Standard_CString theFileName);

  Standard_EXPORT Standard_Boolean
  Transfer(Handle(TDocStd_Document) & theDoc,
           const Message_ProgressRange &theProgress = Message_ProgressRange());

private:
  Standard_Boolean readHeaderSection();

  Standard_Boolean readTablesSection();

  Standard_Boolean readBlocksSection();

  Standard_Boolean readEntitiesSection();

  Standard_Boolean readIgnoredSection();

  Standard_Boolean readLayerTable();

  Standard_Boolean readIgnoredTable();

  Standard_Boolean readUnits();

  Standard_Boolean readLayer();

  Standard_Boolean readEntity();

  Standard_Boolean readLine();

  Standard_Boolean readText();

  Standard_Boolean readArc();

  Standard_Boolean readCircle();

  Standard_Boolean readEllipse();

  Standard_Boolean readPoint();

  Standard_Boolean readSpline();

  Standard_Boolean readLWPolyline();

  Standard_Boolean readPolyline();

  Standard_Boolean readMultiLeader();

  Standard_Boolean readInsert();

  Standard_Boolean readDimension();

  Standard_Boolean readUnknownEntity();

  Standard_Boolean readBlockInfo();

  Standard_Boolean readBlockVersion();

  Standard_Boolean readDWGCodePage();

private:
};

#endif
