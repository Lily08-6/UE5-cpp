// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "TranpolineInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API ATranpolineInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

	ATranpolineInteraction();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction|Params")
	FVector LaunchVelocity = FVector(0.0f, 0.0f, 600.f);

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction")
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction")
	UPaperSprite* SpriteTrampolineUp;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction")
	UPaperSprite* SpriteTrampolineDown;

	FTimerHandle TimerHandle;

public:
	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ResetTrampoline();
	
};
