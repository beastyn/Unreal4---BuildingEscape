// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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
	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen;
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;

private:
	
	
		
	UPROPERTY(EditAnywhere)
		ATriggerVolume * PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		AActor* DoorLight = nullptr;
	
	UPROPERTY(EditAnywhere)
		TArray <ATriggerVolume*> CustomTriggerVolumes = { nullptr, nullptr, nullptr, nullptr, nullptr};
	
	UPROPERTY(EditAnywhere)
		TArray <AActor*> OverlapTriggerStuffs = {nullptr, nullptr, nullptr, nullptr,nullptr};
	
	TArray <AActor*> CheckOverlapTriggerStuffs = { nullptr, nullptr, nullptr, nullptr, nullptr};

	UPROPERTY(EditAnywhere)
		float TriggerMass = 80.f;
	
	AActor * Owner = nullptr;
	float GetTotalMassOnPlate();
	bool CheckStuffPlace();
	void ChangeDoorLightColor();

	
};
