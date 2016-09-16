// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel the right amount this frame
	//given a max elevation speed and the frame time

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

	
	auto RawElevationChange = RelativeRotation.Pitch + ElevationChange;
	RawElevationChange = FMath::Clamp<float>(RawElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawElevationChange, 0, 0));
}

