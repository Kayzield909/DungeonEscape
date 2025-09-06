// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/NameTypes.h"
#include "CollectableItem.generated.h"

UCLASS()
class DUNGEONESCAPE_API ACollectableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//Class Member Variables
	UPROPERTY(EditAnywhere)
	FName ItemName; //FName faster to compare that string
};
