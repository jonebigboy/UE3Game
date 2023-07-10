// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <DrawDebugHelpers.h>
#include "JoneInterationComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "JoneAttributeComponent.h"
#include <CollisionQueryParams.h>

// Sets default values
AJoneCharacter::AJoneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SprintArmComp = CreateDefaultSubobject<USpringArmComponent>("SprintArmComp");
	SprintArmComp->SetupAttachment(RootComponent);
	SprintArmComp->bUsePawnControlRotation = true; //在外部的弹簧臂中

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SprintArmComp);

	InterationComp = CreateDefaultSubobject<UJoneInterationComponent>("InterationComp");

	AttributeComp = CreateDefaultSubobject<UJoneAttributeComponent>("AttributeComp");
	
	
	//使得角色随着鼠标移动方向 
	GetCharacterMovement()->bOrientRotationToMovement = true; //返回的是一个角色运动的指针

	bUseControllerRotationYaw = false; //在人物里面的取消勾选
}

//生命周期中用来初始化的一个方便的组件
void AJoneCharacter::PostInitializeComponents()
{

	Super::PostInitializeComponents();
	AttributeComp->OnHealthChanged.AddDynamic(this, &AJoneCharacter::OnChangeHealth);

}
// Called when the game starts or when spawned
void AJoneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJoneCharacter::OnChangeHealth(AActor* OtherActor, UJoneAttributeComponent* OwnerComp, float NewHealth, float Change)
{
	if (Change < 0.0f) {
		GetMesh()->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.0f && Change < 0.0f) {

		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}



void AJoneCharacter::MoveForward(float value)
{
	FRotator ControlBot = GetControlRotation();//获取控制器的方向
	//去掉除了水平之外的方向
	ControlBot.Pitch = 0.0f;
	ControlBot.Roll = 0.0f;
	//向这个方向移动
	AddMovementInput(ControlBot.Vector(), value);
}

void AJoneCharacter::MoveRight(float value) {

	FRotator ControlBot = GetControlRotation();//获取控制器的方向
	//去掉除了水平之外的方向
	ControlBot.Pitch = 0.0f;
	ControlBot.Roll = 0.0f;
	//FVector RightVector = UKismetMathLibrary::GetRightVector(FRotator ControlBot);
	FVector RightVector = FRotationMatrix(ControlBot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);

}

void AJoneCharacter::JumpStart()
{
	bPressedJump = true;
}

void AJoneCharacter::JumpEnd()
{
	bPressedJump = false;
}

void AJoneCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackAnim);

	//FTimerHandle 一个时间处理的结构体表示这个时间用来处理的函数
	// 传入执行的函数地址
	// 传入过多久执行
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AJoneCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}


void AJoneCharacter::SecondAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_SecondAttack, this, &AJoneCharacter::SecondAttack_TimeElapsed, 0.2f);
}

void AJoneCharacter::DashMove()
{
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(TimerHandle_DashMove, this, &AJoneCharacter::DashMove_TimeElapsed, 0.2f);
}

void AJoneCharacter::SecondAttack_TimeElapsed()
{
	this->SpawnAttack(this->BlackHoleProjectileClass);
}

void AJoneCharacter::PrimaryAttack_TimeElapsed()
{
	this->SpawnAttack(this->ProjectileClass);

}

void AJoneCharacter::DashMove_TimeElapsed()
{
	this->SpawnAttack(this->DashMoveClass);
}


void AJoneCharacter::SpawnAttack(TSubclassOf<AActor>& SpawnClass)
{
	//获取骨骼位置
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	//获取新的旋转
	//获取目标点位置
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult Hit;
	FVector Start;
	FCollisionShape Shape;
	Shape.SetSphere(20.0f);

	Start = CameraComp->GetComponentLocation();

	FRotator CameraRo = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();
	FVector End = Start + CameraRo.Vector() * 10000;

	bool IsAttack = GetWorld()->SweepSingleByObjectType(Hit, Start, End, FQuat::Identity, ObjectQueryParams, Shape, Params);
	
	FRotator ProjectileDir;
	//判断是否存在点
	if (IsAttack) {
		ProjectileDir = UKismetMathLibrary::FindLookAtRotation(HandLocation, Hit.ImpactPoint);
	}
	else {
		ProjectileDir = UKismetMathLibrary::FindLookAtRotation(HandLocation, End);
	}


	UE_LOG(LogTemp, Warning, TEXT("Start: %s, End: %s"), *Hit.ImpactPoint.ToString(), *End.ToString());
	//制定旋转和位置
	//FTransform SpawnTM = FTransform(GetControlRotation() , HandLocation);
	FTransform SpawnTM = FTransform(ProjectileDir, HandLocation);
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 2.0f);

	FActorSpawnParameters SpawnParams;
	//使得他一直生成不考虑撞击因素
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//传入发起人用于无视碰撞
	SpawnParams.Instigator = this;
	//SpawnTM产生的位置
	GetWorld()->SpawnActor<AActor>(SpawnClass, SpawnTM, SpawnParams);
}





void AJoneCharacter::PrimaryInteract()
{
	if (InterationComp) {
		InterationComp->PrimaryInteract();
	}

}

// Called every frame
void AJoneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//画出debug剪头
	// -- Rotation Visualization -- //
	

}

// Called to bind functionality to input
void AJoneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this, &AJoneCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJoneCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AJoneCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AJoneCharacter::JumpEnd);

	PlayerInputComponent->BindAction("PrimaryAttack",IE_Pressed, this, &AJoneCharacter::PrimaryAttack);

	PlayerInputComponent->BindAction("SecondAttack", IE_Pressed, this, &AJoneCharacter::SecondAttack);

	PlayerInputComponent->BindAction("DashMove", IE_Pressed, this, &AJoneCharacter::DashMove);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &AJoneCharacter::PrimaryInteract);
}

