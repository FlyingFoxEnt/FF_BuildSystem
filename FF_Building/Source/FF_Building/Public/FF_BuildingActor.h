//Plugin provided by Flying Fox Ent.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "FF_MeshBuildingInterface.h"
#include "FF_BuildingActor.generated.h"

UCLASS()
class FF_BUILDING_API AFF_BuildingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFF_BuildingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Build Mesh Properties")
	class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Build Mesh Properties")
	class UStaticMeshComponent* SM_Mesh;
	

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Build Mesh Properties")
	int CurrentBuildType = 0;

	UFUNCTION(Server, Reliable, WithValidation, Category="Building Mesh Functions")
	void SERVER_SetBuildType(int BuildTypeIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FF Building|Properties")
	TArray<UStaticMesh*> MeshArray;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
