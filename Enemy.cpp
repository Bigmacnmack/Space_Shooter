// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionFX"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	ExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionSound"));

	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	fBurstDelay = 0.15f;

	
	
}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	TotalTime = 0.0f;
	TimeSinceLastShoot = 0.0f;
	bHit = false;
	bDestroy = false;

	fDestroyTimer = 1.0f;

	ExplosionFX->Deactivate();
	ExplosionSound->Deactivate();

	ThisWorld = GetWorld();

	RandomStart = FMath::Rand();

	OnActorBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
	//this class 와 &AEnemy::OnBeginOverlap를 묶는다
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TotalTime += DeltaTime;
	TimeSinceLastShoot += DeltaTime;

	CurrentLocation = this->GetActorLocation();
	CurrentRotation = this->GetActorRotation();

	CurrentLocation.Y += FMath::Sin(TotalTime + RandomStart);

	/*UE_LOG(LogTemp, Warning, TEXT("ANYTHING"));*/

	this->SetActorLocation(CurrentLocation - (CurrentVelocity * DeltaTime));


	//handle shooting
	if (TimeSinceLastShoot >= 0.8f && !bHit) {
		if (fBurstDelay >= 0.5f) {
			FActorSpawnParameters Params = {};
			Params.Owner = this;
			GetWorld()->SpawnActor(EnemyProjectile, &CurrentLocation, &CurrentRotation, Params);

			fBurstDelay = 0.0f;
		}
		TimeSinceLastShoot = 0.0f;
		fBurstDelay += DeltaTime;
	}//handle shooting

	
	 
	 //handle destroying

	if (bDestroy) {
		this->Destroy();
	}

	if (bHit) {
		StaticMesh->SetVisibility(false);
		this->SetActorEnableCollision(false);
		ExplosionFX->Activate();
		ExplosionSound->Activate();

		fDestroyTimer -= DeltaTime;
	}

	if (fDestroyTimer <= 0.0f) {
		this->Destroy();
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnBeginOverlap(AActor* EnemyActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Bounds")) {

		bDestroy = true;

	}
	
	if (OtherActor->ActorHasTag("Asteroid")|| OtherActor->ActorHasTag("Player")) {
		//Enemy도 운석에 박으면 터지도록
		bHit = true;

	}

	if (OtherActor->ActorHasTag("Projectile")) {

		bHit = true;

		if (ThisWorld) {
			
			if (FMath::RandRange(0, 10) > 7) {

				FVector Current_Location = this->GetActorLocation();
				FRotator Current_Rotation = this->GetActorRotation();
				FActorSpawnParameters Params= {};

				ThisWorld->SpawnActor(PickupCan, &Current_Location, &Current_Rotation, Params);

			}


		}

	}



}
