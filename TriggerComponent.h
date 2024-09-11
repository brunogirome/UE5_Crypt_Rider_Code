
#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"

// #include "Mover.h"

#include "TriggerComponent.generated.h"

class UMover;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMover(UMover *NewMover);

private:
	UPROPERTY(EditAnywhere)
	FName UnlockTagName_;

	UMover *Mover_;

	AActor *GetUnlockerActor() const;
};
