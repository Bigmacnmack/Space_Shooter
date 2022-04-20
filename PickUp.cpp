// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "SS_Player.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollisionMesh = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionMesh"));

	StaticMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}



// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APickUp::OnBeginOverlap);

}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->SetActorLocation(FVector(this->GetActorLocation().X - (DeltaTime * 100.0f),
		this->GetActorLocation().Y, 0.0f));

}

void APickUp::OnBeginOverlap(AActor* PickupActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player")) {

		ASS_Player* PlayerActor = Cast<ASS_Player>(OtherActor);  //AActor로 두면 모든 actor와 충돌시 인식하게 됨
		PlayerActor->CollectablePickup();//로그 호출 함수			//Cast (형변환)을 통해 OtherActor가 플레이어에 해당할 떄만 인식하도록
		this->Destroy();
	}


	if (OtherActor->ActorHasTag("Bounds")) {
		this->Destroy();
	}
}