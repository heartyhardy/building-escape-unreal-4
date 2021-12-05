// Fill out your copyright notice in the Description page of Project Settings.


#include "LightLerp.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameMode.h"
//Only if using UGameplayStatics::GetAllActorsOfClass
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
//To get Pawn through PlayerController
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

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

	Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
	CurrentColor = Light->LightColor;
	
	/*
		To get DefaultPawn through UGameplayStatics

	AGameModeBase* GameMode  = GetWorld()->GetAuthGameMode();
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GameMode->DefaultPawnClass, AllActors);
	Player = AllActors.Pop();
	//UE_LOG(LogTemp, Warning, TEXT("%i"), AllActors.Num());
	*/
}


// Called every frame
void ULightLerp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	
	TurnOnLight(DeltaTime);

	if(bAnimationDone && !bLightNotify){
		USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
		Light->SetLightColor(FLinearColor(0.f, 1.f, 1.f, 1.f));
		bLightNotify = true;
	}

	if(bAnimationDone && LerpProgress < 1.f && Player && TotalMassOfActors() >= TriggerMass){ //!LightSwitch->IsOverlappingActor(Player)
		USpotLightComponent* Light = Cast<USpotLightComponent>(GetOwner()->GetComponentByClass(USpotLightComponent::StaticClass()));
		FLinearColor LerpColor = FLinearColor::LerpUsingHSV(CurrentColor, TriggerColor, LerpProgress);
		Light->SetLightColor(LerpColor.ToFColor(true));
		LerpProgress += DeltaTime;
	}

	if(bAnimationDone && Player && LerpProgress >= 1.f && TotalMassOfActors() < TriggerMass){ //!LightSwitch->IsOverlappingActor(Player)
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

float ULightLerp::TotalMassOfActors() const{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	LightSwitch->GetOverlappingActors(OUT OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		UPrimitiveComponent* ActorComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
		TotalMass += ActorComponent->GetMass();
	}
	UE_LOG(LogTemp, Warning, TEXT("Total Mass: %f"), TotalMass);
	return TotalMass;
}
