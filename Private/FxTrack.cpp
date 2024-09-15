// Fill out your copyright notice in the Description page of Project Settings.


#include "FxTrack.h"

#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"


UFxTrack::UFxTrack()
{
}

UDataTable* UFxTrack::GetDataTable()
{
	FString DataTablePath = TEXT("/Game/PlateFormer2DContent/Blueprints/Sound/DT_DataSound.DT_DataSound");
	UDataTable* DataTableObj = LoadObject<UDataTable>(nullptr, *DataTablePath);

	if (DataTableObj)
	{
		return DataTableObj;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load SoundFXDatatable"));
	}
	
	return nullptr;
}

void UFxTrack::Play2DSoundFX(UObject* WorldContextObject, ETrackSound Sound)
{
	USoundCue* SoundCue = FindSoundCueByTrackSound(Sound);
	if (SoundCue)
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundCue play EtrackSound %d"), (uint8)Sound);
		UGameplayStatics::PlaySound2D(WorldContextObject, SoundCue);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundCue not found for EtrackSound %d"), (uint8)Sound);
	}
}


USoundCue* UFxTrack::FindSoundCueByTrackSound(ETrackSound Sound)
{
	if (!GetDataTable())
	{
		UE_LOG(LogTemp, Warning, TEXT("SoundFXDatatable is null."));
		return nullptr;
	}

	static const FString ContextString(TEXT("Sound FX Data Table context"));
	TArray<FSoundFXStruct*> Rows;
	GetDataTable()->GetAllRows(ContextString, Rows);

	for (const FSoundFXStruct* Row : Rows)
	{
		if (Row && Row->TrackSound == Sound)
		{
			return Row->SoundCue;
		}
	}
	
	return nullptr;
}
