// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/DialogStarter.h"

// Sets default values
ADialogStarter::ADialogStarter()
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
void ADialogStarter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADialogStarter::Interact(AActor* Caller)
{
	IIInteractable::Interact(Caller);

	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, TEXT("Interaction Successfull"), true);
}

void ADialogStarter::StartFocus()
{
	IIInteractable::StartFocus();
}

void ADialogStarter::EndFocus()
{
	IIInteractable::EndFocus();
}

// Called every frame
void ADialogStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

