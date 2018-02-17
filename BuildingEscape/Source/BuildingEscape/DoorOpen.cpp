// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SpotLightComponent.h"

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
	for (const auto* TriggerVolume : CustomTriggerVolumes)
	{
		if (!TriggerVolume)
		{
			UE_LOG(LogTemp, Warning, TEXT("You dont have trigger volumes!"))
		}
			
	}
	for (const auto* OverlapTriggerStuff : OverlapTriggerStuffs)
	{
		if (!OverlapTriggerStuff)
		{
			UE_LOG(LogTemp, Warning, TEXT("You dont have overlaping stuffs!"))
		}
		
	}

}

// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// open door and close door
	if (CheckStuffPlace())
	{
		OnOpen.Broadcast();
		ChangeDoorLightColor();
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

bool UDoorOpen::CheckStuffPlace()
{
	int32 i = 0;
	int32 CountRightPlaces = 0;
	for (const auto* TriggerVolume : CustomTriggerVolumes)
	{
		TriggerVolume->GetOverlappingActors(OUT CheckOverlapTriggerStuffs);
		for (const auto* CheckOverlapTriggerStuff : CheckOverlapTriggerStuffs)
		{
			if (CheckOverlapTriggerStuff == OverlapTriggerStuffs[i])
			{
				CountRightPlaces++;
			}
		}

		i++;
	}
	if (CountRightPlaces == 5)
	{
		return true;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("On right place is %i"), CountRightPlaces)
	
	return false;
}

void UDoorOpen::ChangeDoorLightColor()
{
	if (!DoorLight)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no light on door!"))
	}
	else
	{
		DoorLight->FindComponentByClass<USpotLightComponent>()->SetLightColor(FLinearColor(0.f, 1.f, 0.f, 0.f));
		
	}
	
	return;
}
