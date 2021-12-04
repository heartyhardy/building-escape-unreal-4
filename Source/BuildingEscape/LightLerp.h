// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Math/Color.h"
#include "LightLerp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API ULightLerp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightLerp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void TurnOnLight(float DeltaTime);

	float TargetIntensity;
	float LerpProgress = 0.f;
	bool bAnimationDone = false;
	bool bLightNotify = false;

	FLinearColor CurrentColor;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* LightSwitch;

	UPROPERTY(EditAnywhere)
	AActor* Player; 

	UPROPERTY(EditAnywhere)
	FLinearColor TriggerColor;
};
