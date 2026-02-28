// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateLightComponent.h"

#include "Components/SpotLightComponent.h"


// Sets default values for this component's properties
UUpdateLightComponent::UUpdateLightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUpdateLightComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUpdateLightComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUpdateLightComponent::UpdateLight(FLinearColor LightColor)
{
	AActor* Owner = GetOwner();
	USpotLightComponent* SpotLight = Owner->FindComponentByClass<USpotLightComponent>();
	
	if (SpotLight)
	{
		SpotLight->SetLightColor(LightColor);
	}
}

