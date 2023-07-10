// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneTargetDummy.h"
#include <Components/StaticMeshComponent.h>
#include "JoneAttributeComponent.h"

// Sets default values
AJoneTargetDummy::AJoneTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticComp");
	AttributeComp = CreateDefaultSubobject<UJoneAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AJoneTargetDummy::OnChangeHealth);

	SpeedLight = 1.0f;
}

// Called when the game starts or when spawned
void AJoneTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJoneTargetDummy::OnChangeHealth(AActor* OtherActor, UJoneAttributeComponent* OwnerComp, float NewHealth, float Change)
{
	if (Change < 0.0f) {
		StaticComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
		//ÉèÖÃËÙ¶È	
		StaticComp->SetScalarParameterValueOnMaterials("SpeedLight", GetWorld()->TimeSeconds);
	}

}

// Called every frame
void AJoneTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

