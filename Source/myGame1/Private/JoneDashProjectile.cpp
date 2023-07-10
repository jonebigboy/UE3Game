// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneDashProjectile.h"
#include <Kismet/GameplayStatics.h>
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
AJoneDashProjectile::AJoneDashProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DestroyTime = 0.2;
	TeleportTime = 0.2;
	MovementComp->InitialSpeed = 8000.0f;

}

// Called when the game starts or when spawned
void AJoneDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	//����һ������0.2��֮��ִ��
	GetWorldTimerManager().SetTimer(TimerHandle_Explode, this,&AJoneDashProjectile::Explode, DestroyTime);
	
}

void AJoneDashProjectile::Explode_Implementation()
{
	//ɾ����ʱ��
	GetWorldTimerManager().ClearTimer(TimerHandle_Explode);
	//���ɱ�ը��Ч
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	//����ϵͳ����
	EffectComp->DeactivateSystem();
		//ֹͣ�ƶ�
	MovementComp->StopMovementImmediately();
	//�Ƴ���ײ
	SetActorEnableCollision(false);
	FTimerHandle TimerHandle_Teleport;

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &AJoneDashProjectile::Teleport_TimeElapsed, TeleportTime);

}

void AJoneDashProjectile::Teleport_TimeElapsed()
{
	AActor* Shooter = GetInstigator(); //���ഫ������
	if (ensure(Shooter)) {
		Shooter->TeleportTo(GetActorLocation(), Shooter->GetActorRotation(), false, false);
	}
	
}

// Called every frame
void AJoneDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

