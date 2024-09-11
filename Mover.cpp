// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover.h"

#include "Math/UnrealMathUtility.h"

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();

	if (auto *actor = GetOwner())
	{
		OriginalLocation_ = actor->GetActorLocation();
	}
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (ShouldMove_)
	{
		Move(DeltaTime);
	}
}

void UMover::Move(float DeltaTime)
{
	if (auto *actor = GetOwner())
	{
		FVector currentLocation = actor->GetActorLocation();
		FVector targetLocation = OriginalLocation_ + MoveOffset_;
		float speed = FVector::Dist(OriginalLocation_, targetLocation) / MoveTime_;

		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, speed);
		actor->SetActorLocation(newLocation);
	}
}
