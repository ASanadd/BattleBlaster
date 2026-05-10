// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bIsSprinting = false;
	bool bIsDashing = false;
	bool bCanDash = true;
	FVector DashDirection;
	float DashElapsed = 0.f;

public:
	ATank();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;


	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RotateAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	// Dash
	UPROPERTY(EditAnywhere, Category = "Movement")
	float DashDistance = 600.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DashDuration = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DashCooldown = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DashSpinSpeed = 1080.f; // degrees per second during dash

	// Sprint
	UPROPERTY(EditAnywhere, Category = "Movement")
	float SprintSpeed = 600.f; // separate from MoveSpeed

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 300;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 300;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	APlayerController* PlayerController;
	FTimerHandle DashCooldownHandle;
	FVector2D CurrentMoveInput = FVector2D::ZeroVector;

	bool IsAlive = true;

	void MoveInput(const FInputActionValue& Value);
	void RotateInput(const FInputActionValue& Value);
	void FireInput(const FInputActionValue& Value);
	virtual void HandleDestruction() override;
	void SetPlayerEnabled(bool Enabled);
	void DashInput(const FInputActionValue& Value);
	void SprintStart(const FInputActionValue& Value);
	void SprintStop(const FInputActionValue& Value);
	void PerformDash(float DeltaTime);
};