// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "MovingInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API AMovingInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

	AMovingInteraction();

protected:
	
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class USceneComponent* EndLocation;

	FVector StartLocation;

	FVector TargetLocation;

public:

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void Move(const float& DurationTimeLine);

	

	
};
