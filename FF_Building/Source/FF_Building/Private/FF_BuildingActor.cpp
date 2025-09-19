//Plugin provided by Flying Fox Ent.


#include "FF_BuildingActor.h"


// Sets default values
AFF_BuildingActor::AFF_BuildingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	Scene = CreateDefaultSubobject<USceneComponent>("Root Component");
	SM_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("SM_Mesh");
	RootComponent = Scene;

	Scene->SetMobility(EComponentMobility::Movable);

	SM_Mesh->SetupAttachment(Scene);
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

void AFF_BuildingActor::SERVER_SetBuildType_Implementation(int BuildTypeIndex)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	OwnerCharacter->FindComponentByClass<UFF_BuildingComponent>()->SelectedMeshIndex = BuildTypeIndex;
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