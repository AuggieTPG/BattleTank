// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// move the barrel the right amount this frame
	//given a max elevation speed and the frame time
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond + GetWorld()->DeltaTimeSeconds;

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RawElevationChange = RelativeRotation.Pitch + ElevationChange;

	RawElevationChange = FMath::Clamp<float>(RawElevationChange, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(RawElevationChange, 0, 0));
}

