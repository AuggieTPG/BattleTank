// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"



ATank* ATankAIController::GetPlayerTank() const
{
	
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!playerPawn)
	{
		return nullptr;
	}

	return Cast<ATank>(playerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
	//declare a tank class variable for playertank
	ATank* playerTank;

	//get the Pawn attached to the player controller
	playerTank = GetPlayerTank();

	//Make sure we don't have a null pointer

	if (!playerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Pointer Error when trying to get pointer to tank>pawn"));

	}
	else
	{

		FString playerTankName = playerTank->GetName();

		UE_LOG(LogTemp, Warning, TEXT("Found the player Tank %s"), *playerTankName);
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return	Cast<ATank>(GetPawn());
}


