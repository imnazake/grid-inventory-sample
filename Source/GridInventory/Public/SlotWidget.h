// Copyright (C) Neoxyne, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class GRIDINVENTORY_API USlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	USlotWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Slot")
	void SetData(const FSlot& NewData);

	UFUNCTION(BlueprintImplementableEvent, Category = "Slot")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Slot")
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "Slot")
	void SetSlotColor(const FSlateBrush& Brush);



	UPROPERTY(BlueprintReadOnly, Category = "Slot")
	FSlot SlotData;
};
