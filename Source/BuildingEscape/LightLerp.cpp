// Fill out your copyright notice in the Description page of Project Settings.


#include "LightLerp.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"

// Sets default values for this component's properties
ULightLerp::ULightLerp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightLerp::BeginPlay()
{
	Super::BeginPlay();
	// ...
	TargetIntensity = 10.f;
}


// Called every frame
void ULightLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
	// float NewIntensity = FMath::Lerp(Light->Intensity, TargetIntensity, .001f);
	
	//Use Frame Rate independant versions
	//float NewIntensity = FMath::FInterpConstantTo(Light->Intensity, TargetIntensity, DeltaTime, 1.f);
	float NewIntensity = FMath::FInterpTo(Light->Intensity, TargetIntensity, DeltaTime, .5f);
	
	Light->SetIntensity(NewIntensity);
}

