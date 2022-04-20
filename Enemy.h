// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Projectile.h"
#include "PickUp.h"

#include "Enemy.generated.h"

UCLASS()
class SPACE_SHOOTER_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
		UAudioComponent* ExplosionSound;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> EnemyProjectile;

	UWorld* ThisWorld;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APickUp> PickupCan;

	UPROPERTY(EditAnywhere)
		FVector CurrentVelocity;

	float TotalTime;
	float TimeSinceLastShoot;
	float RandomStart;

	bool bHit;
	bool bDestroy;

	float fDestroyTimer;
	float fBurstDelay;

	FVector CurrentLocation;
	FRotator CurrentRotation;

	UFUNCTION()
		void OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
