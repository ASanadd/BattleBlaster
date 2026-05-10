// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
class ATank;

UCLASS()
class BATTLEBLASTER_API ATower : public ABasePawn
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ATower();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	ATank* Tank;

	UPROPERTY(EditAnywhere)
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere)
	float FireRate = 2.0f;
	FTimerHandle FireTimerHandle;

	void EnableTower();

	void CheckFireCondition();
	bool IsInFireRange();
	void StartFireTimer();
	virtual void HandleDestruction() override;
}; 
