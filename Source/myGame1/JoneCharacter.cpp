// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>


// Sets default values
AJoneCharacter::AJoneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SprintArmComp = CreateDefaultSubobject<USpringArmComponent>("SprintArmComp");
	SprintArmComp->SetupAttachment(RootComponent);
	SprintArmComp->bUsePawnControlRotation = true; //���ⲿ�ĵ��ɱ���

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SprintArmComp);
	//ʹ�ý�ɫ��������ƶ����� 
	GetCharacterMovement()->bOrientRotationToMovement = true; //���ص���һ����ɫ�˶���ָ��

	bUseControllerRotationYaw = false; //�����������ȡ����ѡ
}

// Called when the game starts or when spawned
void AJoneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJoneCharacter::MoveForward(float value)
{
	FRotator ControlBot = GetControlRotation();//��ȡ�������ķ���
	//ȥ������ˮƽ֮��ķ���
	ControlBot.Pitch = 0.0f;
	ControlBot.Roll = 0.0f;
	//����������ƶ�
	AddMovementInput(ControlBot.Vector(), value);
}

void AJoneCharacter::MoveRight(float value) {

	FRotator ControlBot = GetControlRotation();//��ȡ�������ķ���
	//ȥ������ˮƽ֮��ķ���
	ControlBot.Pitch = 0.0f;
	ControlBot.Roll = 0.0f;
	//FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator ControlBot);
	FVector RightVector = FRotationMatrix(ControlBot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);

}

// Called every frame
void AJoneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJoneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &AJoneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJoneCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

