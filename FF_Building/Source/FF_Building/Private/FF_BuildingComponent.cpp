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
    OwnerCharacter = Cast<ACharacter>(GetOwner());
    Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();
}


// Called every frame
void UFF_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (GetOwner()->GetLocalRole() < ROLE_Authority) // ROLE_AutonomousProxy or ROLE_SimulatedProxy
    {
        //UpdateGhostMesh();
    }
    else
    {
        // We are on the server (authority)
    }
}

void UFF_BuildingComponent::SpawnBuilding(int BuildType)
{

	// If the character has a CameraComponent

    UE_LOG(LogTemp, Log, TEXT("Client Trying to spawn building"));
	if (Camera)
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
                    FMath::GridSnap(HitResult.Location.X, 200.f),
                    FMath::GridSnap(HitResult.Location.Y, 200.f),
                    FMath::GridSnap(HitResult.Location.Z, 200.f)
                );

				ServerSpawnBuilding(SelectedMeshIndex, FTransform(CurrentRotation, SnappedLocation));
            }

	}
}



void UFF_BuildingComponent::RotateMesh(FRotator Rotation)
{
    if(CurrentRotation.Yaw + Rotation.Yaw > 360.f)
        CurrentRotation = FRotator(0.f, 0.f, 0.f);
	else
	CurrentRotation += Rotation;
}

void UFF_BuildingComponent::UpdateGhostMesh()
{
    if (Camera == nullptr || OwnerCharacter == nullptr) 
    {
        UE_LOG(LogTemp, Log, TEXT("Ghost Not Valid can't update"));
        //return;
    }
}

void UFF_BuildingComponent::DestroyMesh()
{
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
        IFF_MeshBuildingInterface* MeshInterface = Cast<IFF_MeshBuildingInterface>(HitResult.GetActor());
        if (MeshInterface)
        {
            MeshInterface->DestroyBuild();
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

void UFF_BuildingComponent::ServerSpawnBuilding_Implementation(int BuildType, FTransform BuildTransform)
{
    if (!GetOwner() || !GetWorld())
    {
        return;
    }
    TArray<AActor*> BuildingActorsArray;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFF_BuildingActor::StaticClass(), BuildingActorsArray);
	float MinDistance;
	FVector ActorLocation = GetOwner()->GetActorLocation();
	AActor* NearestBuilding = UGameplayStatics::FindNearestActor(GetOwner()->GetActorLocation(), BuildingActorsArray, MinDistance);


    if (BuildingClass && MinDistance > 150.0f)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = GetOwner();
        SpawnParams.Instigator = Cast<APawn>(GetOwner());

        // Spawn on the server
        AFF_BuildingActor* NewBuilding = GetWorld()->SpawnActor<AFF_BuildingActor>(BuildingClass, BuildTransform, SpawnParams);

        if (NewBuilding)
        {
            UE_LOG(LogTemp, Log, TEXT("Spawned building"));
            UE_LOG(LogTemp, Log, TEXT("Building Type: %i"), SelectedMeshIndex);
            NewBuilding->SERVER_SetBuildType(SelectedMeshIndex);
        }
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Client can't spawn Mesh here."));
    }
}

void UFF_BuildingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    // Register variable for replication
    DOREPLIFETIME(UFF_BuildingComponent, SelectedMeshIndex);
}

