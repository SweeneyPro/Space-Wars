// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HealthComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "EnemyFighterCPP.generated.h"

UCLASS()
class SPACE_API AEnemyFighterCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyFighterCPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// variables
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float forwardSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	AActor* Target;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
	class UClass* Laser;

private:
	float FireCoolDown;
	AAIController* AIController;
	FHitResult* hit;
	UKismetSystemLibrary* math;


	// components
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* Ship;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Particle")
	class UParticleSystemComponent* LeftThrusterParticle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Particle")
	class UParticleSystemComponent* RightFrusterParticle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Health")
	class UHealthComponent* Health;

	UFUNCTION()
		void Points();

private:
	void MoveToTarget();
	void Shoot();
	void Reload();
	void Aim();
};
