// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void UDialogWidget::SetDialog(FString Message)
{
	DialogText->SetText(FText::FromString(Message));
}

void UDialogWidget::SetSliderValue(float NewValue)
{
	Slider->SetValue(NewValue);
}

void UDialogWidget::SetDialogPanelVisibility(bool NewValue)
{
	if(NewValue)
		DialogPanel->SetVisibility(ESlateVisibility::Visible);
	else
		DialogPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogWidget::ShowFlashback(UTexture2D* Texture, AController* ControllerToPauseMovement)
{
	FlashbackPanel->SetVisibility(ESlateVisibility::Visible);
	FlashbackImage->SetBrushFromTexture(Texture, true);

	ControllerToStopMovement = ControllerToPauseMovement;

	if(ControllerToStopMovement != nullptr)
	{
		ControllerToStopMovement->SetIgnoreMoveInput(true);
		ControllerToStopMovement->SetIgnoreLookInput(true);
	}

	FWidgetAnimationDynamicEvent HideEvent;
	HideEvent.BindDynamic(this, &UDialogWidget::HideFlashback);

	PlayAnimation(FadeFlashback, 0, 1, EUMGSequencePlayMode::Forward, 1);
	BindToAnimationFinished(FadeFlashback, HideEvent);
}

void UDialogWidget::HideFlashback()
{
	FlashbackPanel->SetVisibility(ESlateVisibility::Hidden);

	if(ControllerToStopMovement != nullptr)
	{
		ControllerToStopMovement->SetIgnoreMoveInput(false);
		ControllerToStopMovement->SetIgnoreLookInput(false);
	}
}

void UDialogWidget::ShowInteraction()
{
	InteractionPanel->SetVisibility(ESlateVisibility::Visible);
}

void UDialogWidget::HideInteraction()
{
	InteractionPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
