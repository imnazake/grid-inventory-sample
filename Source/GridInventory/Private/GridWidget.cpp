// Copyright (C) Neoxyne. All Rights Reserved.

#include "GridWidget.h"
#include "CellWidget.h"
#include "InventoryComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Item.h"
#include "SlotWidget.h"

UGridWidget::UGridWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UGridWidget::SetData(UInventoryComponent* NewInventory)
{
	Inventory = NewInventory;
	OnPrePopulateData();
	NativeOnDataReceived();
	OnDataReceived();
}

void UGridWidget::NativeOnDataReceived()
{
	if (!Inventory->OnInventoryUpdated.IsBoundToObject(this))
	{
		Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::NativeOnInventoryUpdated);
	}

	CellsWidgets.Empty();
	SlotsWidgets.Empty();

	for (const FPoint2D& Coordinates: Inventory->Cells)
	{
		UCellWidget* CellWidget = CreateWidget<UCellWidget>(GetOwningPlayer(), CellWidgetClass);
		check(CellWidget != nullptr);

		CellsWidgets.Add(CellWidget);
		CellWidget->SetData(Coordinates, Inventory->CellSize, this);
		CellWidget->SetCellSize(Inventory->CellSize);
		CellWidget->SetCellColor(CellWidget->DefaultCellColor);

		OnCellCreated(CellWidget);
	}

	for (const FSlot& Data: Inventory->Slots)
	{
		USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this);
		SlotWidget->SetSlotSize(Inventory->CellSize);

		OnSlotCreated(SlotWidget);
	}
}

void UGridWidget::NativeOnInventoryUpdated()
{
	for (USlotWidget* SlotWidget: SlotsWidgets)
	{
		OnSlotRemoved(SlotWidget);
	}

	SlotsWidgets.Empty();

	for (const FSlot& Data: Inventory->Slots)
	{
		USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this);
		SlotWidget->SetSlotSize(Inventory->CellSize);
		OnSlotCreated(SlotWidget);
	}
	
	OnInventoryUpdated();
}

int32 UGridWidget::GetCellIndex(const FPoint2D& InCoordinates)
{
	for (int32 Index = 0; Index < CellsWidgets.Num(); Index++)
	{
		if (CellsWidgets[Index]->Coordinates == InCoordinates)
		{
			return Index;
		}
	}

	return INDEX_NONE;
}
