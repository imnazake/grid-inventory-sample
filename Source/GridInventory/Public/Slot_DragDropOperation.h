// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Slot_DragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class GRIDINVENTORY_API USlot_DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:

	USlot_DragDropOperation(const FObjectInitializer& ObjectInitializer);

};
