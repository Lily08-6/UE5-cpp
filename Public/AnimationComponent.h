// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbook.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Sound/SoundCue.h"
#include "AnimationComponent.generated.h"

UENUM(BlueprintType)
enum ECharacterState
{
	Idle,
	Run,
	Jump,
	Attack,
	Climb,
	IdleClimb,
	Fall,
	Dead
};

USTRUCT(BlueprintType)
struct FAnimationStruct: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ECharacterState> AnimationState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperFlipbook* AnimationFlipbook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bLoopAnimation;	
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATEFORMER2DGAME_API UAnimationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAnimationComponent();

	void UpdateControlRotation();

	void AnimationStateMachine();

	bool RunAnimation();

	bool JumpAnimation();

	bool FallAnimation();

	bool ClimbAnimation();

	bool AttackAnimation();

	bool DeathAnimation();

	void UpdateAnimation();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UDataTable* GetDataTable();

	UDataTable* GetDataTableRow(ECharacterState CurrentState);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Plateformer2D|Player")
	class APlateformer2DCharacter* CurrentCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Plateformer2D|Player")
	AActor* Owner;


	ECharacterState CharacterState;

	UPROPERTY(EditAnywhere, Category = "Plateformer2D|Animation")
	TArray<FAnimationStruct> AnimationStructs;

	UPROPERTY(EditAnywhere, Category = "Plateformer2D|Animation")
	TSoftObjectPtr<UDataTable> DatatablePtr;

	FAnimationStruct* CurrentAnimation;

	bool bHasPlayedFootstepSound;

	bool bHasPlayedClimbSound;


#pragma region SOUND
	UPROPERTY(EditAnywhere, Category = "Plateformer2D|Sound")
	USoundCue* WalkingSound;
	
#pragma endregion
	
};
