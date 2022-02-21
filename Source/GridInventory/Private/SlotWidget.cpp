// Copyright (C) Neoxyne. All Rights Reserved.

#include "SlotWidget.h"

USlotWidget::USlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void USlotWidget::SetData(const FSlot& NewData)
{
	SlotData = NewData;
	OnDataReceived();
}
