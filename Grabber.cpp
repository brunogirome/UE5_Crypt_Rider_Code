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
		PhysicsHandle_ = physicsHandle;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGrabber::BeginPlay - Can't get the physics handle component."));
	}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PhysicsHandle_)
	{
		return;
	}

	if (PhysicsHandle_->GetGrabbedComponent())
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance_;
		PhysicsHandle_->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}
}

void UGrabber::Grab()
{
	if (!PhysicsHandle_)
	{
		return;
	}

	FHitResult hitResult;
	if (GetGrabbableInReach(hitResult))
	{
		UPrimitiveComponent *hitComponent = hitResult.GetComponent();
		if (hitComponent)
		{
			hitComponent->WakeAllRigidBodies();

			PhysicsHandle_->GrabComponentAtLocationWithRotation(
					hitComponent,
					NAME_None,
					hitResult.ImpactPoint,
					GetComponentRotation());
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Grab nothing"));
	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle_)
	{
		return;
	}

	if (UPrimitiveComponent *grabbedComponent = PhysicsHandle_->GetGrabbedComponent())
	{
		grabbedComponent->WakeAllRigidBodies();
		PhysicsHandle_->ReleaseComponent();
	}
}

bool UGrabber::GetGrabbableInReach(FHitResult &OutHitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * MaxGrabDistance_;

	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5.f);

	FCollisionShape shpere = FCollisionShape::MakeSphere(GrabRadius_);
	return GetWorld()->SweepSingleByChannel(
			OutHitResult,
			start,
			end,
			FQuat::Identity,
			ECC_GameTraceChannel2,
			shpere);
}