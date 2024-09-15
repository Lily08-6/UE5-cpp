// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "GemInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API AGemInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

	AGemInteraction();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UBoxComponent* BoxComponent;

public:

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void BoxEndOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
