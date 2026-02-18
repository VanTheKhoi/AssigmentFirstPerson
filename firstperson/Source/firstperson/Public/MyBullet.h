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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MyCustom")
	TSubclassOf<AActor> BlueprintDefaultPawnClassReference;
	
	// Timer handle for the delay
	FTimerHandle DelayTimerHandle;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit) override;
	
	void DebugHitMessage(FString Message);
	void SetBulletLocationAndRotation(const FHitResult& Hit);
	void UpdateHitActorMaterial(AActor* HitActor);
	void DestroyActor();
	void CreateAndApplyDMI(UMeshComponent* MeshComp, FLinearColor Color);
};