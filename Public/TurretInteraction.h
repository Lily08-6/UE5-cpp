// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurretInteraction.generated.h"

UCLASS()
class PLATEFORMER2DGAME_API ATurretInteraction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurretInteraction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TurretTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category="Plateformer2D|Interaction|params")
	float DurationSpawn = 2.f;

	UPROPERTY(EditDefaultsOnly, Category="Plateformer2D|Interaction|params")
	bool bLooping = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Plateformer2D")
	void Fire();

private:

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class UPaperSpriteComponent* PaperSprite;

	UPROPERTY(VisibleAnywhere, Category="Plateformer2D|Interaction")
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category="Plateformer2D|Interaction")
	TSubclassOf<class AProjectileParent> ProjectileClass;

};
