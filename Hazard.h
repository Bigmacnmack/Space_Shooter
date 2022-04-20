// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "Hazard.generated.h"

UCLASS()
class SPACE_SHOOTER_API AHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHazard();

	void SpawnChildren(int32 NumChildren);
	void SetHazardVelocity(FVector NewVelocity);

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
		UAudioComponent* AsteroidExplosionSound;

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* AsteroidExplosionFX;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AHazard> ChildSpawn;

	UFUNCTION()
		void OnBeginOverlap(AActor* AsteroidActor, AActor* OtherActor);

	float Initial_Rotation;
	float Initial_X_Location;
	float Initial_Y_Location;
	float RandSize;

	float SelfDestructTimer;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Velocity;

	float Spawn_Y_Velocity;

	bool bHit;
	bool bStartDestroyTimer;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
