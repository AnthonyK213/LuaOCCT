#include <lenums.h>

#include <NCollection_BaseMap.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopTools_MapOfShape.hxx>

void luaocct_init_Map(lua_State *L) {
  luabridge::getGlobalNamespace(L)
      .beginNamespace("LuaOCCT")
      .beginNamespace("TopTools")

      .beginClass<NCollection_BaseMap>("NCollection_BaseMap")
      .addFunction("NbBuckets", &NCollection_BaseMap::NbBuckets)
      .addFunction("Extent", &NCollection_BaseMap::Extent)
      .addFunction("IsEmpty", &NCollection_BaseMap::IsEmpty)
      .endClass()

      .deriveClass<TopTools_IndexedDataMapOfShapeListOfShape,
                   NCollection_BaseMap>(
          "TopTools_IndexedDataMapOfShapeListOfShape")
      .addConstructor<void(),
                      void(const TopTools_IndexedDataMapOfShapeListOfShape &)>()
      .endClass()

      .deriveClass<TopTools_IndexedMapOfShape, NCollection_BaseMap>(
          "TopTools_IndexedMapOfShape")
      .addConstructor<void(), void(const TopTools_IndexedMapOfShape &)>()
      .endClass()

      .deriveClass<TopTools_MapOfShape, NCollection_BaseMap>(
          "TopTools_MapOfShape")
      .addConstructor<void(), void(const TopTools_MapOfShape &)>()
      .endClass()

      .endNamespace()
      .endNamespace();
}
