// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Has Started"));

	//declare a tank class variable
	ATank* MyTank;

	//get the Pawn attached to the player controller
	MyTank = GetControlledTank();

	//Make sure we don't have a null pointer

	if (!MyTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Pointer Error when trying to get pointer to tank>pawn"));

	}
	else
	{
		FString myTankName = MyTank->GetName();

		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController is controlling Tank %s"), *myTankName);
	}




}
//tick
	//super
	

void ATankPlayerController::Tick(float  DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick Tock"));
	AimTowardsCrossHair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return	Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation))// Hs side effect , is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location look direction =: %s"), *HitLocation.ToString());
		//Get world world location through crosshair with Linetrace

		//If hits the landscape
		//TODO Tell controlled tank to aim at this point
	}
	

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;

	//Crosshair location 
	//float CrossHairX = 0.5f;
	//float CrossHairY = 0.33333f;

	FVector2D ScreenLocation;

	//Get the size of viewport
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	//find the pixel x,y location of our crosshair calculated from the current viewportsize
	ScreenLocation.X = ViewportSizeX * CrossHairX;
	ScreenLocation.Y = ViewportSizeY * CrossHairY;

	//UE_LOG(LogTemp, Warning, TEXT("CrossHair is located at screen position : %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("World Position of crosshair: %s"), *LookDirection.ToString());
	}

	return true;
	
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	//Deproject the screen position of the crosshair to a world direction
	FVector FVcamera, FVworldPosition;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, FVcamera, FVworldPosition);
	
	

	//Line trace along the look direction
	return true;
	
	
}
