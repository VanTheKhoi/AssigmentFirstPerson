// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMyBullet::AMyBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);

	// Debug message for hit
	// DebugHitMessage(TEXT("Hit detected!"));
	
	// Set Actor Location and Rotation to the hit location and normal
	// SetBulletLocationAndRotation(Hit);
	
	// Update the hit actor's material to show the hit
	UpdateHitActorMaterial(OtherActor);
}

void AMyBullet::DebugHitMessage(FString Message)
{
	if (GEngine)
	{
		//Basic message
		GEngine->AddOnScreenDebugMessage(
			-1,                    // Key (-1 = always add new message)
			5.0f,                  // Display time in seconds
			FColor::Green,         // Text color
			Message
		);
	}
}

void AMyBullet::SetBulletLocationAndRotation(const FHitResult& Hit)
{
	FVector HitLocation = Hit.ImpactPoint;
	FRotator HitRotation = Hit.ImpactNormal.Rotation();
	SetActorLocation(HitLocation);
	SetActorRotation(HitRotation);
}

void AMyBullet::UpdateHitActorMaterial(AActor* HitActor)
{
	if (HitActor == this)
	{
		return; // Avoid changing material of the bullet itself
	}
	
	TSubclassOf<AActor> CurrentHitActor = HitActor->GetClass();
	
	// Check if the hit actor's class matches the BlueprintClassReference
	if (BlueprintClassReference == CurrentHitActor && BlueprintDefaultPawnClassReference != CurrentHitActor)
	{
		// DEBUG 
		FString ActorName = CurrentHitActor->GetName();
		DebugHitMessage(ActorName);
		
		UMeshComponent* MeshComp = HitActor->FindComponentByClass<UMeshComponent>();
		if (MeshComp)
		{
			// Create a dynamic material instance for each material slot and set the "Paint Tint" parameter to red
			CreateAndApplyDMI(MeshComp, FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));
			
			// Change color back to original after delay
			GetWorldTimerManager().SetTimer(
				DelayTimerHandle,
				[this, MeshComp]()
				{
					CreateAndApplyDMI(MeshComp, FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
				},
				0.2f,    // Delay in seconds
				false    // Don't loop
			);
		}
		
		// Destroy
		DestroyActor();
	}
	else
	{
		// Destroy after delay time
		GetWorldTimerManager().SetTimer(DelayTimerHandle, this, 
			&AMyBullet::DestroyActor, 0.3, false);
	}
}

void AMyBullet::DestroyActor()
{
	Destroy(true);
}

void AMyBullet::CreateAndApplyDMI(UMeshComponent* MeshComp, FLinearColor Color)
{
	// Create a dynamic material instance for each material slot and set the "Paint Tint" parameter to red
	int32 MaterialCount = MeshComp->GetNumMaterials();
	for (int32 i = 0; i < MaterialCount; i++)
	{
		UMaterialInstanceDynamic* DynamicMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(i);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(FName("Paint Tint"), Color);
		}
	}
}

