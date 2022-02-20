// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Item.h"

UInventoryComponent::UInventoryComponent()
{
	GridSize = FPoint2D(5, 5);
	CellSize = 50.0f;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

bool UInventoryComponent::IsWithinBoundaries(const FPoint2D& Coordinates)
{
	if (Coordinates.X >= 0 && Coordinates.Y >= 0 && Coordinates.X < GridSize.X && Coordinates.Y < GridSize.Y)
	{
		return true;
	}

	return false;
}

void UInventoryComponent::Initialize()
{                                                                      
	Cells.Empty();

	for (int32 X = 0; X < GridSize.X; X++)
	{
		for (int32 Y = 0; Y < GridSize.Y; Y++)
		{
			Cells.Add(FPoint2D(X, Y));
		}                         
	}

	Slots.Empty();
}

bool UInventoryComponent::IsFree(const FPoint2D& Coordinates)
{
	if (!IsWithinBoundaries(Coordinates))
	{
		// the cell at these coordinates is outside the grid.
		return false;
	}

	for (const FSlot& Slot: Slots)
	{
		for (const FPoint2D& Cell: Slot.Item->GetSizeInCells())
		{
			if (Slot.Item->GetStartCoordinates().X + Cell.X == Coordinates.X &&
				Slot.Item->GetStartCoordinates().Y + Cell.Y == Coordinates.Y)
			{
				// the cell at these coordinates is not empty.
				return false;
			}
		}
	}

	return true;
}

bool UInventoryComponent::DoesItemFit(TArray<FPoint2D> const& SizeInCells, const FPoint2D& Coordinates)
{
	for (const FPoint2D& Cell: SizeInCells)
	{																													
		if (!IsFree(FPoint2D(Coordinates.X + Cell.X, Coordinates.Y + Cell.Y))) 
		{
			// Item does not fit because the cell at these coordinates is occupied.
			return false;
		}
	}

	return true;
}

FPoint2D UInventoryComponent::GetFreeCell()
{
	for (const FPoint2D& Coordinates: Cells)
	{
		if (IsFree(Coordinates))
		{
			return Coordinates;
		}
	}

	return FPoint2D(-1, -1);
}

FPoint2D UInventoryComponent::GetFreeCellThatFitsItem(TArray<FPoint2D> const& SizeInCells)
{
	for (const FPoint2D& Coordinates: Cells)
	{
		if (IsFree(Coordinates))
		{
			if (DoesItemFit(SizeInCells, Coordinates))
			{
				return Coordinates;
			}
		}
	}

	return FPoint2D(-1, -1);
}

bool UInventoryComponent::AddItem(const TSubclassOf<UItem> ItemClass, const int32 Quantity)
{
	UItem* ItemInstance = CreateItem(ItemClass);
	
	FPoint2D Coordinates = GetFreeCellThatFitsItem(ItemInstance->GetSizeInCells());

	if (Coordinates.IsValid())
	{
		ItemInstance->SetStartCoordinates(Coordinates);

		const FSlot Data = FSlot(ItemInstance, Quantity);
		Slots.Add(Data);

		HandleInventoryUpdate();

		return true;
	}

	if (ItemInstance->CanRotate())
	{
		ItemInstance->Rotate();

		FPoint2D RotatedCoordinates = GetFreeCellThatFitsItem(ItemInstance->GetSizeInCells());

		if (RotatedCoordinates.IsValid())
		{
			ItemInstance->SetStartCoordinates(RotatedCoordinates);

			const FSlot Data = FSlot(ItemInstance, Quantity);
			Slots.Add(Data);

			HandleInventoryUpdate();

			return true;
		}

		return false;
	}

	return false;
}

bool UInventoryComponent::RemoveItem(int32 UniqueId, int32 Quantity)
{
	return true;
}

void UInventoryComponent::MoveItem(const FSlot& Slot, const FPoint2D& Destination)
{
	for (FSlot& Element : Slots)
	{
		if (Element == Slot)
		{
			if (DoesItemFit(Element.Item->GetSizeInCells(), Destination))
			{
				Element.Item->SetStartCoordinates(Destination);
				HandleInventoryUpdate();
				return;
			}
		}
	}
}

UItem* UInventoryComponent::CreateItem(const TSubclassOf<UItem> ItemClass)
{
	UItem* ItemInstance = NewObject<UItem>(GetOwner(), ItemClass);
	check(ItemInstance != nullptr);

	ItemInstance->OnConstruct();
	ItemInstance->SetOwningInventory(this);

	return ItemInstance;
}

void UInventoryComponent::HandleInventoryUpdate()
{
	OnInventoryUpdated.Broadcast();
}
