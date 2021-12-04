// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FRotator DoorRotation = GetOwner()->GetActorRotation();

	if(!Flipped){
		TargetRotation = FMath::FInterpTo(DoorRotation.Yaw, MaxRotation, DeltaTime, .5f);
	}else if (Flipped){
		TargetRotation = FMath::FInterpTo(DoorRotation.Yaw, MinRotation, DeltaTime, .5f);
	}

	if(DoorRotation.Yaw < MaxRotationThreshold){
		Flipped = true;
	}else if(DoorRotation.Yaw > MinRotationThreshold){
		Flipped = false;
	}

	FRotator NewRotation = FRotator(DoorRotation.Pitch, TargetRotation, DoorRotation.Roll);
	GetOwner()->SetActorRotation(NewRotation);
	// ...
}

