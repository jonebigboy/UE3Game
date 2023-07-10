// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"


class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class MYGAME1_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly);
	URadialForceComponent* RadialForceComp;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
