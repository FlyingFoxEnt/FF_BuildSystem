//Plugin provided by Flying Fox Ent.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "FF_MeshBuildingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UFF_MeshBuildingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FF_BUILDING_API IFF_MeshBuildingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Build Interface")
	void DestroyBuild();
	
};
