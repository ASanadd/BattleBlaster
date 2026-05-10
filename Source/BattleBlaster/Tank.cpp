// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
	SetPlayerEnabled(false);
}

ATank::ATank()
{
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->SetupAttachment(BaseMesh);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}

	if (bIsDashing)
	{
		if (SpringArmComp) // ← null check just in case
		{
			SpringArmComp->bInheritYaw = false;
		}
		PerformDash(DeltaTime);
	}
	else
	{
		if (SpringArmComp)
		{
			SpringArmComp->bInheritYaw = true;
		}
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
		EIC->BindAction(RotateAction, ETriggerEvent::Triggered, this, &ATank::RotateInput);
		EIC->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::FireInput);
		EIC->BindAction(DashAction, ETriggerEvent::Started, this, &ATank::DashInput);
		EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &ATank::SprintStart);
		EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &ATank::SprintStop);
	}


}

void ATank::MoveInput(const FInputActionValue& Value)
{
	if (bIsDashing) return;

	float InputValue = Value.Get<float>();
	CurrentMoveInput.X = InputValue; // ← forward/back
	float CurrentSpeed = bIsSprinting ? SprintSpeed : MoveSpeed;
	AddActorLocalOffset(FVector(InputValue * CurrentSpeed * GetWorld()->GetDeltaSeconds(), 0, 0), true);
}

void ATank::RotateInput(const FInputActionValue& Value)
{
	if (bIsDashing) return;

	float InputValue = Value.Get<float>();
	CurrentMoveInput.Y = InputValue; // ← left/right
	AddActorLocalRotation(FRotator(0, InputValue * RotationSpeed * GetWorld()->GetDeltaSeconds(), 0), true);
}

void ATank::FireInput(const FInputActionValue& Value)
{
	Fire();
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);

	IsAlive = false;
}


void ATank::SetPlayerEnabled(bool Enabled)
{
	if (PlayerController)
	{
		if (Enabled)
		{
			EnableInput(PlayerController);
		}
		else
		{
			DisableInput(PlayerController);
		}
		PlayerController->SetShowMouseCursor(Enabled);
	}
}

void ATank::DashInput(const FInputActionValue& Value)
{
	if (!bCanDash || bIsDashing) return;

	// Build dash direction from current WASD input in world space
	FVector Forward = GetActorForwardVector() * CurrentMoveInput.X;
	FVector Right = GetActorRightVector() * CurrentMoveInput.Y;
	FVector InputDirection = (Forward + Right).GetSafeNormal();

	// Fall back to forward if no input is held
	DashDirection = InputDirection.IsZero()
		? GetActorForwardVector()
		: InputDirection;

	bIsDashing = true;
	bCanDash = false;
	DashElapsed = 0.f;
}

void ATank::PerformDash(float DeltaTime)
{
	DashElapsed += DeltaTime;
	float Alpha = DashElapsed / DashDuration;

	if (Alpha >= 1.f)
	{
		bIsDashing = false;

		// ← No FTimerHandle here, use the member variable from the header
		GetWorldTimerManager().SetTimer(
			DashCooldownHandle,
			[this]() { bCanDash = true; },
			DashCooldown,
			false
		);
		return;
	}

	float DistanceThisFrame = (DashDistance / DashDuration) * DeltaTime;
	AddActorWorldOffset(DashDirection * DistanceThisFrame, true);

	float SpinThisFrame = DashSpinSpeed * DeltaTime;
	AddActorLocalRotation(FRotator(0.f, SpinThisFrame, 0.f));
}

void ATank::SprintStart(const FInputActionValue& Value)
{
	bIsSprinting = true;
}

void ATank::SprintStop(const FInputActionValue& Value)
{
	bIsSprinting = false;
}
