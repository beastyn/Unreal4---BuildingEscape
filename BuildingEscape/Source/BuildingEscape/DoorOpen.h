// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void DoorOpen();
	void DoorClose();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	FRotator DefaultAngle; //variable for dorr angle at the beginning;
	
	UPROPERTY(VisibleAnywhere)
		float OpenAngle = 120.0f;
	
	UPROPERTY(EditAnywhere)
		ATriggerVolume * PressurePlate;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	float LastDoorOpenTime;
	AActor * Owner;
	AActor * ActorThatOpens; //pawn inherits from actor
	
};
