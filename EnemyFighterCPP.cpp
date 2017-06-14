// Fill out your copyright notice in the Description page of Project Settings.
#include "Space.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "PlayerPawn.h"
#include "EnemyFighterCPP.h"

// Sets default values
AEnemyFighterCPP::AEnemyFighterCPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	Ship->AttachTo(RootComponent);

	LeftThrusterParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleLeft"));
	LeftThrusterParticle->AttachTo(Ship);

	RightFrusterParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleRight"));
	RightFrusterParticle->AttachTo(Ship);

	Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	
}

// Called when the game starts or when spawned
void AEnemyFighterCPP::BeginPlay()
{
	Super::BeginPlay();
	AIController = UAIBlueprintHelperLibrary::GetAIController(Cast<AActor>(this));

}

// Called every frame
void AEnemyFighterCPP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	if (Target != nullptr)
	{
		
		MoveToTarget();
		Reload();
	}
	
	
	
}

// Called to bind functionality to input
void AEnemyFighterCPP::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AEnemyFighterCPP::MoveToTarget()
{
	FVector loc = FVector(Target->GetActorLocation().X, Target->GetActorLocation().Y, 250.0f);
	AIController->MoveToLocation(loc, 500.0f, true, true, false, false);
}

void AEnemyFighterCPP::Reload()
{
	FireCoolDown += GetWorld()->GetDeltaSeconds();
	if (FireCoolDown >= FireRate)
	{
		Aim();
	}
}

void AEnemyFighterCPP::Shoot()
{

	FVector spawnLoc;
	FVector SpawnRot;
	FActorSpawnParameters spawn = FActorSpawnParameters();
	FVector fwd = UKismetMathLibrary::GetForwardVector(GetActorRotation());
	spawnLoc = GetActorLocation() + fwd * 150;
	SpawnRot = Ship->GetForwardVector();
	AActor *LaserBullet = GetWorld()->SpawnActor<AActor>(Laser, spawnLoc, SpawnRot.Rotation());
	FireCoolDown = 0;
}

void AEnemyFighterCPP::Aim()
{

	FVector fwd = UKismetMathLibrary::GetForwardVector(GetActorRotation());
	//DrawDebugLine(GetWorld(), GetActorLocation(), GetActorLocation() + fwd * 3000, FColor::Red, false, 0.0f);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bTraceAsyncScene = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	FHitResult RV_Hit(ForceInit);

	GetWorld()->LineTraceSingle(RV_Hit, GetActorLocation(), GetActorLocation() + fwd * 3000, ECC_Pawn, RV_TraceParams);

	if (Cast<APlayerPawn>(RV_Hit.GetActor()))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (RV_Hit.Actor->GetName()));
		Shoot();
	}
}

void AEnemyFighterCPP::Points()
{
	Cast<APlayerPawn>(Target)->score += 10;
}


