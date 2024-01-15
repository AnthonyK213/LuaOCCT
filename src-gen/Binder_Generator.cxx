#include "Binder_Generator.hxx"
#include "Binder_Module.hxx"

Binder_Generator::Binder_Generator() : myCurMod(nullptr) {}

Binder_Generator::~Binder_Generator() {}

#define MOD_CALL(F) myCurMod ? (myCurMod->F) : false

bool Binder_Generator::Parse() { return MOD_CALL(parse()); }

bool Binder_Generator::Generate(const std::string &theExportDir) {
  return MOD_CALL(generate());
}

int Binder_Generator::Save(const std::string &theFilePath) const {
  return MOD_CALL(save(theFilePath));
}

bool Binder_Generator::Load(const std::string &theFilePath) {
  return MOD_CALL(load(theFilePath));
}
