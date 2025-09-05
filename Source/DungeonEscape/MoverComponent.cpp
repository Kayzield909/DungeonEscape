// Fill out your copyright notice in the Description page of Project Settings.


#include "MoverComponent.h"

#include "Math/UnrealMathUtility.h" // Include Directive

// Sets default values for this component's properties
UMoverComponent::UMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.SetTickFunctionEnable(false);
	// ...
}


// Called when the game starts
void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + MoveOffset;

	// SetMovementEnabled(bMovementEnabled, bReverseMovement);
}


// Called every frame
void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// 

	// Move Owner using Interpolation from Start to Target Location

	if (bMovementEnabled)
	{
		FVector CurrentLocation = GetOwner()->GetActorLocation();

		// bTargetReached = CurrentLocation.Equals(TargetLocation); 
		// // IMPROVEMENT: Use tolerance calc via DistanceSquared < 1.0f to solve floating-point precision
		float DistanceSquared = FVector::DistSquared(CurrentLocation, TargetLocation);
		bTargetReached = DistanceSquared < 1.0f;

		if (!bTargetReached)
		{
			float InterpSpeed = MoveOffset.Length() / MoveTime; //InterpSpeed name ok as passing to external scope

			FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);

			GetOwner()->SetActorLocation(NewLocation);
		}
		else
		{
			SetMovementEnabled(false, !bReverseMovement);
		}
		
	}
}

void UMoverComponent::SetMovementEnabled(bool Enabled, bool Reverse)
{
	bMovementEnabled = Enabled;
	bReverseMovement = Reverse;
	SetComponentTickEnabled(bMovementEnabled);

	// Change TargetLocation based on bReverseMovement
	if (bReverseMovement)
	{
		TargetLocation = StartLocation; //Reverse Mode
	}
	else
	{
		TargetLocation = StartLocation + MoveOffset; //Forward Mode
	}
}

