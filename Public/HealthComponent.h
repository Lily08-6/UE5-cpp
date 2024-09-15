// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATEFORMER2DGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void Relife();

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void InitHealth();

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	float TakeDamage(const float& Damage);

private:

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Params")
	float Health;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Params")
	float DefaultHealth;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Player")
	AActor* Owner;

public:
	
	float GetHealth() const
	{
		return Health;
	}

	void UpdateHealth(float NewHealth)
	{
		this->Health = NewHealth;
	}

	float GetDefaultHealth() const
	{
		return DefaultHealth;
	}

	void SetDefaultHealth(float NewDefaultHealth)
	{
		this->DefaultHealth = NewDefaultHealth;
	}
		
};
