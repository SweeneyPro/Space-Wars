// Fill out your copyright notice in the Description page of Project Settings.

#include "Space.h"
#include "HealthComponent.h"
#include "PlayerPawn.h"
#include "HealthRestore.h"


// Sets default values
AHealthRestore::AHealthRestore()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->AttachTo(RootComponent);

	BallCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BallCollision"));
	BallCollision->AttachTo(BallMesh);
	BallCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealthRestore::OnOverlap);

}

// Called when the game starts or when spawned
void AHealthRestore::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthRestore::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AHealthRestore::OnOverlap(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FString(OtherActor->GetName()));

	UHealthComponent* health = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
	//APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(OtherActor)->GetController());

	//APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
	APlayerPawn* kek = Cast<APlayerPawn>(OtherActor);
	if (health != nullptr && kek != nullptr)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FString(PlayerController->GetName()));

		health->Heal(20.0f);
		Destroy();

	}

	

}

