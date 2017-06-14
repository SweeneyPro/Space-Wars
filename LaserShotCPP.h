// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LaserShotCPP.generated.h"


UCLASS()
class SPACE_API ALaserShotCPP : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALaserShotCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* LaserMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Audio")
	class UAudioComponent* LaserAudio;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Collision")
	class UClass* CollisionExplosion;

	UFUNCTION()
	void OnOverlap(AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

  

};
