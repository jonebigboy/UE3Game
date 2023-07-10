// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JoneBTService_CheckAttackRange.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Actor.h>
#include <AIController.h>
#include <GameFramework/Pawn.h>

void UJoneBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp,NodeMemory,DeltaSeconds);

	// πµ√AI ‘∂¿Îactor
	UBlackboardComponent* BlackBoardComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackBoardComp)) {
		AActor* TargetActor = Cast<AActor>( BlackBoardComp->GetValueAsObject("TargetActor"));
		if (TargetActor) {
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController)) {
				APawn* AIPawn =  MyController->GetPawn();
				if (ensure(AIPawn)) {
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());
					bool inRange = DistanceTo < 2000.0f;
					bool isSeeTarget = false;

					if (inRange) {
						isSeeTarget = MyController->LineOfSightTo(TargetActor);
					}
					

					BlackBoardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, inRange&&isSeeTarget);
				}
			}
		}
	}

}
