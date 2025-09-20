# FF_BuildSystem
A basic replicated build system in a UE5 plugin made to be "plug and play"
The goal of this plugin is to be easily implemented into any project using a character pawn.

## How it work?
Here the following inner-working of the plugin :

### [UActorComponent | UFF_BuildingComponent](FF_Building/Source/FF_Building/Private/FF_BuildingComponent.cpp): The actor component managing the Static Mesh list & the spawning of meshs.
### [AActor | AFF_BuildingActor](FF_Building/Source/FF_Building/Private/FF_BuildingActor.cpp): The actor reponsible for the building mesh.

### [UActorComponent | UFF_BuildingComponent](FF_Building/Source/FF_Building/Private/FF_MeshBuildingInterface.cpp): The interface for the interact functionalities of the building meshs.

### [AActor | AFF_GhostMesh](FF_Building/Source/FF_Building/Private/FF_GhostMesh.cpp): The actor reponsible for the ghost placement preview.
WIP

## How to use ? 

For now you just need to add the "FF_Building" component to your character and create a Blueprint Actor child of "AFF_BuildingActor" and set the differents functions for the inputs in your character actor, and everything should be ready to be used.

WIP

