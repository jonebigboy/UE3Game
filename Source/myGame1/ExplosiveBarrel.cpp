// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include <Components/StaticMeshComponent.h>
#include <PhysicsEngine/RadialForceComponent.h>
#include <DrawDebugHelpers.h>


// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnCompHit);
	StaticMeshComp->SetSimulatePhysics(true);
	RootComponent = StaticMeshComp;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(StaticMeshComp);

	RadialForceComp->Radius = 750.0f;			 // 爆炸范围
	RadialForceComp->ImpulseStrength = 2000.0f; // 冲击力
	RadialForceComp->bImpulseVelChange = true; // 忽略质量大小；见UE中ForceComp的“冲量速度变更”


}
//postinitializeComponents 在beginplay之前执行

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMeshComp->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnCompHit);
}

void AExplosiveBarrel::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();
	
	//LogTemp用于分类log
	UE_LOG(LogTemp, Log, TEXT("OnActor Attack the barrel"));
	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at game time: 124.4" 
	//可以吧字符串理解为一个指针，然后用*解引用
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	// logs: "Hit at location: 111" 
	FString CombineString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombineString, nullptr, FColor::Green, 2.0f, true);
	// Detailed info on logging in ue4
	// https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

