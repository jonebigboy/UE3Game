// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class UAudioComponent;

UCLASS()
class MYGAME1_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,Category= "Effect")
	UParticleSystem* ImpactVFX;

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
	USoundBase* ImpactSound;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere,Category="Component");
	USphereComponent* SphereComp;

	//给出组件的速度移动
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component");
	UProjectileMovementComponent* MovementComp;
	//粒子系统，有东西展示
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component");
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditDefaultsOnly, Category = "Component")
	UAudioComponent* AudioComp;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Explode();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
