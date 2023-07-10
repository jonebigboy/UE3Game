// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include <BehaviorTree/BehaviorTreeTypes.h>
#include "JoneBTService_CheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME1_API UJoneBTService_CheckAttackRange : public UBTService
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,Category="AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
