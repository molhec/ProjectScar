// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractuableTrigger.h"
#include "PlayerCharacter.h"
#include "DialogStarter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS()
class PROJECTSCAR_API ADialogStarter : public AInteractuableTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogStarter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interactions)
	TArray<FString> DialogsToShow;

	UPROPERTY(BlueprintAssignable, Category=CustomEvents)
	FTriggerDelegate OnTriggerAction;

	int CurrentDialogIndex;


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
