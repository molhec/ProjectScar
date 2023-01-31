// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DialogStarter.generated.h"

UCLASS()
class PROJECTSCAR_API ADialogStarter : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogStarter();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;


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