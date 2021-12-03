// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString OwnerName = GetOwner()->GetName();
	FString* PtrOwnerName = &OwnerName;
	UE_LOG(LogTemp, Warning, TEXT("Actor name: %s"), **PtrOwnerName);

	FString OwnerPosition = GetOwner()->GetActorLocation().ToString();
	FString* PtrOwnerPosition = &OwnerPosition;
	UE_LOG(LogTemp, Warning, TEXT("Actor location: %s"), **PtrOwnerPosition);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
