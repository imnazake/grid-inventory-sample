// Copyright (C) Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryComponent.h"
#include "DraggedSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIDINVENTORY_API UDraggedSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UDraggedSlotWidget(const FObjectInitializer& ObjectInitializer);


	UFUNCTION(BlueprintCallable, Category = "DraggedSlot")
	void SetData(const FSlot& NewData, float InCellSize);

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "DraggedSlot")
	void OnItemSizeChanged();


	UPROPERTY(BlueprintReadOnly, Category = "DraggedSlot")
	FSlot SlotData;

	UPROPERTY(BlueprintReadOnly, Category = "DraggedSlot")
	float CellSize;

};
