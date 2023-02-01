// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogWidget.h"

#include "Components/TextBlock.h"


void UDialogWidget::SetDialog(FString Message)
{
	DialogText->SetText(FText::FromString(Message));
}
