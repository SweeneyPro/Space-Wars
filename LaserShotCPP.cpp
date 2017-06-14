// Fill out your copyright notice in the Description page of Project Settings.

#include "Space.h"
#include "HealthComponent.h"
#include "LaserShotCPP.h"


// Sets default values
ALaserShotCPP::ALaserShotCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
	LaserMesh->AttachTo(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->AttachTo(LaserMesh);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALaserShotCPP::OnOverlap);

	LaserAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	LaserAudio->AttachTo(LaserMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	


}

// Called when the game starts or when spawned
void ALaserShotCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALaserShotCPP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ALaserShotCPP::OnOverlap(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UHealthComponent* health = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));

	if (health != nullptr)
	{
		health->DealDamage(10.0f);
		
		
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FString(OtherActor->GetName()));	
	AActor *explosion = GetWorld()->SpawnActor<AActor>(CollisionExplosion, GetActorLocation(), GetActorRotation());

	Destroy();
}
