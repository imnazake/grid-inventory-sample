// Copyright (C) Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "SlotWidget.generated.h"

class UGridWidget;

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
	void SetData(const FSlot& NewData, UGridWidget* NewParentWidget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Slot")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Slot")
	void SetSlotSize(float Size);

	UFUNCTION(BlueprintImplementableEvent, Category = "Slot")
	void SetSlotColor(const FSlateBrush& Brush);


	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	UPROPERTY(Transient, BlueprintReadOnly, Category = "Slot")
	FSlot SlotData;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "Slot")
	UGridWidget* ParentWidget;


};
