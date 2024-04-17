#ifndef _LuaOCCT_mod_header_BRepTools_HeaderFile
#define _LuaOCCT_mod_header_BRepTools_HeaderFile

// clang-format off
#include <BRepTools.hxx>
#include <BRepTools_Modification.hxx>
#if (OCC_VERSION_MAJOR > 7 || (OCC_VERSION_MAJOR == 7 && OCC_VERSION_MINOR > 6))
#include <BRepTools_CopyModification.hxx>
#endif
#include <BRepTools_DataMapIteratorOfMapOfVertexPnt2d.hxx>
#include <BRepTools_GTrsfModification.hxx>
#include <BRepTools_History.hxx>
#include <BRepTools_MapOfVertexPnt2d.hxx>
#include <BRepTools_Modifier.hxx>
#include <BRepTools_NurbsConvertModification.hxx>
#include <BRepTools_PurgeLocations.hxx>
#include <BRepTools_Quilt.hxx>
#include <BRepTools_ReShape.hxx>
#include <BRepTools_ShapeSet.hxx>
#include <BRepTools_Substitution.hxx>
#include <BRepTools_TrsfModification.hxx>
#include <BRepTools_WireExplorer.hxx>
// clang-format on

#endif
