// Fill out your copyright notice in the Description page of Project Settings.


#include "LightZone.h"

#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"


// Sets default values
ALightZone::ALightZone()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create components
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(SceneRoot);
	SphereComponent->SetSphereRadius(200.f);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightZone::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ALightZone::OnOverlapEnd);
	
	// Create and configure the point light component
	SpotLightComponent = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComponent"));
	SpotLightComponent->SetupAttachment(SceneRoot);
	SpotLightComponent->SetIntensity(100000.0f);
	SpotLightComponent->SetLightColor(FLinearColor::Yellow);
}

// Called when the game starts or when spawned
void ALightZone::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightZone::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ALightZone::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

