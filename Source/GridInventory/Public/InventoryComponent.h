// Copyright (C) Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UItem;

USTRUCT(BlueprintType)
struct FPoint2D
{
	GENERATED_BODY()

	FPoint2D()
	{
		X = 0;
		Y = 0;
	}

	FPoint2D(const int32 InX, const int32 InY)
	{
		X = InX;
		Y = InY;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	int32 Y;

	bool operator==(const FPoint2D& Other)
	{
		return (X == Other.X && Y == Other.Y);
	}

	FPoint2D operator+(const FPoint2D& Other)
	{
		return FPoint2D(X + Other.X, Y + Other.Y);
	}

	bool IsValid()
	{
		return X >= 0 && Y >= 0;
	}

};

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_BODY()

	FSlot()
	{
		Item = nullptr;
		Quantity = 0;
	}

	FSlot(UItem* InItem, const int32 InQuantity)
	{
		Item = InItem;
		Quantity = InQuantity;
	}

	UPROPERTY(BlueprintReadOnly)
	UItem* Item;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity;

	bool operator==(const FSlot& Other)
	{
		return Item == Other.Item && Quantity == Other.Quantity;
	}

};

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdatedSignature);

UCLASS(Abstract, BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRIDINVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventoryComponent();

	virtual void BeginPlay() override;

	/** How big is this grid in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FPoint2D GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	/** Holds all grid cells coordinates. */
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<FPoint2D> Cells;

	/** Holds our stored items and their grid coordinates. */
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<FSlot> Slots;

	/** Called when inventory changes (item added, removed, moved, etc..). */
	FOnInventoryUpdatedSignature OnInventoryUpdated;


	UFUNCTION(BlueprintCallable, Category = "Grid")
	void Initialize();

	/**
	* Checks whether the specified coordinates are inside the grid.
	*
	* @param	Coordinates		Grid cell coordinates.
	*
	* @return True, if the coordinates are inside the grid.
	*/
	UFUNCTION(BlueprintPure, Category = "Grid")
	bool IsWithinBoundaries(const FPoint2D& Coordinates);

	/**
	* Checks whether a specific grid cell is free to use.
	*
	* @param	Coordinates		Grid cell coordinates.
	*
	* @return True, if the grid cell is free to use.
	*/
	UFUNCTION(BlueprintPure, Category = "Grid")
	bool IsFree(const FPoint2D& Coordinates);

	/**
	* Checks whether we can fit an item on a specific grid cell coordinates.
	*
	* @param	SizeInCells		Item size we are trying to fit.
	* @param	Coordinates		Grid cell coordinates.
	*
	* @return True, if we can fit that item on the specified grid cell coordinates.
	*/
	UFUNCTION(BlueprintPure, Category = "Slot")
	bool DoesItemFit(TArray<FPoint2D> const& SizeInCells, const FPoint2D& Coordinates);

	/**
	* Searches for a free (unused) grid cell.
	*
	* @return Free cell coordinates on the grid. (-1, -1) if none found.
	*/
	UFUNCTION(BlueprintPure, Category = "Slot")
	FPoint2D GetFreeCell();

	/**
	 * Searches for a free grid cell where we can fit a specific item.
	 *
	 * @param	SizeInCells		Item size we are trying to fit.
	 *
	 * @return Cell coordinates where we can fit that item on the grid. (-1, -1) if none found.
	 */
	UFUNCTION(BlueprintPure, Category = "Slot")
	FPoint2D GetFreeCellThatFitsItem(TArray<FPoint2D> const& SizeInCells);

	/**
	 * Adds a new item instance to the inventory.
	 *
	 * @param	ItemClass		Item class we are trying to add/instantiate.
	 * @param	Quantity		Quantity to add.
	 *
	 * @return True, if the item is added to the inventory. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<UItem> ItemClass, int32 Quantity);
	
	/**
	 * Removes an existing item instance from the inventory.
	 *
	 * @param	UniqueId		Item UniqueId we are trying to remove.
	 * @param	Quantity		Quantity to remove.
	 *
	 * @return True, if the item is removed from the inventory. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(int32 UniqueId, int32 Quantity);

	/**
	 * Moves an existing item from to the specified grid coordinates.
	 *
	 * @param	Source			Source grid cell coordinates.
	 * @param	Destination		Destination grid cell coordinates.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void MoveItem(const FSlot& Slot, const FPoint2D& Destination);


private:

	/**
	 * Creates an item instance from the specified item class.
	 *
	 * @param	ItemClass		Item class to instantiate.
	 *
	 * @return a UItem instance of the specified class. nullptr otherwise.
	 */
	UItem* CreateItem(TSubclassOf<UItem> ItemClass);

	/** Notifies all listeners that the inventory has been updated. */
	void HandleInventoryUpdate();
		
};
