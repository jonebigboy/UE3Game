// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JoneGamePlayInterface.h"
#include "JoneItemChestActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class MYGAME1_API AJoneItemChestActor : public AActor,public IJoneGamePlayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJoneItemChestActor();

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UStaticMeshComponent* LidMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//因为UFUNCTION(BlueprintNativeEvent) 这个声明会加一个实施的参数
	void Interact_Implementation(APawn* InstigatorPawn) override;
	
};
