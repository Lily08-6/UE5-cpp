// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "FallingInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API AFallingInteraction : public AParentActorInteraction
{
	GENERATED_BODY()
	
	AFallingInteraction();

private:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, Category="Plateformer2D|Interaction")
	TSubclassOf<AFallingInteraction> FallingInteractionClass;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|params")
	float DropDelay = 2.0f;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|params")
	float RespawnDelay = 2.0f;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|params")
	bool bDestroy = true;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|params")
	bool bRespawn = true;

	FVector StartLocation;

	FTimerHandle TimerHandle;

	bool bAlreadyOnFall;

public:

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void OnFall();

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void OnReset();
	
};
