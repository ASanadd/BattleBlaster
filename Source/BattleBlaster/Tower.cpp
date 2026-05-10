// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();	

}

void ATower::EnableTower()
{
	StartFireTimer();
}

ATower::ATower()
{

}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank && Tank->IsAlive && IsInFireRange())
	{
			RotateTurret(Tank->GetActorLocation());
	}
	
}


void ATower::CheckFireCondition()
{
	if (Tank && Tank->IsAlive && IsInFireRange())
	{
		FVector ToTarget = Tank->GetActorLocation() - TurretMesh->GetComponentLocation();
		FRotator TargetRotation = ToTarget.Rotation();
		FRotator CurrentRotation = TurretMesh->GetComponentRotation();
		float YawDifference = FMath::Abs(
			FMath::FindDeltaAngleDegrees(
				CurrentRotation.Yaw,
				TargetRotation.Yaw
			)
		);

		if (YawDifference < 5.f)
		{
			Fire();
			FireRate = 2.0f;
			StartFireTimer();
		}
		else
		{
			FireRate = 0.1f;
			StartFireTimer();
		}
	}
	else
	{
		FireRate = 0.1f;
		StartFireTimer();
	}
}

bool ATower::IsInFireRange()
{
	bool Result = false;

	if (Tank)
	{
		float DistanceToTank = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		Result = (DistanceToTank <= FireRange);
	}

	return Result;
}

// Called to bind functionality to input
void ATower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATower::StartFireTimer()
{
	GetWorldTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		false
	);
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	this->Destroy();
}

