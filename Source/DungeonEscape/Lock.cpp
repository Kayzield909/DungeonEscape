// Fill out your copyright notice in the Description page of Project Settings.


#include "Lock.h"

// Sets default values
ALock::ALock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false); //Pre-optimisation, we only tick intentionally

	Tags.Add("Lock");

	//Defines actor components and assigns
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(RootComp);

	KeyItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyItemMesh"));
	KeyItemMesh->SetupAttachment(RootComp);

	TriggerComp = CreateDefaultSubobject<UTriggerComponent>(TEXT("TriggerComp"));
	TriggerComp->SetupAttachment(RootComp);

}

// Called when the game starts or when spawned
void ALock::BeginPlay()
{
	Super::BeginPlay();
	
	SetKeyInPlace(true); // Test pursposes
}

// Called every frame
void ALock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ALock::IsKeyInPlace()
{
	return KeyInPlace;
}

void ALock::SetKeyInPlace(bool NewKeyInPlace)
{
	KeyInPlace = NewKeyInPlace;

	TriggerComp->SetTriggerActive(NewKeyInPlace);
	KeyItemMesh->SetVisibility(NewKeyInPlace);
}

