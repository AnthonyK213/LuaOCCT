#include <luaocct/LOUtil_AIS.hxx>

std::vector<Handle(AIS_InteractiveObject)>
LOUtil_AIS::GetSelections(const Handle(AIS_InteractiveContext) & theCtx) {
  std::vector<Handle(AIS_InteractiveObject)> aResult{};
  aResult.reserve(theCtx->NbSelected());

  for (theCtx->InitSelected(); theCtx->MoreSelected(); theCtx->NextSelected()) {
    aResult.push_back(theCtx->SelectedInteractive());
  }

  return aResult;
}
