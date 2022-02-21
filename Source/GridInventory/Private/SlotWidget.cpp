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
	//
	// USlot_DragDropOperation* Operation = Cast<USlot_DragDropOperation>(InOperation);
	// check(Operation != nullptr);
	//
	// UDraggedSlotWidget* DraggedSlot = Cast<UDraggedSlotWidget>(Operation->DefaultDragVisual);
	// check(DraggedSlot != nullptr);
	//
	// // reset all grid cells to their default color
	// for (UCellWidget* Cell : ParentWidget->CellsWidgets)
	// {
	// 	Cell->SetCellColor(Cell->DefaultCellColor);
	// }
	//
	// TArray<FPoint2D> ItemSizeInCells = DraggedSlot->SlotData.Item->GetSizeInCells();
	//
	// if (DraggedSlot->SlotData.Item->GetOwnerInventory()->DoesItemFit(ItemSizeInCells, SlotData.Item->GetStartCoordinates()/*Coordinates*/))
	// {
	// 	// Dragged item can be placed, set cells color to valid color ...
	// 	// (starting from current cell coordinates to `coordinates+item size` ...)
	// 	for (FPoint2D& Element : ItemSizeInCells)
	// 	{
	// 		FPoint2D TargetCell = Element;// + Coordinates;
	// 		const int32 Index = ParentWidget->GetCellIndex(TargetCell);
	//
	// 		if (Index >= 0 && Index < ParentWidget->CellsWidgets.Num())
	// 		{
	// 			// Only change cell color if its within grid boundaries
	// 			ParentWidget->CellsWidgets[Index]->SetCellColor(ParentWidget->CellsWidgets[Index]->ValidCellPlacementColor);
	// 		}
	//
	// 		//UE_LOG(LogTemp, Warning, TEXT("Element (%d,%d). TargetCell (%d,%d). Index (%d)"), Element.X, Element.Y, TargetCell.X, TargetCell.Y, Index);
	// 	}
	// }
	// else
	// {
	// 	// Dragged item cannot be placed, set cells color to invalid color ...
	// 	// (starting from current cell coordinates to `coordinates+item size` ...)
	// 	for (FPoint2D& Element : ItemSizeInCells)
	// 	{
	// 		FPoint2D TargetCell = Element;// + Coordinates;
	// 		const int32 Index = ParentWidget->GetCellIndex(TargetCell);
	//
	// 		if (Index >= 0 && Index < ParentWidget->CellsWidgets.Num())
	// 		{
	// 			// Only change cell color if its within grid boundaries
	// 			ParentWidget->CellsWidgets[Index]->SetCellColor(ParentWidget->CellsWidgets[Index]->InvalidCellPlacementColor);
	// 		}
	//
	// 		//UE_LOG(LogTemp, Warning, TEXT("Element (%d,%d). TargetCell (%d,%d). Index (%d)"), Element.X, Element.Y, TargetCell.X, TargetCell.Y, Index);
	// 	}
	// }
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
