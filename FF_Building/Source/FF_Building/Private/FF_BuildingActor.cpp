//Plugin provided by Flying Fox Ent.


#include "FF_BuildingActor.h"


// Sets default values
AFF_BuildingActor::AFF_BuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;  
	SetNetUpdateFrequency(15.f);
		SetMinNetUpdateFrequency(2.f);

	Scene = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Scene;
	Scene->SetMobility(EComponentMobility::Movable);

	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("SM_Mesh");
	SM_Mesh->SetupAttachment(Scene);
	SM_Mesh->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AFF_BuildingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFF_BuildingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFF_BuildingActor::DestroyBuild()
{
	UE_LOG(LogTemp, Log, TEXT("CLIENT : Destroy Mesh"));
	SERVER_DestroyBuild();
	Destroy();
}

void AFF_BuildingActor::SERVER_DestroyBuild_Implementation()
{
	Destroy();
	UE_LOG(LogTemp, Log, TEXT("SERVER : Destroy Mesh"));
}

void AFF_BuildingActor::SERVER_SetBuildType_Implementation(int BuildTypeIndex)
{
	if (MeshArray.IsValidIndex(BuildTypeIndex))
	{
		SM_Mesh->SetStaticMesh(MeshArray[BuildTypeIndex]);
	}
}

bool AFF_BuildingActor::SERVER_SetBuildType_Validate(int BuildTypeIndex)
{
	if (BuildTypeIndex > 0 && BuildTypeIndex < 6)
	{
		return true;
	}
	return false;
}

void AFF_BuildingActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register variable for replication
	DOREPLIFETIME(AFF_BuildingActor, CurrentBuildType);
}