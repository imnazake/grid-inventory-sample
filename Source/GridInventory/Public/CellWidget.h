// Copyright (C) Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Styling/SlateBrush.h"
#include "Blueprint/UserWidget.h"
#include "CellWidget.generated.h"

class UGridWidget;

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


	UFUNCTION(BlueprintCallable, Category = "Cell")
	void SetData(const FPoint2D& NewCoordinates, const float NewSize, UGridWidget* ParentWidget);

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

	UPROPERTY(BlueprintReadOnly, Category = "Cell")
	UGridWidget* ParentWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush DefaultCellColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush ValidCellPlacementColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cell")
	FSlateBrush InvalidCellPlacementColor;
	
};
