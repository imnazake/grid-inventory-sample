// Fill out your copyright notice in the Description page of Project Settings.

#include "SlotWidget.h"

USlotWidget::USlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void USlotWidget::SetData(const FSlot& NewData)
{
	SlotData = NewData;
	OnDataReceived();
}
