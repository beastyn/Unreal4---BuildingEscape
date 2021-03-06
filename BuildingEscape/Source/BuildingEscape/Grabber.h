// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//length for grabbing view
	float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	///Fins handle component if we have it
	void FindPhysicsHandleComponent();

	///Setup attached input component
	void SetupInputComponent();

	///Calculate end of trace line for getting reached physics body

	FVector GetLineTraceEnd();
	FVector GetLineTraceStart();
	///return JIT for first physics body we reach
	FHitResult GetFirstPhysicsBodyInReach();

	///Ray-cast and grab with HitResult
	void Grab();
	void Release();


};
