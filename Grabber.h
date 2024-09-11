#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:
	UGrabber();

	void Grab();

	void Release()
	{
		UE_LOG(LogTemp, Display, TEXT("Grabber - Release"));
	};

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float MaxGrabDistance_ = 400.f;

	UPROPERTY(EditAnywhere)
	float GrabRadius_ = 100.f;
};
