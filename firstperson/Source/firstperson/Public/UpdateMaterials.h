// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpdateMaterials.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTPERSON_API UUpdateMaterials : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpdateMaterials();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	// Setup Material Parameter Collection
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Parameter Collection")
	class UMaterialParameterCollection* MaterialParameterCollection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Parameter Collection")
	FName ParameterName;
	
	
	// Function to update the material parameter collection
	UFUNCTION(BlueprintCallable, Category = "Material Parameter Collection")
	void UpdateMaterialParameterCollection(FLinearColor ParameterValue);
};
