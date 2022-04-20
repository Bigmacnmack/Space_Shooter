// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "Projectile.h"

#include "SS_Player.generated.h"

UCLASS()
class SPACE_SHOOTER_API ASS_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASS_Player();

	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ParticleSystems;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* ExplosionFX;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
		UAudioComponent* ExplosionSound;

	UPROPERTY(EditAnywhere)
		float Field_Width; //초기화 안해서 0임 실행하면 뱅기 안움직임

	UPROPERTY(EditAnywhere)
		float Field_Height;//언리얼에서 플레이어 액터 디테일에서 조정가능.

	UPROPERTY(BlueprintReadOnly)
		float Max_Health;

	UPROPERTY(BlueprintReadOnly)
		float Current_Health;

	UPROPERTY(BlueprintReadOnly)
		float Max_Armor;

	UPROPERTY(BlueprintReadOnly)
		float Current_Armor;

	void LeftRight(float AxisValue);
	void UpDown(float AxisValue);

	void FireWeapon();
	void StartFiring();
	void StopFiring();

	UPROPERTY(EditAnywhere)
		float MaxVelocity;

	bool bIsFiring;
	float WeaponFireRate;
	float TimeSinceLastShot;
	bool bHit;
	bool bDead;

	float Current_X_Velocity;
	float Current_Y_Velocity;

	UPROPERTY(BlueprintReadOnly)
		float PlayerScore;

	FVector Current_Location;
	FRotator Current_Rotation;
	FVector New_Location;

	UFUNCTION()
		void OnBeginOverlap(AActor* PlayerActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> WeaponProjectile_BP;

	void CollectablePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
