// Fill out your copyright notice in the Description page of Project Settings.

#include "Space.h"
#include "HealthComponent.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyFighterCPP.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Health = MaxHealth;
	CheckHealth();	//REMOVE ON COMPLETION
	
}


// Called every frame
void UHealthComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UHealthComponent::DealDamage(float damage)
{
	Health -= damage;
	CheckHealth();
}

/*Spawn all objects in OnDeathSpawn array and then destroy owner*/
void UHealthComponent::CheckHealth()
{
	if (Health <= 0)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController());
		AAIController* AIController = Cast<AAIController>(Cast<APawn>(GetOwner())->GetController());
		if (PlayerController)
		{
			MyGameOverWidget = CreateWidget<UUserWidget>(GetWorld()->GetGameInstance(), GameOverWidget);
			MyGameOverWidget->AddToViewport();
			GetOwner()->Destroy();
		}
		else if (AIController)
		{
			for (int i = 0; i < OnDeathSpawn.Num(); i++)
			{
				
				int ran = FMath::FRandRange(0, 5);
				if (ran == 1)
				AActor* spawn = GetWorld()->SpawnActor<AActor>(OnDeathSpawn[i], GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
			}
			Cast<AEnemyFighterCPP>(GetOwner())->Points();

			GetOwner()->Destroy();
		}
		else
		{
			//	TODO
		}
		
	}
}

void UHealthComponent::Heal(float healValue)
{
	Health += healValue;
	if (Health > MaxHealth) Health = MaxHealth;
}

