// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BulletBase.generated.h"

UCLASS()
class FIRSTPERSON_API ABulletBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sphere collision component for the bullet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	TObjectPtr<USphereComponent> CollisionComp;
	
	// Static mesh component for visual representation of the bullet
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	TObjectPtr<UStaticMeshComponent> VisualSphere;
	
	// Function to handle hit events
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
			   const FHitResult& Hit);
};
