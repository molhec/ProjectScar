// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/DialogStarter.h"

#include "DialogWidget.h"
#include "PlayerCharacter.h"

// Sets default values
ADialogStarter::ADialogStarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADialogStarter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADialogStarter::Interact(AActor* Caller)
{
	Super::Interact(Caller);

	if(CurrentDialogIndex > DialogsToShow.Num() - 1)
	{
		CurrentDialogIndex = 0;

		if(PlayerCharacterRef != nullptr)
			PlayerCharacterRef->HideDialog();
		
		return;
	}

	if(PlayerCharacterRef != nullptr)
	{
		PlayerCharacterRef->ShowDialog(DialogsToShow[CurrentDialogIndex]);

		CurrentDialogIndex++;
	}
}

void ADialogStarter::StartFocus()
{
	Super::StartFocus();
}

void ADialogStarter::EndFocus()
{
	Super::EndFocus();

	CurrentDialogIndex = 0;
	if(PlayerCharacterRef != nullptr)
		PlayerCharacterRef->HideDialog();
	PlayerCharacterRef = nullptr;
}

// Called every frame
void ADialogStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

