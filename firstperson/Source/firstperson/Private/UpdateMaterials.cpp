// Fill out your copyright notice in the Description page of Project Settings.


#include "UpdateMaterials.h"

#include "Kismet/KismetMaterialLibrary.h"


// Sets default values for this component's properties
UUpdateMaterials::UUpdateMaterials()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ParameterName = "ColorMultiply";
}


// Called when the game starts
void UUpdateMaterials::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUpdateMaterials::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUpdateMaterials::UpdateMaterialParameterCollection(FLinearColor ParameterValue)
{
	if (MaterialParameterCollection)
	{
		UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(), MaterialParameterCollection, ParameterName, ParameterValue);
	}
}

