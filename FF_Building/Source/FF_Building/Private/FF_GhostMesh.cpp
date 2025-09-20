// Fill out your copyright notice in the Description page of Project Settings.


#include "FF_GhostMesh.h"


// Sets default values
AFF_GhostMesh::AFF_GhostMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Scene;
	Scene->SetMobility(EComponentMobility::Movable);

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("SM_Mesh");
	SM_Mesh->SetupAttachment(Scene);
	SM_Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AFF_GhostMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFF_GhostMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

