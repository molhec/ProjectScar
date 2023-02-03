// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractuableTrigger.h"

// Sets default values
AInteractuableTrigger::AInteractuableTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMesh->SetupAttachment(Root);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AInteractuableTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractuableTrigger::Interact(AActor* Caller)
{
	PlayerCharacterRef = Cast<APlayerCharacter>(Caller);
}

void AInteractuableTrigger::StartFocus()
{

}

void AInteractuableTrigger::EndFocus()
{

}

// Called every frame
void AInteractuableTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

