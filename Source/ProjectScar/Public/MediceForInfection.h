// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractuableTrigger.h"
#include "GameFramework/Actor.h"
#include "MediceForInfection.generated.h"

UCLASS()
class PROJECTSCAR_API AMediceForInfection : public AInteractuableTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMediceForInfection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactions)
	float InfectionValueToCure;

	bool bPickedUp;

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
