// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MoverComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONESCAPE_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Class variables
	UPROPERTY(EditAnywhere) //So we can set actor var in level
	AActor* MoverActor;

	UMoverComponent* MoverComponentToTrigger;

	UPROPERTY(EditAnywhere)
	bool bPressurePlate = false;

	UPROPERTY(EditAnywhere)
	int32 RequiredActivatorCount = 1; // Used to control threshhold of how many actors needed to activate trigger, deactivate if Activator count below this number

private:
	UPROPERTY(VisibleAnywhere)
	int32 ActivatorCount = 0; // Counts how many activator actors are currently overlapping 

	UPROPERTY(VisibleAnywhere)
	bool bTriggerActive = false;

public:
	// Class Functions
	/** called when something enters the box component */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/** called when something leaves the box component */
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void SetTriggerActive(bool Active);

	UFUNCTION(BlueprintCallable)
	void SetMoverActor(AActor* NewMoverActor);
};
