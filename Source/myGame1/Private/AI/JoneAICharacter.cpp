// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/JoneAICharacter.h"

// Sets default values
AJoneAICharacter::AJoneAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJoneAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJoneAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJoneAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

