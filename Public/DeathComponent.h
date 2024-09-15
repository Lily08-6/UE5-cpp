// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DeathComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATEFORMER2DGAME_API UDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDeathComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	bool bIsDead = false;

public:

	UFUNCTION(BlueprintPure, Category="Plateformer2D")
	bool IsDead() const
	{
		return bIsDead;
	}
	
	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void SetIsDead(bool bNewIsDead)
	{
		this->bIsDead = bNewIsDead;
	}

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void OnDeath();		
};
