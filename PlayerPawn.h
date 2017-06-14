// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "HealthComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SPACE_API APlayerPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Variables
public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float forwardSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
		float score;

private:
		class APlayerController* PlayerController;
		float FireCoolDown;
	//Components
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* Ship;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Particle")
		class UParticleSystemComponent* LeftThrusterParticle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Particle")
		class UParticleSystemComponent* RightFrusterParticle;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Audio")
		class UAudioComponent* ThrusterAudio;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Health")
		class UHealthComponent* Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
		class UClass* Laser;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
			TSubclassOf<class UUserWidget> Hud;

	UUserWidget* HudInstance;

private:
		void MoveY(float value);
		void MoveX(float value);
		void LookAtMouse();
		void SetupMouse();
		void Reload();
		void Shoot(float value);
		void SetupUI();
};
