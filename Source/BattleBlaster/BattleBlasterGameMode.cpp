// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "BattleBlasterGameInstance.h"
#include "ScreenMessage.h"
#include "Tower.h"
#include "Tank.h"

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
	TowerCount = Towers.Num();

	if (!(Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))))
	{
		UE_LOG(LogTemp, Warning, TEXT("Gamemode: Tank not found!"));
	}

	for (AActor* Actor : Towers)
	{
		if (Actor)
		{
			ATower* Tower = Cast<ATower>(Actor);
			if (Tower)
			{
				Tower->Tank = Tank;
			}
		}
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		ScreenMessageWidget = CreateWidget<UScreenMessage>(PlayerController, ScreenMessageClass);
		if (ScreenMessageWidget)
		{
			ScreenMessageWidget->AddToPlayerScreen();
			ScreenMessageWidget->SetMessageText("Get Ready!");
		}
	}

	CountdownTime = CountdownDelay;
	GetWorldTimerManager().SetTimer(
		CountdownTimerHandle,
		this,
		&ABattleBlasterGameMode::OnCountdownTimerTimeout,
		1.0f,
		false
	);

}

void ABattleBlasterGameMode::OnCountdownTimerTimeout()
{
	CountdownTime--;
	if (CountdownTime == 0)
	{
		TArray<AActor*> Towers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), Towers);
		for (AActor* Actor : Towers)
		{
			if (Actor)
			{
				ATower* Tower = Cast<ATower>(Actor);
				if (Tower)
				{
					Tower->EnableTower();
				}
			}
		}
		ScreenMessageWidget->SetMessageText("Go!");
		Tank->SetPlayerEnabled(true);
		GetWorldTimerManager().SetTimer(
			CountdownTimerHandle,
			this,
			&ABattleBlasterGameMode::OnCountdownTimerTimeout,
			1.0f,
			false
		);
	}
	else if (CountdownTime < 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ScreenMessageWidget->SetMessageText(FString::FromInt(CountdownTime));
		GetWorldTimerManager().SetTimer(
			CountdownTimerHandle,
			this,
			&ABattleBlasterGameMode::OnCountdownTimerTimeout,
			1.0f,
			false
		);
	}
}


void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	bool bIsGameOver = false;
	bIsVictory = false;

	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		bIsGameOver = true;
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TowerCount--;
		if (TowerCount <= 0)
		{
			bIsGameOver = true;
			bIsVictory = true;
		}
	}

	if (bIsGameOver)
	{
		FString GameOverString = bIsVictory ? "Victory!" : "Defeat!";
		ScreenMessageWidget->SetMessageText(GameOverString);
		ScreenMessageWidget->SetVisibility(ESlateVisibility::Visible);

		UE_LOG(LogTemp, Display, TEXT("Game over: %s"), *GameOverString);
		FTimerHandle GameOverTimerHandle;

		GetWorldTimerManager().SetTimer(
			GameOverTimerHandle,
			this,
			&ABattleBlasterGameMode::OnGameOverTimeout,
			GameOverDelay,
			false
		);
	}
}

void ABattleBlasterGameMode::OnGameOverTimeout()
{
	UGameInstance* GameInstance = GetGameInstance();
	if(GameInstance)
	{
		UBattleBlasterGameInstance* BattleBlasterGameInstance = Cast<UBattleBlasterGameInstance>(GameInstance);
		if(BattleBlasterGameInstance)
		{
			if(bIsVictory)
			{
				BattleBlasterGameInstance->LoadNextLevel();
			}
			else
			{
				BattleBlasterGameInstance->RestartCurrentLevel();
			}
		}
	}
	
}
