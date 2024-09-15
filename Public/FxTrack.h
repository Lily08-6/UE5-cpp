// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "FxTrack.generated.h"

UENUM(BlueprintType)
enum ETrackSound
{
	FootStepSound,
	JumpSound,
	FireSound,
	TrampolineSound,
	NotificationSound,
	CheckpointSound,
	ClimbSound,
	DamageSound,
	GameOverSound,
};

USTRUCT(BlueprintType)
struct FSoundFXStruct: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TEnumAsByte<ETrackSound> TrackSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundCue* SoundCue;
	
};


UCLASS()
class PLATEFORMER2DGAME_API UFxTrack : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFxTrack();

	UFUNCTION(BlueprintCallable, Category="Plateformer2D", meta=(WorldContext = "WorldContextObject"))
	static void Play2DSoundFX(UObject* WorldContextObject, ETrackSound Sound);

private:

	static UDataTable* GetDataTable();

	static USoundCue* FindSoundCueByTrackSound(ETrackSound Sound);
	
};
