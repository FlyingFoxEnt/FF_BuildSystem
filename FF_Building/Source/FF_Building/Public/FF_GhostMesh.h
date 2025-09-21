// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FF_GhostMesh.generated.h"

UCLASS()
class FF_BUILDING_API AFF_GhostMesh : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFF_GhostMesh();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Build Mesh Properties")
	class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Build Mesh Properties")
	class UStaticMeshComponent* SM_Mesh;

	UFUNCTION(BlueprintCallable, Category = "FF Building|Functions")
	void updateGhostMesh(UStaticMesh* NewMesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
