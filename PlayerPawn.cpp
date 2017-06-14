// Fill out your copyright notice in the Description page of Project Settings.


#include "Space.h"
#include "PlayerPawn.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	Ship->AttachTo(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachTo(Ship);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName);

	LeftThrusterParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleLeft"));
	LeftThrusterParticle->AttachTo(Ship);

	RightFrusterParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleRight"));
	RightFrusterParticle->AttachTo(Ship);

	ThrusterAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ThrusterAudio"));
	ThrusterAudio->AttachTo(Ship);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SetupMouse();
	SetupUI();
}

// Called every frame
void APlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	LookAtMouse();
	Reload();
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	check(InputComponent);
	
	InputComponent->BindAxis("MoveForward", this, &APlayerPawn::MoveY);
	InputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveX);
	InputComponent->BindAxis("Shoot", this, &APlayerPawn::Shoot);
}

void APlayerPawn::MoveY(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(value));
	if (value != 0)
	{
		Ship->AddForce(FVector(value*forwardSpeed*100, 0,0));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(value*forwardSpeed));
	}
}

void APlayerPawn::MoveX(float value)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(value));
	if (value != 0)
	{
		Ship->AddForce(FVector(0, value*forwardSpeed * 100, 0));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(value*forwardSpeed));
	}
}

void APlayerPawn::LookAtMouse()
{
	if (PlayerController != nullptr)
	{
		FHitResult TraceResult(ForceInit);
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, TraceResult);
		FString TraceString;
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(PlayerController->GetControlledPawn()->GetActorLocation(), FVector(TraceResult.Location.X, TraceResult.Location.Y, 230));
		//DrawDebugSphere(GetWorld(),TraceResult.Location,24,32,FColor(255, 0, 0));
		PlayerController->GetPawn()->SetActorRotation(PlayerRot);
	}

	
}

void APlayerPawn::SetupMouse()	
{
	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		PlayerController->bShowMouseCursor = true;
	}
}

void APlayerPawn::Reload()
{
	FireCoolDown += GetWorld()->GetDeltaSeconds();
	
}

void APlayerPawn::Shoot(float value)
{
	if (value != 0 && FireCoolDown > FireRate)
	{
		FVector spawnLoc;
		FVector SpawnRot;
		FActorSpawnParameters spawn = FActorSpawnParameters();
		spawnLoc = (PlayerController->GetPawn()->GetActorForwardVector() * 250) + PlayerController->GetPawn()->GetActorLocation(); 
		SpawnRot = Ship->GetForwardVector();
		AActor *LaserBullet = GetWorld()->SpawnActor<AActor>(Laser, spawnLoc, SpawnRot.Rotation());
		FireCoolDown = 0;
		//Health->DealDamage(10);
	}
}

void APlayerPawn::SetupUI()
{
	HudInstance = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), Hud);
	HudInstance->AddToViewport();
}
