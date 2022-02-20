// Fill out your copyright notice in the Description page of Project Settings.

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
	OnPreInitialize();
	NativeOnDataReceived();
	OnDataReceived();
}

void UGridWidget::NativeOnDataReceived()
{
	if (!Inventory->OnInventoryUpdated.IsBoundToObject(this))
	{
		Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::NativeOnInventoryUpdate);
	}

	CellsWidgets.Empty();
	SlotsWidgets.Empty();

	for (const FPoint2D& Coordinates: Inventory->Cells)
	{
		UCellWidget* CellWidget = CreateWidget<UCellWidget>(GetOwningPlayer(), CellWidgetClass);
		check(CellWidget != nullptr);

		CellsWidgets.Add(CellWidget);
		CellWidget->SetData(Coordinates, Inventory->CellSize);
		CellWidget->SetCellSize(Inventory->CellSize);
		CellWidget->SetCellColor(CellWidget->DefaultCellColor);

		OnCellCreated(CellWidget);
	}

	for (UCellWidget* CellWidget : CellsWidgets)
	{
		CellWidget->SetCellsWidgets(CellsWidgets);
	}

	for (const FSlot& Data: Inventory->Slots)
	{
		USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data);
		SlotWidget->SetSlotSize(Inventory->CellSize);

		OnSlotCreated(SlotWidget);
	}
}

void UGridWidget::NativeOnInventoryUpdate()
{
	OnPreUpdateInventory();

	SlotsWidgets.Empty();

	for (const FSlot& Data: Inventory->Slots)
	{
		USlotWidget* SlotWidget = CreateWidget<USlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data);
		SlotWidget->SetSlotSize(Inventory->CellSize);
		OnSlotCreated(SlotWidget);
	}
	
	OnInventoryUpdated();
}
