// Copyright (C) Neoxyne. All Rights Reserved.

#include "DraggedSlotWidget.h"
#include "InventoryComponent.h"
#include "Item.h"

UDraggedSlotWidget::UDraggedSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDraggedSlotWidget::SetData(const FSlot NewData, const float InCellSize)
{
	// CopyItem = DuplicateObject(NewData.Item, NewData.Item->GetOuter());
	// CopyItem->OnConstruct();
	SlotData = NewData;
	CellSize = InCellSize;

	OnDataReceived();
	SetSlotSize(CellSize);

	if (!SlotData.Item->OnItemRotated.IsBoundToObject(this))
	{
		SlotData.Item->OnItemRotated.AddUObject(this, &ThisClass::OnItemRotated);
	}
}
