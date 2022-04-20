// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Enemy.h"
#include "Hazard.h"
#include "Blueprint/UserWidget.h"

#include "SS_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_SHOOTER_API ASS_GameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemy> Enemy;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AHazard> HazardTemplate;

	UPROPERTY(EditAnywhere)
		UAudioComponent* MusicTrack;

	//constructor
	ASS_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	TSubclassOf<AHazard> GetHazardTemplate();

public:

	int32 SpawnTimer;
	bool bPlayerDead;

	UFUNCTION()
		void RestartLevel(FName LevelName);

	bool bStart;


protected:

	FActorSpawnParameters AsteroidSpawnParameters;
	FVector AsteroidSpawnLoc;
	FRotator AsteroidSpawnRot;

	UWorld* ThisWorld;



	//add widget
	UPROPERTY(EditAnywhere, Category = "HUD Elements")
		TSubclassOf<UUserWidget> Score_Widget_Class;
	UUserWidget* Score_Widget;

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
		TSubclassOf<UUserWidget> Shield_And_Armor_Widget_Class;
	UUserWidget* Shield_Armor_Widget;

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
		TSubclassOf<UUserWidget> Restart_Widget_Class;
	UUserWidget* Restart_Widget;

	APlayerController* PC_Ref;

};
