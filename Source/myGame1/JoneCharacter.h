// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JoneCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UJoneInterationComponent;
class UAnimMontage;
class UJoneAttributeComponent;

UCLASS()
class MYGAME1_API AJoneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJoneCharacter();

	FTimerHandle TimerHandle_PrimaryAttack;

	FTimerHandle TimerHandle_SecondAttack;

	FTimerHandle TimerHandle_DashMove;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere);
	USpringArmComponent * SprintArmComp;
	UPROPERTY(VisibleAnywhere);
	UCameraComponent * CameraComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UJoneInterationComponent* InterationComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UJoneAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnChangeHealth(AActor* OtherActor, UJoneAttributeComponent* OwnerComp, float NewHealth, float Change);
	
	virtual void PostInitializeComponents();

	void MoveForward(float value);

	void MoveRight(float value);

	void JumpStart();

	void JumpEnd();

	void PrimaryAttack_TimeElapsed();

	void PrimaryAttack();

	void SecondAttack_TimeElapsed();

	void SecondAttack();

	void DashMove_TimeElapsed();

	void DashMove();

	void SpawnAttack(TSubclassOf<AActor>&);

	void PrimaryInteract();
	
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackHoleProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashMoveClass;

	UPROPERTY(EditAnywhere, Category = "Attack");
	UAnimMontage* AttackAnim;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
