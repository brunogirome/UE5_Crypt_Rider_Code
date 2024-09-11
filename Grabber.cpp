#include "DrawDebugHelpers.h"

#include "Grabber.h"

#include "Engine/World.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent *physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandle)
	{
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGrabber::BeginPlay - Can't get the physics handle component."));
	}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance_;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5.f);

	FCollisionShape shpere = FCollisionShape::MakeSphere(GrabRadius_);
	FHitResult hitResult;
	bool hasHit = GetWorld()->SweepSingleByChannel(
			hitResult,
			start,
			end,
			FQuat::Identity,
			ECC_GameTraceChannel2,
			shpere);

	if (hasHit)
	{
		DrawDebugSphere(GetWorld(), hitResult.Location, 10, 10, FColor::Yellow, false, 5.f);
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Green, false, 5.f);

		UE_LOG(LogTemp, Display, TEXT("Hit result: %s"), *hitResult.GetActor()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Grab nothing"));
	}
}
