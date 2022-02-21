// Copyright (C) Neoxyne. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridWidget.generated.h"

class UInventoryComponent;
class UCellWidget;
class USlotWidget;

/**
 * 
 */
UCLASS()
class GRIDINVENTORY_API UGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UGridWidget(const FObjectInitializer& ObjectInitializer);

	
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void SetData(UInventoryComponent* NewInventory);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnDataReceived();

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnPreInitialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnCellCreated(UCellWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnSlotCreated(USlotWidget* Widget);

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnPreUpdateInventory();

	UFUNCTION(BlueprintImplementableEvent, Category = "Grid")
	void OnInventoryUpdated();


	void NativeOnDataReceived();
	void NativeOnInventoryUpdate();


	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	UInventoryComponent* Inventory;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TSubclassOf<UCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<UCellWidget*> CellsWidgets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grid")
	TSubclassOf<USlotWidget> SlotWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<USlotWidget*> SlotsWidgets;
};
