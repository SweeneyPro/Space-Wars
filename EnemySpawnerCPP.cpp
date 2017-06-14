// Fill out your copyright notice in the Description page of Project Settings.

#include "Space.h"
#include "EnemySpawnerCPP.h"


// Sets default values
AEnemySpawnerCPP::AEnemySpawnerCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawnerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawnerCPP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	cooldown += DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(cooldown));
	if (cooldown > SpawnRate)
	{
		AActor *SpawnObj = GetWorld()->SpawnActor<AActor>(ObjectToSpawn, GetActorLocation(), GetActorRotation());

		AEnemyFighterCPP* enemy = Cast<AEnemyFighterCPP>(SpawnObj);
		enemy->Target = TargetActor;
		//Cast<AEnemyFighterCPP>(SpawnObj)->Target = TargetActor;
		cooldown = 0;
	}
}



