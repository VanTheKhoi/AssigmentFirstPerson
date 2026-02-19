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
	OwnerActor = GetOwner();
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
	
	// Update the hit actor's material to show the hit
	UpdateHitActorMaterial(OtherActor);
	
	// Update the hit Position
	// SetBulletLocationAndRotation(Hit);
	
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
	// Only Default Pawn can change material of the hit actor
	if (BlueprintClassReference == OwnerActor->GetClass())
	{
		USkeletalMeshComponent* SkeletalMeshComp = HitActor->FindComponentByClass<USkeletalMeshComponent>();
		
		// If the hit actor has a skeletal mesh component, change its material color to red
		if (SkeletalMeshComp)
		{
			// Create a dynamic material instance for each material slot and set the "Paint Tint" parameter to red
			CreateAndApplyDMI(SkeletalMeshComp, 
				FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), 
				FName("Paint Tint"));
			
			// Change color back to original after delay
			GetWorldTimerManager().SetTimer(
				DelayTimerHandle,
				[this, SkeletalMeshComp]()
				{
					CreateAndApplyDMI(SkeletalMeshComp, 
						FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), 
						FName("Paint Tint"));
				},
				0.2f,    // Delay in seconds
				false    // Don't loop
			);
			
			Destroy(true);
		}
		
		else
		{
			// If the hit actor doesn't have a skeletal mesh component, 
			// try to find a static mesh component and change its material color to green
			UMeshComponent* MeshComp = HitActor->FindComponentByClass<UMeshComponent>();
			if (MeshComp)
			{
				// Get current color to restore later
				FLinearColor OriginalColor;
				MeshComp->GetMaterial(0)->GetVectorParameterValue(FName("Base Color"), OriginalColor);
				
				// Create a dynamic material instance for each material slot and set the "Paint Tint" parameter to red
				CreateAndApplyDMI(MeshComp, 
					FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), 
					FName("Base Color"));
				
				// Change color back to original after delay
				GetWorldTimerManager().SetTimer(
					DelayTimerHandle,
					[this, MeshComp, OriginalColor]()
					{
						CreateAndApplyDMI(MeshComp, 
							OriginalColor, 
							FName("Base Color"));
					},
					0.2f,    // Delay in seconds
					false    // Don't loop
				);
			}
			
			// Destroy 
			Destroy(true);
		}
	}
	
	// If the owner is not the Default Pawn, just destroy the bullet without changing the material
	else
	{
		// Destroy after a short delay to allow the material change to be visible
		GetWorldTimerManager().SetTimer(
			DelayTimerHandle,
			this,
			&AMyBullet::DestroyActor,
			0.2f,    // Delay in seconds
			false    // Don't loop
		);
	}
}

void AMyBullet::DestroyActor()
{
	Destroy(true);
}

void AMyBullet::CreateAndApplyDMI(UMeshComponent* MeshComp, FLinearColor Color, FName ParameterName)
{
	// Create a dynamic material instance for each material slot and set the "Paint Tint" parameter to red
	int32 MaterialCount = MeshComp->GetNumMaterials();
	for (int32 i = 0; i < MaterialCount; i++)
	{
		UMaterialInstanceDynamic* DynamicMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(i);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue(ParameterName, Color);
		}
	}
}

