// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneMagicProjectile.h"
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "JoneAttributeComponent.h"
#include <Components/AudioComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
AJoneMagicProjectile::AJoneMagicProjectile()
{
 	
	//找到这个函数的输入
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AJoneMagicProjectile::OnActorOverlap);


	
}




void AJoneMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor != GetInstigator() && OtherActor) {


		//获取撞击的Actor的comp减少血量
		//选择返回组件的GetComponentByClass函数
		UJoneAttributeComponent* AttributeComp = Cast<UJoneAttributeComponent>(OtherActor->GetComponentByClass(UJoneAttributeComponent::StaticClass()));
		if (AttributeComp) {
			AttributeComp->ApplyHealthChange(-20.0f);
			
			Explode();
		}
	}

}



