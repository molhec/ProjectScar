// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"

#include "Components/CanvasPanel.h"
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
