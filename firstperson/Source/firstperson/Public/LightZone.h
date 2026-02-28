// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightZone.generated.h"

UCLASS()
class FIRSTPERSON_API ALightZone : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALightZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Scene Root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* SceneRoot;
	
	// Sphere collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* SphereComponent;
	
	// Light component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpotLightComponent* SpotLightComponent;
	
	// Light intensity when player is inside the zone
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	float InsideLightIntensity;
	
	// Overlap
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
						class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, 
						bool bFromSweep, 
						const FHitResult & SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, 
					class AActor* OtherActor, 
					class UPrimitiveComponent* OtherComp, 
					int32 OtherBodyIndex);
};
