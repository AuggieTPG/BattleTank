// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
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

	//get the pawn attached to this enemy tank controller
	ATank* enemyTank = GetAIControlledTank();

	//Make sure we don't have a null pointer on player tank
	if (!playerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Pointer Error when trying to get pointer to tank>pawn"));

	}
	else
	{
		FString playerTankName = playerTank->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Found the player Tank %s"), *playerTankName);		
	
	}
	//Make sure we don't have a null pointer on player tank
	if (!enemyTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Pointer Error when trying to get pointer to enemytank>pawn"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found enemy Tank named: %s"), *enemyTank->GetName());
	}	
}

void ATankAIController::Tick(float DeltaSeconds)
{

	Super::Tick(DeltaSeconds);

	//get the Pawn attached to the player controller
	ATank* playerTank = GetPlayerTank();
	//get our enemy tank pawn
	ATank* enemyTank = GetAIControlledTank();

	if (playerTank)
	{
		//TODO move towatrd player


		//Aim at player
		enemyTank->AimAt(playerTank->GetActorLocation());

		//Fire if ready
	}


	

}

ATank* ATankAIController::GetAIControlledTank() const
{
	return	Cast<ATank>(GetPawn());
}


