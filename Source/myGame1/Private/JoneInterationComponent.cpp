// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneInterationComponent.h"
#include "JoneGamePlayInterface.h"
#include <DrawDebugHelpers.h>

// Sets default values for this component's properties
UJoneInterationComponent::UJoneInterationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UJoneInterationComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	AActor* MyOwner = GetOwner(); //获取当前的 actor
	//半径
	float r = 30.0f;

	FVector EyeLocation;  //作为开始的位置
	FRotator EyeRotation; 
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + EyeRotation.Vector() * 1000; //眼睛方向的这个地方是线条碰撞的终点
	//FHitResult Hit; //存储碰撞的结果
	//bool isBlock = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(r);

	bool isBlock = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	
	FColor LineColor = isBlock ? FColor::Green : FColor::Red;
	FHitResult FirstHit;//接收第一个
	for (FHitResult& Hit : Hits) {
		AActor* HitOwner = Hit.GetActor();
		if (HitOwner) { //判断是否存在
			if (HitOwner->Implements<UJoneGamePlayInterface>()) { //对象是否实现接口U来表示接口，I来用来执行
				FirstHit = Hit;
				APawn* MyPawn= Cast<APawn>(MyOwner);
				IJoneGamePlayInterface::Execute_Interact(HitOwner, MyPawn);
				break;
			}
		}
		
		
	}
	DrawDebugSphere(GetWorld(), FirstHit.ImpactPoint, r, 32, LineColor, false, 2.0f);
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
	
}

// Called when the game starts
void UJoneInterationComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void UJoneInterationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

