// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLATEFORMER2DGAME_API UPlayerStatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	void InitHealthWidget();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=( BindWidget ), Category="Plateformer2D|Widget")
	class UProgressBar* PlayerHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=( BindWidget ), Category="Plateformer2D|Widget")
	class UTextBlock* NbGem;

	UFUNCTION(BlueprintCallable, Category="Plateformer2D|Widget")
	void UpdateHealthBar(float Health, float MaxHealth);

	UFUNCTION(BlueprintCallable, Category="Plateformer2D|Widget")
	void UpdateNbGem(float Gem);

private:

	FTimerHandle TimerHandle;
	
};
