// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.h"
#include "JoneDashProjectile.generated.h"

UCLASS()
class MYGAME1_API AJoneDashProjectile : public ABaseProjectile
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJoneDashProjectile();
	float DestroyTime;
	float TeleportTime;

	FTimerHandle TimerHandle_Explode;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Base class using BlueprintNativeEvent, we must override the _Implementation not the Explode()
	virtual void Explode_Implementation() override;

	

	void Teleport_TimeElapsed();

};
