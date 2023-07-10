// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoneTargetDummy.generated.h"

class UJoneAttributeComponent;
class UStaticMeshComponent;

UCLASS()
class MYGAME1_API AJoneTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJoneTargetDummy();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticComp;

	UPROPERTY(VisibleAnywhere)
	UJoneAttributeComponent *AttributeComp;

	UFUNCTION()
	void OnChangeHealth(AActor* OtherActor, UJoneAttributeComponent* OwnerComp, float NewHealth, float Change);

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attribute")
	float SpeedLight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
