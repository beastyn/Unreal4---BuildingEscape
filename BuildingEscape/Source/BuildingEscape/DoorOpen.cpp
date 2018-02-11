// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

#define OUT


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Can`t find pressure plate on %s"), *GetOwner()->GetName())
	}
	}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// open door and close door
	if (GetTotalMassOnPlate() >= TriggerMass) 
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UDoorOpen::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	float ActorMass = 0.f;
	//find all the overlaping masses and sum their mass
	
	TArray<AActor*> OverlappingActors;
	if (!PressurePlate) { return TotalMass; }
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* OverlapingActor : OverlappingActors)
	{
		TotalMass += OverlapingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s on Pressure Plate has mass %f"), *OverlapingActor->GetName(), TotalMass)
	}
	//UE_LOG(LogTemp, Warning, TEXT("TotalMass on Pressure Plate is %f"), TotalMass)

	return TotalMass;
}