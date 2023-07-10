// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "JoneGamePlayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UJoneGamePlayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MYGAME1_API IJoneGamePlayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent) //可以在蓝图中实现也可以在CPP中实现
	void Interact(APawn* InstigatorPawn);

};
