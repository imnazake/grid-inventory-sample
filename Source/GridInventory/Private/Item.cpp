// Copyright (C) Neoxyne. All Rights Reserved.

#include "Item.h"

UItem::UItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Size = FPoint2D(1, 1);
	bIsRotated = false;
	UniqueId = 0;
}

void UItem::OnConstruct()
{
	SizeInCells.Empty();
	SizeInCells = CalcItemSize();

	CachedSize = Size;
	CachedSizeInCells = SizeInCells;

	bIsRotated = false;
}

void UItem::SetStartCoordinates(const FPoint2D& Coordinates)
{
	StartCoordinates = Coordinates;
}

TArray<FPoint2D> UItem::CalcItemSize()
{
	TArray<FPoint2D> ItemSize;

	for (int32 X = 0; X < Size.X; X++)
	{
		for (int32 Y = 0; Y < Size.Y; Y++)
		{
			ItemSize.Add(FPoint2D(X, Y));		
		}
	}

	return ItemSize;
}

bool UItem::CanRotate()
{
	// Only rotate rectangle-shaped items because they might fit in a specific space.
	return Size.X != Size.Y;

	//return true; // Uncomment: If you want to be able to rotate any item.
}

void UItem::Rotate()
{
	if (!CanRotate())
	{
		return;
	}

	if (bIsRotated)
	{
		Size = CachedSize;
		SizeInCells = CachedSizeInCells;

		bIsRotated = false;

		HandleItemSizeChanged();

		return;
	}

	SizeInCells.Empty();

	for (const FPoint2D& Coordinates: CachedSizeInCells)
	{
		FPoint2D InvertedCoordinates = FPoint2D(Coordinates.Y, Coordinates.X);
		SizeInCells.Add(InvertedCoordinates);	
	}

	const FPoint2D InvertedSize = FPoint2D(CachedSize.Y, CachedSize.X);
	Size = InvertedSize;

	bIsRotated = true;

	HandleItemSizeChanged();
}

void UItem::SetOwningInventory(UInventoryComponent* NewInventory)
{
	OwnerInventory = NewInventory;
}

void UItem::HandleItemSizeChanged()
{
	OnItemSizeChanged.Broadcast();
}
