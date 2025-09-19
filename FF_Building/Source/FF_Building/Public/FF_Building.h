//Plugin provided by Flying Fox Ent.

#pragma once

#include "Modules/ModuleManager.h"

class FFF_BuildingModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
