// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Actor.h"
#include "EnemyFighterCPP.h"
#include "EnemySpawnerCPP.generated.h"

UCLASS()
class SPACE_API AEnemySpawnerCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnerCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawn")
		float SpawnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
		AActor* TargetActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
		UClass* ObjectToSpawn;
	

private:
	float cooldown;

	
};
