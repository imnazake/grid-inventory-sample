// Fill out your copyright notice in the Description page of Project Settings.

#include "DraggedSlotWidget.h"
#include "InventoryComponent.h"
#include "Item.h"

UDraggedSlotWidget::UDraggedSlotWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UDraggedSlotWidget::SetData(const FSlot& NewData, const float InCellSize)
{
	SlotData = NewData;
	CellSize = InCellSize;

	OnDataReceived();
	SetSlotSize(CellSize);

	if (!SlotData.Item->OnItemSizeChanged.IsBoundToObject(this))
	{
		SlotData.Item->OnItemSizeChanged.AddUObject(this, &ThisClass::OnItemSizeChanged);
	}
}
