// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazard.h"

// Sets default values
AHazard::AHazard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	AsteroidExplosionFX = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("AsteroidExplosionFX"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	AsteroidExplosionSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AsteroidExplosionSound"));

	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AsteroidExplosionFX->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AsteroidExplosionSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);


	Spawn_X_Velocity = -500.0f;
	Spawn_Y_Velocity = 0.0f;
	SelfDestructTimer = 1.0f;
	bHit = false;

}



// Called when the game starts or when spawned
void AHazard::BeginPlay()
{
	Super::BeginPlay();
	
	Initial_Rotation = 0.0f;
	Initial_X_Location = 1500.0f;
	Initial_Y_Location = FMath::RandRange(-400, 400);

	RandSize = FMath::RandRange(3, 8);
	this->SetActorScale3D(FVector(RandSize, RandSize, RandSize));

	AsteroidExplosionSound->Deactivate();
	AsteroidExplosionSound->bStopWhenOwnerDestroyed = false;

	AsteroidExplosionFX->Deactivate();

	//Bind the event
	OnActorBeginOverlap.AddDynamic(this, &AHazard::OnBeginOverlap);
}

// Called every frame
void AHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(this != nullptr);

	Initial_Rotation += DeltaTime;

	Initial_X_Location += DeltaTime * Spawn_X_Velocity;
	Initial_Y_Location += DeltaTime * Spawn_Y_Velocity;

	this->SetActorRotation(FRotator(Initial_Rotation * 100.0f, Initial_Rotation * 50.0f, 0.0f));
	this->SetActorLocation(FVector(Initial_X_Location, Initial_Y_Location, 0.0f));

	//Destroy Asteroid
	if (SelfDestructTimer <= 0.0f) {
		this->Destroy();
	}

	if (bHit) {
		bHit = false;
		bStartDestroyTimer = true;

		AsteroidExplosionFX->Activate();
		AsteroidExplosionFX->SetWorldLocation(this->GetActorLocation());
		AsteroidExplosionFX->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));

		AsteroidExplosionSound->Activate();
		AsteroidExplosionSound->Play();

		this->StaticMesh->SetVisibility(false);
		this->SetActorEnableCollision(false);

		if (this->GetActorScale3D().X > 6.0f) {

			SpawnChildren(FMath::RandRange(0,4));

		}

	}

	if (bStartDestroyTimer) {
		SelfDestructTimer -= DeltaTime;
	}

}//tick

void AHazard::SpawnChildren(int32 NumChildren)
{
	FActorSpawnParameters Params = {};
	Params.Owner = this;

	for (int i = 0; i < NumChildren; i++) {
		if (ChildSpawn != nullptr) {
			AHazard* NewHazard = Cast<AHazard>(GetWorld()->SpawnActor(ChildSpawn,
				new FVector(this->GetActorLocation()), new FRotator(this->GetActorRotation()), Params));

			NewHazard->Initial_X_Location = this->GetActorLocation().X;
			NewHazard->Initial_Y_Location = this->GetActorLocation().Y;
			NewHazard->SetHazardVelocity(FVector(FMath::RandRange(-250, 100),
				FMath::RandRange(-50, 50), 0.0f));

			float RandScale = FMath::RandRange(2, 5);

			NewHazard->SetActorScale3D(FVector(RandScale, RandScale, RandScale));

			NewHazard->SetActorEnableCollision(true);
			NewHazard->StaticMesh->SetVisibility(true);

		}
	}//for loop

}

void AHazard::SetHazardVelocity(FVector NewVelocity)
{
	Spawn_X_Velocity = NewVelocity.X;
	Spawn_Y_Velocity = NewVelocity.Y;
}

void AHazard::OnBeginOverlap(AActor* AsteroidActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Bounds")) {
		SelfDestructTimer = 0.0f;
	}

	if (OtherActor->ActorHasTag("Projectile") || OtherActor->ActorHasTag("Player")) {
		bHit = true;
	}
}//OnBeginOverlap