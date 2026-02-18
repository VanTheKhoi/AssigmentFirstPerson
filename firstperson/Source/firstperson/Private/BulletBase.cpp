// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the collision component
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionObjectType(ECC_GameTraceChannel1);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComp->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	CollisionComp->SetGenerateOverlapEvents(true);
	
	// Make sure hit events are enabled
	CollisionComp->SetNotifyRigidBodyCollision(true);
	
	// Make the sphere the root component
	RootComponent = CollisionComp;
	 
	// Add a visual sphere
	VisualSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualSphere"));
	VisualSphere->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentHit.AddDynamic(this, &ABulletBase::OnHit);
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}
