// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FindPhysicsHandle();

	BindInputs();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
	// UE_LOG(LogTemp, Warning,
	//  TEXT("Player View: %s %s"), 
	//  *PlayerLocation.ToString(), 
	//  *PlayerRotation.ToString()
	// );
	if(bGrabbing){
		GetFirstActorRayHit();
		DrawGrabReach();

		if(PhysicsHandle->GrabbedComponent){
			PhysicsHandle->SetTargetLocation(LineOfReach);
		}
	}
}

void UGrabber::Grab(){
	// Only Raycast when Grabbing!
	FHitResult Hit = GetFirstActorRayHit();
	UPrimitiveComponent* GrabbedActor = Hit.GetComponent();

	if(GrabbedActor){
		UE_LOG(LogTemp, Warning, TEXT("Grabbing!!"));
		bGrabbing = true;
		PhysicsHandle->GrabComponentAtLocation(GrabbedActor,NAME_None, LineOfReach);
	}

}

void UGrabber::Release(){
	if(PhysicsHandle->GrabbedComponent){
		bGrabbing = false;
		PhysicsHandle->ReleaseComponent();
		UE_LOG(LogTemp, Warning, TEXT("Released!!"));
	}
}

void UGrabber::FindPhysicsHandle(){
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle){
		UE_LOG(LogTemp, Error, TEXT("No Physics handle found in: %s"), *GetOwner()->GetName());
	}
}

void UGrabber::BindInputs(){
	if(GetOwner()->InputComponent){
		InputComponent = GetOwner()->InputComponent;
		InputComponent->BindAction(
			"Grab",
			EInputEvent::IE_Pressed,
			this,
			&UGrabber::Grab
		);
		InputComponent->BindAction(
			"Grab",
			EInputEvent::IE_Released,
			this,
			&UGrabber::Release
		);
	}
}

FHitResult UGrabber::GetFirstActorRayHit() {
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation, 
		OUT PlayerRotation
	);

	LineOfReach = PlayerLocation + PlayerRotation.Vector() * Reach;
	
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerLocation,
		LineOfReach,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	// if(Hit.GetActor()){
	// 	UE_LOG(LogTemp, Warning, TEXT("HIT ACTOR: %s"), *Hit.GetActor()->GetName());
	// }

	return Hit;
}

void UGrabber::DrawGrabReach() {
	DrawDebugLine(
		GetWorld(),
		PlayerLocation,
		LineOfReach,
		FColor(255, 0, 0, 1),
		false,
		0.f,
		10,
		4.f
	);
}