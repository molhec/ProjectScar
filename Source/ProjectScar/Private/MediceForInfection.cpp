// Fill out your copyright notice in the Description page of Project Settings.


#include "MediceForInfection.h"

// Sets default values
AMediceForInfection::AMediceForInfection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMediceForInfection::BeginPlay()
{
	Super::BeginPlay();

	bPickedUp = false;
}

void AMediceForInfection::Interact(AActor* Caller)
{
	Super::Interact(Caller);

	if(PlayerCharacterRef != nullptr && !bPickedUp)
	{
		PlayerCharacterRef->CureInfection(InfectionValueToCure);
		SetActorHiddenInGame(true);
		bPickedUp = true;
	}
}

void AMediceForInfection::StartFocus()
{
	Super::StartFocus();
}

void AMediceForInfection::EndFocus()
{
	Super::EndFocus();
}

// Called every frame
void AMediceForInfection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

