// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"



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
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	
	
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

	// open door if ActorThatOpens in trigger
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
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

