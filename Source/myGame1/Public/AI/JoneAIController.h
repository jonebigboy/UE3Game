// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "JoneAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME1_API AJoneAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,Category="AI")
	UBehaviorTree* BeTree;

	virtual void BeginPlay() override;
	
};
