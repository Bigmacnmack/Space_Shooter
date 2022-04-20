// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "SS_Player.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	BulletComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletComponent"));
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	
	
	BulletComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CapsuleCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	ProjectileSpeed = 0.0f;

	bHit = false;
	bDestroy = false;
}



// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentLocation = this->GetActorLocation();

	OnActorBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
	
	//
	fDestroyTimer = 3.0f;
	//
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = FVector(CurrentLocation.X + (ProjectileSpeed * DeltaTime),
		CurrentLocation.Y,CurrentLocation.Z);

	this->SetActorLocation(NewLocation);
	CurrentLocation = NewLocation;
	
	//
	fDestroyTimer -= DeltaTime;
	if (fDestroyTimer < 0.0f) {
		this->Destroy();
	}
	//
	
	if (bHit) {
		this->Destroy();
	}

}

void AProjectile::OnBeginOverlap(AActor* ProjectileActor, AActor* OtherActor)
{
	

	if (OtherActor) // OtherActor!=nullptr과 같은 의미
	{
		ASS_Player* OwningPlayer = Cast<ASS_Player>(this->GetOwner()); //플레이어가 쏜 것만 유효하게 만들기

		if (OtherActor->ActorHasTag("Bounds"))	//ActorHasTag(FName("Bounds")))과 동일함
			bHit = true;

		if (OtherActor->ActorHasTag("Iron"))	//Player 발사체를 없애주자
			this->Destroy();

		if (this->ActorHasTag("EnemyProjectile")&& OtherActor->ActorHasTag("Player")) { //발사체가 EnemyProjectile이고 Player일 때
			bHit = true;
		}


		if (OtherActor->ActorHasTag("EnemyShip")) {
			if (OwningPlayer)
				OwningPlayer->PlayerScore += 50.0f;

			bHit = true;
		}

		if (OtherActor->ActorHasTag("Asteroid")) {
			if (OwningPlayer)
				OwningPlayer->PlayerScore += 50.0f;

			bHit = true;
		}
	}


}