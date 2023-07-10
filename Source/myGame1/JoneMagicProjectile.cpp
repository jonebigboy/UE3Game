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
 	
	//�ҵ��������������
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AJoneMagicProjectile::OnActorOverlap);


	
}




void AJoneMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor != GetInstigator() && OtherActor) {


		//��ȡײ����Actor��comp����Ѫ��
		//ѡ�񷵻������GetComponentByClass����
		UJoneAttributeComponent* AttributeComp = Cast<UJoneAttributeComponent>(OtherActor->GetComponentByClass(UJoneAttributeComponent::StaticClass()));
		if (AttributeComp) {
			AttributeComp->ApplyHealthChange(-20.0f);
			
			Explode();
		}
	}

}



