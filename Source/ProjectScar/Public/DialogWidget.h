// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSCAR_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* DialogText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class USlider* Slider;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* DialogPanel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UCanvasPanel* FlashbackPanel;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* FlashbackImage;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeFlashback;

	UFUNCTION()
	void SetDialog(FString Message);

	UFUNCTION()
	void SetSliderValue(float NewValue);

	UFUNCTION()
	void SetDialogPanelVisibility(bool NewValue);

	UFUNCTION()
	void ShowFlashback(UTexture2D* Texture, AController* ControllerToPauseMovement = nullptr);

	UFUNCTION()
	void HideFlashback();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFlashbackFadeAnimation();

	AController* ControllerToStopMovement;

protected:
	virtual void NativeConstruct() override;
};
