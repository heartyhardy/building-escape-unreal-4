// Fill out your copyright notice in the Description page of Project Settings.


#include "LightLerp.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
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

	AGameModeBase* GameMode  = GetWorld()->GetAuthGameMode();
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GameMode->DefaultPawnClass, AllActors);
	Player = AllActors.Pop();
	//UE_LOG(LogTemp, Warning, TEXT("%i"), AllActors.Num());

	USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
	CurrentColor = Light->LightColor;
}


// Called every frame
void ULightLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	
	TurnOnLight(DeltaTime);

	if(bAnimationDone && !bLightNotify){
		USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
		Light->SetLightColor(FLinearColor(0.f, 1.f, 0.f, 1.f));
		bLightNotify = true;
	}

	if(bAnimationDone && LerpProgress < 1.f && Player && LightSwitch->IsOverlappingActor(Player)){
		USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
		FLinearColor LerpColor = FLinearColor::LerpUsingHSV(CurrentColor, TriggerColor, LerpProgress);
		Light->SetLightColor(LerpColor.ToFColor(true));
		LerpProgress += DeltaTime;
	}

	if(bAnimationDone && Player && LerpProgress >= 1.f && !LightSwitch->IsOverlappingActor(Player)){
		LerpProgress = 0.f;
		USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
		Light->SetLightColor(CurrentColor);
	}
}


void ULightLerp::TurnOnLight(float DeltaTime){
	USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));

	if(!bAnimationDone){
		float NewIntensity = FMath::FInterpTo(Light->Intensity, TargetIntensity, DeltaTime, 1.f);
		
		Light->SetIntensity(NewIntensity);
	}

	if(Light->Intensity >= TargetIntensity){
		bAnimationDone = true;
	}
}
