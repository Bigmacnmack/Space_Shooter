// Fill out your copyright notice in the Description page of Project Settings.


#include "SS_GameMode.h"

ASS_GameMode::ASS_GameMode() {

	SpawnTimer = 0.0f;

	MusicTrack = CreateDefaultSubobject<UAudioComponent>(TEXT("Music"));
	MusicTrack->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	AsteroidSpawnLoc = FVector(1000.0f, 1000.0f, 1000.0f);
	AsteroidSpawnRot = FRotator(0.0f, 0.0f, 0.0f);

	ThisWorld = GetWorld();

}


void ASS_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	MusicTrack->Play();

	bPlayerDead = false;


	//widget
	if (Score_Widget_Class != nullptr) {
		Score_Widget = CreateWidget<UUserWidget>(GetWorld(), Score_Widget_Class);
		Score_Widget->AddToViewport();
	}

	if (Shield_And_Armor_Widget_Class != nullptr) {
		Shield_Armor_Widget = CreateWidget<UUserWidget>(GetWorld(), Shield_And_Armor_Widget_Class);
		Shield_Armor_Widget->AddToViewport();
	}

	if (Restart_Widget_Class != nullptr) {
		Restart_Widget = CreateWidget<UUserWidget>(GetWorld(), Restart_Widget_Class);
		Restart_Widget->AddToViewport();

		Restart_Widget->SetVisibility(ESlateVisibility::Hidden); //뷰포트에서 보이지 않게
	}

	PC_Ref = GetWorld()->GetFirstPlayerController();

}

void ASS_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpawnTimer = FMath::RandRange(0, 1000);

	if (Enemy) {
		if (SpawnTimer > 990) {
			FVector EnemySpawnLoc(0.0f, 0.0f, 0.0f);
			FRotator EnemySpawnRot(0.0f, 0.0f, 0.0f);

			AActor* NewEnemy = GetWorld()->SpawnActor(Enemy, &EnemySpawnLoc, &EnemySpawnRot, AsteroidSpawnParameters);

			if (NewEnemy) {
				NewEnemy->SetActorLocation(FVector(1000.0f, FMath::RandRange(-500,500), 0.0f));

			}

		}
	}//spawn enemy

	if (HazardTemplate) {

		if (SpawnTimer > 995) {
			AActor* NewHazard = GetWorld()->SpawnActor(HazardTemplate, &AsteroidSpawnLoc, &AsteroidSpawnRot, AsteroidSpawnParameters);

			if (NewHazard) {
				NewHazard->SetActorLocation(FVector(1000.0f, 1000.0f, 1000.0f));
			}

		}


		if (bPlayerDead) {
			Restart_Widget->SetVisibility(ESlateVisibility::Visible);

			PC_Ref->bShowMouseCursor = true;
			bPlayerDead = false; //다시 재설정
		}




	}

}//tick



void ASS_GameMode::RestartLevel(FName LevelName)
{
}

TSubclassOf<AHazard> ASS_GameMode::GetHazardTemplate()
{
	return TSubclassOf<AHazard>();
}