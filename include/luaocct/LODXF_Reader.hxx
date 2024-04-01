#ifndef _LuaOCCT_LODXF_Reader_HeaderFile
#define _LuaOCCT_LODXF_Reader_HeaderFile

#include <Geom_Line.hxx>
#include <IFSelect_ReturnStatus.hxx>
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
  LODXF_Version_Unknown,
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
  LODXF_Reader();

  IFSelect_ReturnStatus ReadFile(const Standard_CString theFileName);

private:
private:
};

#endif
