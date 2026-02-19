// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BulletBase.h"
#include "TimerManager.h"
#include "MyBullet.generated.h"

UCLASS()
class FIRSTPERSON_API AMyBullet : public ABulletBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyCustom")
	TSubclassOf<AActor> BlueprintClassReference;
	
	// Reference to the owner actor (e.g., the character that fired the bullet)
	UPROPERTY()
	TObjectPtr<AActor> OwnerActor;
	
	// Timer handle for the delay
	FTimerHandle DelayTimerHandle;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Override the OnHit function to handle hit events
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit) override;
	
	UFUNCTION()
	void DebugHitMessage(FString Message);
	
	UFUNCTION()
	void SetBulletLocationAndRotation(const FHitResult& Hit);
	
	UFUNCTION()
	void UpdateHitActorMaterial(AActor* HitActor);
	
	UFUNCTION()
	void DestroyActor();
	
	UFUNCTION()
	void CreateAndApplyDMI(UMeshComponent* MeshComp, FLinearColor Color, FName ParameterName);
};