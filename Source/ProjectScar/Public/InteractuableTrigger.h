// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Interactables/IInteractable.h"
#include "InteractuableTrigger.generated.h"

UCLASS()
class PROJECTSCAR_API AInteractuableTrigger : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractuableTrigger();
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;
    
    UPROPERTY(EditDefaultsOnly)
    UBoxComponent* BoxComponent;
    
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;
	
	UPROPERTY()
	APlayerCharacter* PlayerCharacterRef;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact(AActor* Caller) override;

	virtual void StartFocus() override;

	virtual void EndFocus() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
