// Fill out your copyright notice in the Description page of Project Settings.


#include "JoneAttributeComponent.h"
#include <Math/UnrealMathUtility.h>

// Sets default values for this component's properties
UJoneAttributeComponent::UJoneAttributeComponent()
{
	health = 100.0f;
	HealthMax = 100.f;

}

bool UJoneAttributeComponent::isAlive() const
{
	return health > 0.0f;
}

bool UJoneAttributeComponent::ApplyHealthChange(float Number)
{
	health += Number;
	health = FMath::Clamp(health, 0.0f, HealthMax);
	
	OnHealthChanged.Broadcast(nullptr, this, health, Number);
	return true;
}


