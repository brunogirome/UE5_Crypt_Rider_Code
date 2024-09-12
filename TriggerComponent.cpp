// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

#include "Engine/World.h"

#include "Mover.h"

UTriggerComponent::UTriggerComponent()
{
  PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
  Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  if (!Mover_)
  {
    return;
  }

  if (AActor *unlockerActor = GetUnlockerActor())
  {
    UPrimitiveComponent *root = Cast<UPrimitiveComponent>(unlockerActor->GetRootComponent());
    if (root)
    {
      root->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
      root->SetSimulatePhysics(false);
      Mover_->SetShouldMove(true);
    }
  }
  else
  {
    Mover_->SetShouldMove(false);
  }
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
  Mover_ = NewMover;
}

AActor *UTriggerComponent::GetUnlockerActor() const
{
  TArray<AActor *> overlapingActors;
  GetOverlappingActors(overlapingActors);

  for (AActor *actor : overlapingActors)
  {
    if (actor && actor->ActorHasTag(UnlockTagName_) && !actor->ActorHasTag("Grabbed"))
    {
      return actor;
    }
  }

  return nullptr;
}