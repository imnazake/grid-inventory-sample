// Copyright (C) Neoxyne. All Rights Reserved.

#include "CellWidget.h"

#include "Item.h"
#include "SlotWidget.h"
#include "DraggedSlotWidget.h"
#include "GridWidget.h"
#include "Slot_DragDropOperation.h"

UCellWidget::UCellWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    
}

void UCellWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	USlot_DragDropOperation* Operation = Cast<USlot_DragDropOperation>(InOperation);
	check(Operation != nullptr);

	UDraggedSlotWidget* DraggedSlot = Cast<UDraggedSlotWidget>(Operation->DefaultDragVisual);
	check(DraggedSlot != nullptr);

	// reset all grid cells to their default color
	for (UCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}

	TArray<FPoint2D> ItemSizeInCells = DraggedSlot->SlotData.Item->GetSizeInCells();

	if (DraggedSlot->SlotData.Item->GetOwnerInventory()->DoesItemFit(ItemSizeInCells, Coordinates))
	{
		// Dragged item can be placed, set cells color to valid color ...
		// (starting from current cell coordinates to `coordinates+item size` ...)
		for (FPoint2D& Element : ItemSizeInCells)
		{
			FPoint2D TargetCell = Element + Coordinates;
			const int32 Index = ParentWidget->GetCellIndex(TargetCell);

			if (Index >= 0 && Index < ParentWidget->CellsWidgets.Num())
			{
				// Only change cell color if its within grid boundaries
				ParentWidget->CellsWidgets[Index]->SetCellColor(ValidCellPlacementColor);
			}

			//UE_LOG(LogTemp, Warning, TEXT("Element (%d,%d). TargetCell (%d,%d). Index (%d)"), Element.X, Element.Y, TargetCell.X, TargetCell.Y, Index);
		}
	}
	else
	{
		// Dragged item cannot be placed, set cells color to invalid color ...
		// (starting from current cell coordinates to `coordinates+item size` ...)
		for (FPoint2D& Element : ItemSizeInCells)
		{
			FPoint2D TargetCell = Element + Coordinates;
			const int32 Index = ParentWidget->GetCellIndex(TargetCell);

			if (Index >= 0 && Index < ParentWidget->CellsWidgets.Num())
			{
				// Only change cell color if its within grid boundaries
				ParentWidget->CellsWidgets[Index]->SetCellColor(InvalidCellPlacementColor);
			}

			//UE_LOG(LogTemp, Warning, TEXT("Element (%d,%d). TargetCell (%d,%d). Index (%d)"), Element.X, Element.Y, TargetCell.X, TargetCell.Y, Index);
		}
	}
}

void UCellWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	// reset all grid cells to their default color
	for (UCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}
}

void UCellWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	// reset all grid cells to their default color
	for (UCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}
}

bool UCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bDroppedSomething = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// reset all grid cells to their default color
	for (UCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}

	USlot_DragDropOperation* Operation = Cast<USlot_DragDropOperation>(InOperation);
	check(Operation != nullptr);

	UDraggedSlotWidget* DraggedSlot = Cast<UDraggedSlotWidget>(Operation->DefaultDragVisual);
	check(DraggedSlot != nullptr);

	DraggedSlot->SlotData.Item->GetOwnerInventory()->MoveItem(DraggedSlot->SlotData, Coordinates);

	bDroppedSomething |= true;

	return bDroppedSomething;
}

void UCellWidget::SetData(const FPoint2D& NewCoordinates, const float NewSize, UGridWidget* NewParentWidget)
{
	Coordinates = NewCoordinates;
	CellSize = NewSize;
	ParentWidget = NewParentWidget;

	OnDataReceived();
	  
    SetCellSize(NewSize);
    SetCellColor(DefaultCellColor);
}
