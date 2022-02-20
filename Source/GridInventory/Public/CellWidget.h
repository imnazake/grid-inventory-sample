// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Styling/SlateBrush.h"
#include "Blueprint/UserWidget.h"
#include "CellWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIDINVENTORY_API UCellWidget : public UUserWidget
{
	GENERATED_BODY()
		
public:

	UCellWidget(const FObjectInitializer& ObjectInitializer);


	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	/** Stores grid cell widgets array from parent widget. */
	void SetCellsWidgets(const TArray<UCellWidget*>& NewCellsWidgets);

	/** Returns index of cell widget in cells widgets array from the specified cell coordinates. -1 if none found. */
	int32 GetCellIndex(const FPoint2D& InCoordinates);


	UFUNCTION(BlueprintCallable, Category = "Cell")
	void SetData(const FPoint2D& NewCoordinates, const float NewSize);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
	void SetCellSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "Cell")
	void SetCellColor(const FSlateBrush& Brush);




	// Current cell coordinates in the grid.
	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	FPoint2D Coordinates;

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	float CellSize;	
	
	// An array of all the grid cell widgets.
	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	TArray<UCellWidget*> CellsWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush DefaultCellColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush ValidCellPlacementColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush InvalidCellPlacementColor;
	
};
