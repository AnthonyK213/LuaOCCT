#include "lBRepBuilderAPI.h"

void luaocc_init_BRepBuilderAPI(lua_State *L) {
  LuaBridge__G(L)
      .Begin_Namespace1(BRepBuilderAPI)

      .Begin_Namespace(BRepBuilderAPI_EdgeError)
      .Bind_Enum(BRepBuilderAPI_EdgeError, BRepBuilderAPI_EdgeDone)
      .Bind_Enum(BRepBuilderAPI_EdgeError, BRepBuilderAPI_PointProjectionFailed)
      .Bind_Enum(BRepBuilderAPI_EdgeError, BRepBuilderAPI_ParameterOutOfRange)
      .Bind_Enum(BRepBuilderAPI_EdgeError,
                 BRepBuilderAPI_DifferentPointsOnClosedCurve)
      .Bind_Enum(BRepBuilderAPI_EdgeError,
                 BRepBuilderAPI_PointWithInfiniteParameter)
      .Bind_Enum(BRepBuilderAPI_EdgeError,
                 BRepBuilderAPI_DifferentsPointAndParameter)
      .Bind_Enum(BRepBuilderAPI_EdgeError,
                 BRepBuilderAPI_LineThroughIdenticPoints)
      .End_Namespace()

      .Begin_Namespace(BRepBuilderAPI_WireError)
      .Bind_Enum(BRepBuilderAPI_WireError, BRepBuilderAPI_WireDone)
      .Bind_Enum(BRepBuilderAPI_WireError, BRepBuilderAPI_EmptyWire)
      .Bind_Enum(BRepBuilderAPI_WireError, BRepBuilderAPI_DisconnectedWire)
      .Bind_Enum(BRepBuilderAPI_WireError, BRepBuilderAPI_NonManifoldWire)
      .End_Namespace()

      .Begin_Namespace(BRepBuilderAPI_FaceError)
      .Bind_Enum(BRepBuilderAPI_FaceError, BRepBuilderAPI_FaceDone)
      .Bind_Enum(BRepBuilderAPI_FaceError, BRepBuilderAPI_NoFace)
      .Bind_Enum(BRepBuilderAPI_FaceError, BRepBuilderAPI_NotPlanar)
      .Bind_Enum(BRepBuilderAPI_FaceError, BRepBuilderAPI_CurveProjectionFailed)
      .Bind_Enum(BRepBuilderAPI_FaceError, BRepBuilderAPI_ParametersOutOfRange)
      .End_Namespace()

      .Begin_Namespace(BRepBuilderAPI_ShellError)
      .Bind_Enum(BRepBuilderAPI_ShellError, BRepBuilderAPI_ShellDone)
      .Bind_Enum(BRepBuilderAPI_ShellError, BRepBuilderAPI_EmptyShell)
      .Bind_Enum(BRepBuilderAPI_ShellError, BRepBuilderAPI_DisconnectedShell)
      .Bind_Enum(BRepBuilderAPI_ShellError,
                 BRepBuilderAPI_ShellParametersOutOfRange)
      .End_Namespace()

      .Begin_Class(BRepBuilderAPI)
      .addStaticFunction("Plane",
                         luabridge::overload<const Handle(Geom_Plane) &>(
                             &BRepBuilderAPI::Plane),
                         luabridge::overload<>(&BRepBuilderAPI::Plane))
      .addStaticFunction(
          "Precision",
          luabridge::overload<const Standard_Real>(&BRepBuilderAPI::Precision),
          luabridge::overload<>(&BRepBuilderAPI::Precision))
      .End_Class()

      .Begin_Class(BRepBuilderAPI_Command)
      .Bind_Method(BRepBuilderAPI_Command, IsDone)
      .Bind_Method(BRepBuilderAPI_Command, Check)
      .End_Class()

      .Begin_Derive(BRepBuilderAPI_MakeShape, BRepBuilderAPI_Command)
      .Bind_Method(BRepBuilderAPI_MakeShape, Build)
      .Bind_Method(BRepBuilderAPI_MakeShape, Shape)
      .Bind_Method(BRepBuilderAPI_MakeShape, Generated)
      .Bind_Method(BRepBuilderAPI_MakeShape, Modified)
      .Bind_Method(BRepBuilderAPI_MakeShape, IsDeleted)
      .End_Derive()

      .Begin_Derive(BRepBuilderAPI_MakeVertex, BRepBuilderAPI_MakeShape)
      .addConstructor<void(const gp_Pnt &)>()
      .Bind_Method(BRepBuilderAPI_MakeVertex, Vertex)
      .End_Derive()

      .Begin_Derive(BRepBuilderAPI_MakeEdge, BRepBuilderAPI_MakeShape)
      .addConstructor<
          void(), void(const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const gp_Pnt &, const gp_Pnt &), void(const gp_Lin &),
          void(const gp_Lin &, const Standard_Real, const Standard_Real),
          void(const gp_Lin &, const gp_Pnt &, const gp_Pnt &),
          void(const gp_Lin &, const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const gp_Circ &),
          void(const gp_Circ &, const Standard_Real, const Standard_Real),
          void(const gp_Circ &, const gp_Pnt &, const gp_Pnt &),
          void(const gp_Circ &, const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const gp_Elips &),
          void(const gp_Elips &, const Standard_Real, const Standard_Real),
          void(const gp_Elips &, const gp_Pnt &, const gp_Pnt &),
          void(const gp_Elips &, const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const gp_Hypr &),
          void(const gp_Hypr &, const Standard_Real, const Standard_Real),
          void(const gp_Hypr &, const gp_Pnt &, const gp_Pnt &),
          void(const gp_Hypr &, const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const gp_Parab &),
          void(const gp_Parab &, const Standard_Real, const Standard_Real),
          void(const gp_Parab &, const gp_Pnt &, const gp_Pnt &),
          void(const gp_Parab &, const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const Handle(Geom_Curve) &),
          void(const Handle(Geom_Curve) &, const Standard_Real,
               const Standard_Real),
          void(const Handle(Geom_Curve) &, const gp_Pnt &, const gp_Pnt &),
          void(const Handle(Geom_Curve) &, const TopoDS_Vertex &,
               const TopoDS_Vertex &),
          void(const Handle(Geom_Curve) &, const gp_Pnt &, const gp_Pnt &,
               const Standard_Real, const Standard_Real),
          void(const Handle(Geom_Curve) &, const TopoDS_Vertex &,
               const TopoDS_Vertex &, const Standard_Real, const Standard_Real),
          void(const Handle(Geom2d_Curve) &, const Handle(Geom_Surface) &),
          void(const Handle(Geom2d_Curve) &, const Handle(Geom_Surface) &,
               const Standard_Real, const Standard_Real),
          void(const Handle(Geom2d_Curve) &, const Handle(Geom_Surface) &,
               const gp_Pnt &, const gp_Pnt &),
          void(const Handle(Geom2d_Curve) &, const Handle(Geom_Surface) &,
               const TopoDS_Vertex &, const TopoDS_Vertex &),
          void(const Handle(Geom2d_Curve) &, const Handle(Geom_Surface) &,
               const gp_Pnt &, const gp_Pnt &, const Standard_Real,
               const Standard_Real),
          void(const Handle(Geom2d_Curve) &, const Handle(Geom_Surface) &,
               const TopoDS_Vertex &, const TopoDS_Vertex &,
               const Standard_Real, const Standard_Real)>()
      .addFunction(
          "Init",
          luabridge::overload<const Handle(Geom_Curve) &>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom_Curve) &, const Standard_Real,
                              const Standard_Real>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom_Curve) &, const gp_Pnt &,
                              const gp_Pnt &>(&BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom_Curve) &, const TopoDS_Vertex &,
                              const TopoDS_Vertex &>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom_Curve) &, const gp_Pnt &,
                              const gp_Pnt &, const Standard_Real,
                              const Standard_Real>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom_Curve) &, const TopoDS_Vertex &,
                              const TopoDS_Vertex &, const Standard_Real,
                              const Standard_Real>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom2d_Curve) &,
                              const Handle(Geom_Surface) &>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom2d_Curve) &,
                              const Handle(Geom_Surface) &, const Standard_Real,
                              const Standard_Real>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom2d_Curve) &,
                              const Handle(Geom_Surface) &, const gp_Pnt &,
                              const gp_Pnt &>(&BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom2d_Curve) &,
                              const Handle(Geom_Surface) &,
                              const TopoDS_Vertex &, const TopoDS_Vertex &>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom2d_Curve) &,
                              const Handle(Geom_Surface) &, const gp_Pnt &,
                              const gp_Pnt &, const Standard_Real,
                              const Standard_Real>(
              &BRepBuilderAPI_MakeEdge::Init),
          luabridge::overload<const Handle(Geom2d_Curve) &,
                              const Handle(Geom_Surface) &,
                              const TopoDS_Vertex &, const TopoDS_Vertex &,
                              const Standard_Real, const Standard_Real>(
              &BRepBuilderAPI_MakeEdge::Init))
      .Bind_Property_Readonly(BRepBuilderAPI_MakeEdge, Error)
      .Bind_Method(BRepBuilderAPI_MakeEdge, Edge)
      .Bind_Method(BRepBuilderAPI_MakeEdge, Vertex1)
      .Bind_Method(BRepBuilderAPI_MakeEdge, Vertex2)
      .End_Derive()

      .Begin_Derive(BRepBuilderAPI_MakeWire, BRepBuilderAPI_MakeShape)
      .addConstructor<void(), void(const TopoDS_Edge &),
                      void(const TopoDS_Edge &, const TopoDS_Edge &),
                      void(const TopoDS_Edge &, const TopoDS_Edge &,
                           const TopoDS_Edge &),
                      void(const TopoDS_Edge &, const TopoDS_Edge &,
                           const TopoDS_Edge &, const TopoDS_Edge &),
                      void(const TopoDS_Wire &),
                      void(const TopoDS_Wire &, const TopoDS_Edge &)>()
      .addFunction("Add",
                   luabridge::overload<const TopoDS_Edge &>(
                       &BRepBuilderAPI_MakeWire::Add),
                   luabridge::overload<const TopoDS_Wire &>(
                       &BRepBuilderAPI_MakeWire::Add))
      .Bind_Property_Readonly(BRepBuilderAPI_MakeWire, Error)
      .Bind_Method(BRepBuilderAPI_MakeWire, Wire)
      .Bind_Method(BRepBuilderAPI_MakeWire, Edge)
      .Bind_Method(BRepBuilderAPI_MakeWire, Vertex)
      .End_Derive()

      .Begin_Derive(BRepBuilderAPI_MakeFace, BRepBuilderAPI_MakeShape)
      .addConstructor<
          void(), void(const TopoDS_Face &), void(const gp_Pln &),
          void(const gp_Cylinder &), void(const gp_Cone &),
          void(const gp_Sphere &), void(const gp_Torus &),
          void(const Handle(Geom_Surface) &, const Standard_Real),
          void(const gp_Pln &, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real),
          void(const gp_Cylinder &, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real),
          void(const gp_Cone &, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real),
          void(const gp_Sphere &, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real),
          void(const gp_Torus &, const Standard_Real, const Standard_Real,
               const Standard_Real, const Standard_Real),
          void(const Handle(Geom_Surface) &, const Standard_Real,
               const Standard_Real, const Standard_Real, const Standard_Real,
               const Standard_Real),
          void(const TopoDS_Wire &, Standard_Boolean),
          void(const gp_Pln &, const TopoDS_Wire &, Standard_Boolean),
          void(const gp_Cylinder &, const TopoDS_Wire &, Standard_Boolean),
          void(const gp_Cone &, const TopoDS_Wire &, Standard_Boolean),
          void(const gp_Sphere &, const TopoDS_Wire &, Standard_Boolean),
          void(const gp_Torus &, const TopoDS_Wire &, Standard_Boolean),
          void(const Handle(Geom_Surface) &, const TopoDS_Wire &,
               Standard_Boolean),
          void(const TopoDS_Face &, const TopoDS_Wire &)>()
      .addFunction(
          "Init",
          luabridge::overload<const TopoDS_Face &>(
              &BRepBuilderAPI_MakeFace::Init),
          luabridge::overload<const Handle(Geom_Surface) &,
                              const Standard_Boolean, const Standard_Real>(
              &BRepBuilderAPI_MakeFace::Init),
          luabridge::overload<const Handle(Geom_Surface) &, const Standard_Real,
                              const Standard_Real, const Standard_Real,
                              const Standard_Real, const Standard_Real>(
              &BRepBuilderAPI_MakeFace::Init))
      .Bind_Method(BRepBuilderAPI_MakeFace, Add)
      .Bind_Property_Readonly(BRepBuilderAPI_MakeFace, Error)
      .Bind_Method(BRepBuilderAPI_MakeFace, Face)
      .End_Derive()

      .Begin_Derive(BRepBuilderAPI_MakeShell, BRepBuilderAPI_MakeShape)
      .addConstructor<
          void(), void(const Handle(Geom_Surface) &, const Standard_Boolean),
          void(const Handle(Geom_Surface) &, const Standard_Real,
               const Standard_Real, const Standard_Real, const Standard_Real,
               const Standard_Boolean)>()
      .Bind_Property_Readonly(BRepBuilderAPI_MakeShell, Error)
      .Bind_Method(BRepBuilderAPI_MakeShell, Shell)
      .End_Derive()

      .Begin_Derive(BRepBuilderAPI_MakeSolid, BRepBuilderAPI_MakeShape)
      .addConstructor<void(), void(const TopoDS_CompSolid &),
                      void(const TopoDS_Shell &),
                      void(const TopoDS_Shell &, const TopoDS_Shell &),
                      void(const TopoDS_Shell &, const TopoDS_Shell &,
                           const TopoDS_Shell &),
                      void(const TopoDS_Solid &),
                      void(const TopoDS_Solid &, const TopoDS_Shell &)>()
      .Bind_Method(BRepBuilderAPI_MakeSolid, Add)
      .Bind_Method(BRepBuilderAPI_MakeSolid, Solid)
      .End_Derive()

      .End_Namespace1();
}
