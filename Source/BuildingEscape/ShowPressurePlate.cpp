// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Actor.h"
#include "Components/LightComponent.h"
#include "ShowPressurePlate.h"

// Sets default values for this component's properties
UShowPressurePlate::UShowPressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShowPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Light = Cast<ULightComponent>(GetOwner()->GetComponentByClass(ULightComponent::StaticClass()));	
	CurrentColor = Light->GetLightColor();
}


// Called every frame
void UShowPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	TurnOnLight(DeltaTime);
	LerpLight(DeltaTime);
}

void UShowPressurePlate::TurnOnLight(float DeltaTime){
	if(!bAnimationDone && GetWorld()->GetTimeSeconds() > DelayTime){
		float NewIntensity = FMath::FInterpTo(Light->Intensity, TargetIntensity, DeltaTime, .5f);
		Light->SetIntensity(NewIntensity);
	}

	if(Light->Intensity >= TargetIntensity){
		bAnimationDone = true;
	}
}

void UShowPressurePlate::LerpLight(float DeltaTime){
	if(GetWorld()->GetTimeSeconds() > DelayTime && LerpProgress < 1.f){
		FLinearColor LerpColor = FLinearColor::LerpUsingHSV(CurrentColor, TargetColor, LerpProgress);
		Light->SetLightColor(LerpColor);
		LerpProgress += DeltaTime/3.f;
	}
}
