#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:
	UGrabber();

	void Grab();

	void Release();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UPhysicsHandleComponent *PhysicsHandle_;

	UPROPERTY(EditAnywhere)
	float MaxGrabDistance_ = 400.f;

	UPROPERTY(EditAnywhere)
	float GrabRadius_ = 100.f;

	UPROPERTY(EditAnywhere)
	float HoldDistance_ = 200.f;

	bool GetGrabbableInReach(FHitResult &OutHitResult) const;
};
