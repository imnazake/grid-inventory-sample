// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnItemSizeChangedSignature);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GRIDINVENTORY_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem(const FObjectInitializer& ObjectInitializer);


	/** Called when we create an instance of a UItem using CreateItem(). @see InventoryComponent. */
	void OnConstruct();

	/** Stores the first cell coordinates (top-left cell of our item) where we stored this item in the grid. */
	void SetStartCoordinates(const FPoint2D& Coordinates);

	/** How big is this item in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FPoint2D Size;


	UFUNCTION(BlueprintPure, Category = "Item")
	FORCEINLINE FPoint2D const& GetStartCoordinates()
	{
		return StartCoordinates;
	}

	UFUNCTION(BlueprintPure, Category = "Item")
	FORCEINLINE TArray<FPoint2D> const& GetSizeInCells()
	{
		return SizeInCells;
	}

	/**
	* Calculates how many cells are needed to store this item based on Size.
	* 
	* @return An array of cell(s) coordinates relative to StartCoordinates.
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
	TArray<FPoint2D> CalcItemSize();

	/** 
	* @return true, if we can rotate this item.
	* 
	* @note this currently returns true only for rectangle-shaped items.
	* return true, if you want to rotate any item.
	*/
	UFUNCTION(BlueprintPure, Category = "Item")
	bool CanRotate();

	/** Rotates the item (inverts Size and SizeInCells coordinates). Use cached values to undo this. */
	UFUNCTION(BlueprintCallable, Category = "Item")
	void Rotate();

	UFUNCTION(BlueprintCallable, Category = "Item")
	UInventoryComponent* GetOwnerInventory()
	{
		return OwnerInventory;
	}

	void SetOwningInventory(UInventoryComponent* NewInventory);


	void HandleItemSizeChanged();
	FOnItemSizeChangedSignature OnItemSizeChanged;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 UniqueId;

private:

	/** First grid cell (Top-left corner of our item) coordinates where we found an empty space that can fit this item. */
	FPoint2D StartCoordinates;

	/** All grid cells coordinates used to store this item. */
	TArray<FPoint2D> SizeInCells;

	/** These hold default data before rotating the item. */
	FPoint2D CachedSize;
	TArray<FPoint2D> CachedSizeInCells;

	/** Whether the item is currently rotated. */
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item")
	uint8 bIsRotated : 1;

	/** Item's owning inventory component reference. */
	UPROPERTY(Transient)
	UInventoryComponent* OwnerInventory;
};
