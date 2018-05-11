// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"

#include "TankAIController.h"


ATank* ATankAIController::GetControllerTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerPawn = GetTankPlayer();
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can not player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AiController found palyer: %s"), *(PlayerPawn->GetName()));
	}
}

ATank* ATankAIController::GetTankPlayer() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}
		return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector HitLocation;
	if (GetTankPlayer())
	{
		GetControllerTank()->AimAt(GetTankPlayer()->GetActorLocation());
	}

}
