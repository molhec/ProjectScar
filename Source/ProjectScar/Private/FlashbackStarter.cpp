// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashbackStarter.h"

// Sets default values
AFlashbackStarter::AFlashbackStarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlashbackStarter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlashbackStarter::Interact(AActor* Caller)
{
	Super::Interact(Caller);
	
	PlayerCharacterRef = Cast<APlayerCharacter>(Caller);
	
	if(PlayerCharacterRef != nullptr)
		PlayerCharacterRef->ShowFlashback(TextureToShowFlashback);
}

void AFlashbackStarter::StartFocus()
{
	Super::StartFocus();
}

void AFlashbackStarter::EndFocus()
{
	Super::EndFocus();
}

// Called every frame
void AFlashbackStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

