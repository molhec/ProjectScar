// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RunsManager.generated.h"

USTRUCT(BlueprintType)
struct FRunObjects
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RunObjects")
	TArray<AActor*> ObjectsForTheRun;
};

UCLASS()
class PROJECTSCAR_API ARunsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARunsManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Runs)
	int CurrentRunIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RunObjects")
	TArray<AActor*> AllObjectsAffectedByRuns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Runs)
	TArray<FRunObjects> Runs;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateRunWithIndex(int Index);

	UFUNCTION(BlueprintCallable)
	void NextRun();

	void DeactivateActor(AActor* ActorToDeactivate);
	void ActivateActor(AActor* ActorToActivate);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
