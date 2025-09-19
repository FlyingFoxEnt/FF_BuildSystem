//Plugin provided by Flying Fox Ent.

#include "FF_BuildingComponent.h"

// Sets default values for this component's properties
UFF_BuildingComponent::UFF_BuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true); // Ensures default replication
	// ...
}


// Called when the game starts
void UFF_BuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFF_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFF_BuildingComponent::SpawnBuilding(int BuildType, FTransform BuildTransfor)
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	// If the character has a CameraComponent
	if (UCameraComponent* Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>())
	{
		UE_LOG(LogTemp, Log, TEXT("Camera found: %s"), *Camera->GetName());
		// Store it if you need later
		FVector Start = Camera->GetComponentLocation();
            FVector ForwardVector = Camera->GetForwardVector();
            FVector End = Start + (ForwardVector * 1000.f); // 1000 units forward

            FHitResult HitResult;
            FCollisionQueryParams Params;
            Params.AddIgnoredActor(OwnerCharacter); // Ignore self

            bool bHit = GetWorld()->LineTraceSingleByChannel(
                HitResult,
                Start,
                End,
                ECC_Visibility,  // Trace channel (can use custom)
                Params
            );

            if (bHit)
            {
                UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());

                FVector SnappedLocation = FVector(
                    FMath::GridSnap(HitResult.Location.X, 100.f),
                    FMath::GridSnap(HitResult.Location.Y, 100.f),
                    FMath::GridSnap(HitResult.Location.Z, 100.f)
                );
            }

	}
}

void UFF_BuildingComponent::UpdateSelectMesh(int MeshIndex)
{
    SERVER_SelectMesh(MeshIndex);
}

void UFF_BuildingComponent::SERVER_SelectMesh_Implementation(int MeshIndex)
{
    if (SelectedMeshIndex + MeshIndex > 6)
        SelectedMeshIndex = 0;
    else if (SelectedMeshIndex + MeshIndex < 0)
        SelectedMeshIndex = 6;
    else
        SelectedMeshIndex = FMath::Clamp(MeshIndex + SelectedMeshIndex, 0, 6);
}

bool UFF_BuildingComponent::ServerSpawnBuilding_Validate(int BuildType, FTransform BuildTransfor)
{
    return true;
}

void UFF_BuildingComponent::ServerSpawnBuilding_Implementation(int BuildType, FTransform BuildTransfor)
{
}

void UFF_BuildingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Register variable for replication
    DOREPLIFETIME(UFF_BuildingComponent, SelectedMeshIndex);
}

