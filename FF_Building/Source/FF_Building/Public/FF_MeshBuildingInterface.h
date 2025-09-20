//Plugin provided by Flying Fox Ent.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "FF_MeshBuildingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFF_MeshBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IFF_MeshBuildingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void DestroyBuild() = 0;
	
};
