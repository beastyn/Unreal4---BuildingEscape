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

	
	DefaultAngle = GetOwner()->GetActorRotation();
	
	
	
	
}

void UDoorOpen::DoorOpen()
{
	Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.f, DefaultAngle.Yaw + OpenAngle, 0.f));
}
void UDoorOpen::DoorClose()
{
	Owner = GetOwner();
	Owner->SetActorRotation(FRotator(0.f, DefaultAngle.Yaw, 0.f));
}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// open door
	if (GetTotalMassOnPlate() >= 80.f) //TODO make it to parameter
	{
		
		DoorOpen();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	//check if it time to close the door
	if (GetWorld()->GetTimeSeconds() >= (LastDoorOpenTime + DoorCloseDelay))
	{
		DoorClose();
	}
}

float UDoorOpen::GetTotalMassOnPlate()
{
	float TotalMass = 0.f;
	float ActorMass = 0.f;
	//find all the overlaping masses and sum their mass
	
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* OverlapingActor : OverlappingActors)
	{
		TotalMass += OverlapingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on Pressure Plate has mass %f"), *OverlapingActor->GetName(), TotalMass)
	}
	UE_LOG(LogTemp, Warning, TEXT("TotalMass on Pressure Plate is %f"), TotalMass)

	return TotalMass;
}