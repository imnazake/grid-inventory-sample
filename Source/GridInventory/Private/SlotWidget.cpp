// Copyright (C) Neoxyne. All Rights Reserved.

#include "SlotWidget.h"
#include "CellWidget.h"
#include "DraggedSlotWidget.h"
#include "GridWidget.h"
#include "Item.h"
#include "Slot_DragDropOperation.h"

USlotWidget::USlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void USlotWidget::SetData(const FSlot& NewData, UGridWidget* NewParentWidget)
{
	SlotData = NewData;
	ParentWidget = NewParentWidget;
	OnDataReceived();
}

void USlotWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void USlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

void USlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

bool USlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bDroppedSomething = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bDroppedSomething |= true;

	return bDroppedSomething;
}
