// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:
	UMover();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void SetShouldMove(bool ShouldMove);

private:
	UPROPERTY(EditAnywhere)
	FVector MoveOffset_;

	UPROPERTY(EditAnywhere)
	float MoveTime_ = 4.f;

	UPROPERTY(EditAnywhere)
	bool ShouldMove_ = false;

	FVector OriginalLocation_;

	void Move(float DeltaTime);
};
