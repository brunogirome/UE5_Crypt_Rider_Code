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

  TArray<AActor *> overlapingActors;
  GetOverlappingActors(overlapingActors);

  for (AActor *actor : overlapingActors)
  {
    if (actor && actor->ActorHasTag(UnlockTagName_))
    {
      UE_LOG(LogTemp, Display, TEXT("Man have it!"));
    }
  }
}