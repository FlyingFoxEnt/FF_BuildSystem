//Plugin provided by Flying Fox Ent.

#include "FF_Building.h"

#define LOCTEXT_NAMESPACE "FFF_BuildingModule"

void FFF_BuildingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FFF_BuildingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFF_BuildingModule, FF_Building)