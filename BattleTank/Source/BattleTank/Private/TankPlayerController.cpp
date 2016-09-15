// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
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
		
		//Get world world location through crosshair with Linetrace
		
		
		//Tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
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

	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
	
		GetLookVectorHitLocation(LookDirection, HitLocation);

	}

	return true;
	
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult myHitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);


	if (GetWorld()->LineTraceSingleByChannel(
		myHitResult, 
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		//hit on the landscape or object
		HitLocation = myHitResult.Location;
		
		return true;
	}
	else
	{
		//No hit
		HitLocation = FVector(0, 0, 0);
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	//Deproject the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
	
	

	//Line trace along the look direction
	return true;
	
	
}

