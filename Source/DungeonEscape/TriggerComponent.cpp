// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay(); //Run parent code

	if (MoverActor) // check MoverActor is valid
	{
		MoverComponentToTrigger = MoverActor->FindComponentByClass<UMoverComponent>();
		
		if (MoverComponentToTrigger) // Less concise way is MoverComponentToTrigger != nullptr
		{
			// Trigger logic moved to overlap events
			// bool bReverseMovement = MoverComponentToTrigger->bReverseMovement;
			// MoverComponentToTrigger->SetMovementEnabled(true, bReverseMovement);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("MoverComponentToTrigger NOT FOUND"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("MoverActor is nullptr"));
	}

	if (bPressurePlate)
	{
		OnComponentBeginOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapBegin);
		OnComponentEndOverlap.AddDynamic(this, &UTriggerComponent::OnOverlapEnd);
	}

}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); //Run parent code
}

void UTriggerComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		SetTriggerActive(true);
	}
	
}

void UTriggerComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("PressurePlateActivator"))
	{
		SetTriggerActive(false);
	}
}

void UTriggerComponent::SetTriggerActive(bool Active)
{
	if (MoverComponentToTrigger)
	{
		bTriggerActive = Active;

		MoverComponentToTrigger->SetMovementEnabled(true, !Active); // !Active == MoverComponent Forward Direction e.g. Open Gate
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("%s Does NOT have MoverActor to Trigger"), *GetOwner()->GetActorNameOrLabel()); // * for string conversion
	}
}
