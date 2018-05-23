// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();



}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)){return;}
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);


	}
}

void ATankAIController::OnPossedTankDeath()
{
	if (!ensure(GetPawn())){return;}
	//AI坦克死后，失去AI控制，不能再移动或是开火
	GetPawn()->DetachFromControllerPendingDestroy();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank= GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank&& ControlledTank)) { return; }
	
		// TODO Move towards the player

		MoveToActor(PlayerTank, AcceptanceRadius);
		//UE_LOG(LogTemp, Warning, TEXT("ControlledTank: %s"),*(ControlledTank->GetName()));
		// Aim towards the player
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetFiringState()==EFiringState::Locked)
		{
			AimingComponent->Fire();
		}

		// Fire if ready
	
}


