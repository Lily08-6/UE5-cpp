// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "SpikeInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API ASpikeInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

public:

	ASpikeInteraction();

	void ChangeSpikeStat();

	UFUNCTION(BlueprintCallable, Category= "Plateformer2D")
	void BringSpikeUp();
	
	UFUNCTION(BlueprintCallable, Category= "Plateformer2D")
	void BringSpikeDown();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction|Params")
	bool bSpikeUp = false;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction|Params")
	bool bLooping = true;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction|Params")
	float DamageAmount = 10.f;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction|Params")
	float Duration = 4.f;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction")
	class UPaperSprite* SpriteSpikeUp;
	
	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction")
	UPaperSprite* SpriteSpikeDown;

	FTimerHandle TimerHandle;

public:
	
	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
