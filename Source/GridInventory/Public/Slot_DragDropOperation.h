// Copyright (C) Neoxyne. All Rights Reserved.

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
