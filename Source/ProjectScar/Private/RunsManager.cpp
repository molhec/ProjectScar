// Fill out your copyright notice in the Description page of Project Settings.


#include "RunsManager.h"

#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"

// Sets default values
ARunsManager::ARunsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARunsManager::BeginPlay()
{
	Super::BeginPlay();

	UpdateRunWithIndex(CurrentRunIndex);
	
}

void ARunsManager::UpdateRunWithIndex(int Index)
{

	if(Index > Runs.Num() -1)
		return;
	
	// First Disable Object for Runs
	for (FRunObjects Run : Runs)
	{
		for (int i = 0; i < AllObjectsAffectedByRuns.Num(); i++)
		{
			for (UActorComponent* Component : AllObjectsAffectedByRuns[i]->GetComponents())
			{
				USceneComponent* scene = Cast<USceneComponent>(Component);
				UBoxComponent* boxCollider = Cast<UBoxComponent>(Component);
				UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(Component);

				if(scene != nullptr)
					scene->SetVisibility(false, true);
				if(boxCollider != nullptr)
					boxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				if(meshComponent != nullptr)
					meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			
			}

			TArray<AActor*> ChildrenOfCurrentActor;
			AllObjectsAffectedByRuns[i]->GetAllChildActors(ChildrenOfCurrentActor);

			for (AActor* Child : ChildrenOfCurrentActor)
			{
				DeactivateActor(Child);
			}

			DeactivateActor(AllObjectsAffectedByRuns[i]);
		}
	}

	// Then enable the objects but only for the desired Run
	
	for (int i = 0; i < Runs[Index].ObjectsForTheRun.Num(); i++)
	{
		for (UActorComponent* Component : Runs[Index].ObjectsForTheRun[i]->GetComponents())
		{
			USceneComponent* scene = Cast<USceneComponent>(Component);
			UBoxComponent* boxCollider = Cast<UBoxComponent>(Component);
			UStaticMeshComponent* meshComponent = Cast<UStaticMeshComponent>(Component);

			if(scene != nullptr)
				scene->SetVisibility(true, true);
			if(boxCollider != nullptr)
				boxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			if(meshComponent != nullptr)
				meshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

		TArray<AActor*> ChildrenOfCurrentActor;
		Runs[Index].ObjectsForTheRun[i]->GetAllChildActors(ChildrenOfCurrentActor);

		for (AActor* Child : ChildrenOfCurrentActor)
		{
			ActivateActor(Child);
		}

		ActivateActor(Runs[Index].ObjectsForTheRun[i]);
	}
}

void ARunsManager::NextRun()
{
	CurrentRunIndex++;
	UpdateRunWithIndex(CurrentRunIndex);
}

void ARunsManager::DeactivateActor(AActor* ActorToDeactivate)
{
	GEngine->AddOnScreenDebugMessage(-5, 1, FColor::Yellow, ActorToDeactivate->GetActorNameOrLabel());

	USceneComponent* scene = Cast<USceneComponent>(ActorToDeactivate);
	AStaticMeshActor* meshactor = Cast<AStaticMeshActor>(ActorToDeactivate);

	if(scene != nullptr)
		scene->SetVisibility(false, true);

	if(meshactor != nullptr)
		meshactor->SetActorEnableCollision(false);

	ActorToDeactivate->SetActorHiddenInGame(true);
	ActorToDeactivate->SetActorEnableCollision(false);
	ActorToDeactivate->SetActorTickEnabled(false); 
}

// Called every frame
void ARunsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARunsManager::ActivateActor(AActor* ActorToActivate)
{
	GEngine->AddOnScreenDebugMessage(-5, 1, FColor::Yellow, ActorToActivate->GetActorNameOrLabel());

	USceneComponent* scene = Cast<USceneComponent>(ActorToActivate);

	if(scene != nullptr)
		scene->SetVisibility(true, true);

	ActorToActivate->SetActorHiddenInGame(false);
	ActorToActivate->SetActorEnableCollision(true);
	ActorToActivate->SetActorTickEnabled(true); 
}

