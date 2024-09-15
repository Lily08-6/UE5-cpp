// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatWidget.h"
#include "HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void UPlayerStatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UPlayerStatWidget::InitHealthWidget, 0.3f, false);
}

void UPlayerStatWidget::InitHealthWidget()
{
	if (ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0))
	{
		if (UHealthComponent* HealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>())
		{
			const float Health = HealthComponent->GetHealth();
			const float MaxHealth = HealthComponent->GetDefaultHealth();

			UpdateHealthBar(Health, MaxHealth);
			
		}
	}
}

void UPlayerStatWidget::UpdateHealthBar(float Health, float MaxHealth)
{
	if (Health >= 0.f && MaxHealth >= 0.f)
	{
		const float Percent = Health / MaxHealth;
		PlayerHealthBar->SetPercent(Percent);
	}
}

void UPlayerStatWidget::UpdateNbGem(float Gem)
{
	NbGem->SetText(FText::AsNumber(Gem));
}
