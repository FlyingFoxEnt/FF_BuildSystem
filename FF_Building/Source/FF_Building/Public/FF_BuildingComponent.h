//Plugin provided by Flying Fox Ent.

#pragma once

#include "CoreMinimal.h"
#include "Math/Vector.h"
#include "Engine/World.h"
#include "FF_GhostMesh.h"
#include "FF_BuildingActor.h"
#include "DrawDebugHelpers.h"
#include "Net/UnrealNetwork.h"
#include "Math/UnrealMathUtility.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "FF_MeshBuildingInterface.h"
#include "Components/ActorComponent.h"
#include "FF_BuildingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FF_BUILDING_API UFF_BuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFF_BuildingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "FF Building|Functions")
	void SpawnBuilding(int BuildType);
	
	UFUNCTION(Server, Reliable)
	void ServerSpawnBuilding(int BuildType, FTransform BuildTransfor);

	UFUNCTION(BlueprintCallable, Category = "FF Building|Functions")
	void UpdateSelectMesh(int MeshIndex);
	
	UFUNCTION(BlueprintCallable, Category = "FF Building|Functions")
	void RotateMesh(FRotator Rotation);

	UFUNCTION(Server, Unreliable)
	void SERVER_SelectMesh(int MeshIndex);

	UFUNCTION(BlueprintCallable, Category = "FF Building|Function")
	void UpdateGhostMesh();

	UFUNCTION(BlueprintCallable, Category = "FF Building|Function")
	void DestroyMesh();
	
	ACharacter* OwnerCharacter;

	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Replicated, BlueprintReadOnly, Category = "FF Building|Properties")
	int SelectedMeshIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FF Building|Properties")
	FRotator CurrentRotation;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "FF Building|Properties")
	TSubclassOf<AFF_BuildingActor> BuildingClass;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
