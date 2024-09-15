// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentActorInteraction.h"
#include "CheckpointInteraction.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API ACheckpointInteraction : public AParentActorInteraction
{
	GENERATED_BODY()

public:

	ACheckpointInteraction();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UPaperFlipbookComponent* PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class USceneComponent* Checkpoint;

	UPROPERTY(EditDefaultsOnly, Category="Plateformer2D|Interaction|params")
	class UPaperFlipbook* CheckpointOff;

	UPROPERTY(EditDefaultsOnly, Category="Plateformer2D|Interaction|params")
	class UPaperFlipbook* CheckpointOn;

public:
	
	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void BoxBeginOverlaped(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
};
