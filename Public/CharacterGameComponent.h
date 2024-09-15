// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Components/ActorComponent.h"
#include "CharacterGameComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATEFORMER2DGAME_API UCharacterGameComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterGameComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveLeftRight(const FInputActionValue& Value);

	void MoveUpAndDown(const FInputActionValue& Value);

	void Jump();

	void RespawnCharacter(FVector Location, bool bRelife);

	float IncrementGem();

	void CapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Player")
	class APlateformer2DCharacter* CurrentCharacter;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Player")
	AActor* Owner;

	bool bJumping;

	bool bOnLadder;

	FVector RespawnLocation;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Player")
	float Gem;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Player")
	float DefaultDamageAmount = 100;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Widget")
	TSubclassOf<class UPlayerStatWidget> PlayerStatWidgetClass;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Widget")
	class UPlayerStatWidget* PlayerStatWidget;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Widget")
	class AEnemyBase* EnemyBase;

public:
	
	float GetDefaultDamageAmount() const
	{
		return DefaultDamageAmount;
	}
	
	
	class UPlayerStatWidget* GetPlayerStatWidget() const
	{
		return PlayerStatWidget;
	}

	FVector GetRespawnLocation() const
	{
		return RespawnLocation;
	}

	void SetRespawnLocation(const FVector& NewRespawnLocation)
	{
		this->RespawnLocation = NewRespawnLocation;
	}
	
	bool IsOnLadder() const
	{
		return bOnLadder;
	}

	void SetOnLadder(bool bNewOnLadder)
	{
		this->bOnLadder = bNewOnLadder;
	}

	bool IsJumping() const
	{
		return bJumping;
	}

	void SetJumping(bool bNewJumping)
	{
		this->bJumping = bNewJumping;
	}
	
};

