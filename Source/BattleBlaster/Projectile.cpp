// Copyright Epic Games, Inc. All Rights Reserved.

#include "Projectile.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"


// Sets default values
AProjectile::AProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    if (!RootComponent)
    {
        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
    }

    if (!CollisionComponent)
    {
        // Use a sphere as a simple collision representation.
        CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
        // Set the sphere's collision profile name to "Projectile".
        CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
        // Event called when component hits something.
        CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
        // Set the sphere's collision radius.
        CollisionComponent->InitSphereRadius(15.0f);
        // Set the root component to be the collision component.
        RootComponent = CollisionComponent;
    }

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
        ProjectileMovementComponent->InitialSpeed = 1000.0f;
        ProjectileMovementComponent->MaxSpeed = 1000.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = false;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }

    if (!ProjectileMeshComponent)
    {
        ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
        ProjectileMeshComponent->SetupAttachment(RootComponent);
    }
    // Delete the projectile after 3 seconds.
    InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
    Super::BeginPlay();
    if (LaunchSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
    }

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Function that initializes the projectile's velocity in the shoot direction.
void AProjectile::FireInDirection(const FVector& ShootDirection)
{
    ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;

}

// Function that is called when the projectile hits something.
void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("HIT!!!!!!"));
    if (OtherActor &&
        OtherActor != this &&
        OtherComponent &&
        OtherActor != GetOwner())
    {
        if (OtherComponent->IsSimulatingPhysics())
        {
            OtherComponent->AddImpulseAtLocation(
                ProjectileMovementComponent->Velocity * 100.0f,
                Hit.ImpactPoint
            );
        }
        if (OtherActor->CanBeDamaged())
        {
            UGameplayStatics::ApplyDamage(
                OtherActor,
                Damage,                 // Damage amount
                GetInstigatorController(),
                this,
                UDamageType::StaticClass()
            );
        }

    }
    if (HitSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
    }
    if (HitEffect)
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            HitEffect,
            Hit.ImpactPoint,
            Hit.ImpactNormal.Rotation()
        );
    }
    if (HitCameraShakeClass)
    {
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PlayerController)
        {
            PlayerController->ClientStartCameraShake(HitCameraShakeClass);
        }
    }
    Destroy();
}