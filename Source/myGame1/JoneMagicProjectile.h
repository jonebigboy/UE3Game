// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"
#include "JoneMagicProjectile.generated.h"

class UAudioComponent;

UCLASS()
class MYGAME1_API AJoneMagicProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJoneMagicProjectile();



protected:
	

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

public:	
	

};
