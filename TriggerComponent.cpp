// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

#include "Engine/World.h"

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

  AActor *unlockerActor = GetUnlockerActor();
  if (unlockerActor)
  {
    UE_LOG(LogTemp, Display, TEXT("CAUTGHT!"));
  }
  else
  {
    UE_LOG(LogTemp, Display, TEXT("NO DEAL..."));
  }
}

AActor *UTriggerComponent::GetUnlockerActor() const
{
  TArray<AActor *> overlapingActors;
  GetOverlappingActors(overlapingActors);

  for (AActor *actor : overlapingActors)
  {
    if (actor && actor->ActorHasTag(UnlockTagName_))
    {
      return actor;
    }
  }

  return nullptr;
}