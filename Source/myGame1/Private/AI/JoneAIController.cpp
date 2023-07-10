// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JoneAIController.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h" 

void AJoneAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BeTree);

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (MyPawn) {

		GetBlackboardComponent()->SetValueAsVector("MoveLocation", MyPawn->GetActorLocation());

		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);

	}

}
