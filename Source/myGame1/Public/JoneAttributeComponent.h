// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JoneAttributeComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, OtherActor, UJoneAttributeComponent*, OwnerComp, float, NewHealth, float, Change);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYGAME1_API UJoneAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJoneAttributeComponent();

protected:
	

	// EditAnywhere - edit in BP editor and per-instance in level.
	// VisibleAnywhere - 'read-only' in editor and level. (Use for Components)
	// EditDefaultsOnly - hide variable per-instance, edit in BP editor only
	// VisibleDefaultsOnly - 'read-only' access for variable, only in BP editor (uncommon)
	// EditInstanceOnly - allow only editing of instance (eg. when placed in level)
	// --
	// BlueprintReadOnly - read-only in the Blueprint scripting (does not affect 'details'-panel)
	// BlueprintReadWrite - read-write access in Blueprints
	// --
	// Category = "" - display only for detail panels and blueprint context menu.
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Attribute")
	float health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	float HealthMax;

public:

	UFUNCTION(BlueprintCallable)
	bool isAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable,Category="Attribute")
	bool ApplyHealthChange(float Number);

	

		
};
