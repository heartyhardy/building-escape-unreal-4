// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Color.h"
#include "Components/ActorComponent.h"
#include "Components/LightComponent.h"
#include "ShowPressurePlate.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UShowPressurePlate : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShowPressurePlate();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void TurnOnLight(float DeltaTime);
	void LerpLight(float DeltaTime);
private:

	bool bAnimationDone = false;
	float LerpProgress = 0.f;	
	FLinearColor CurrentColor;	
	ULightComponent* Light;

	UPROPERTY(EditAnywhere)
	float DelayTime = 1.f;

	UPROPERTY(EditAnywhere)
	float TargetIntensity;

	UPROPERTY(EditAnywhere)
	FLinearColor TargetColor;	
};
