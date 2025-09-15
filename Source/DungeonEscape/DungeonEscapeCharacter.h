// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "UObject/NameTypes.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "DungeonEscapeCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A basic first person character
 */
UCLASS(abstract)
class ADungeonEscapeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: first person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstPersonMesh;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category ="Input")
	class UInputAction* MouseLookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* InteractAction;
	
public:
	ADungeonEscapeCharacter();

protected:

	/** Called from Input Actions for movement input */
	void MoveInput(const FInputActionValue& Value);

	/** Called from Input Actions for looking input */
	void LookInput(const FInputActionValue& Value);

	/** Handles aim inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoAim(float Yaw, float Pitch);

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles jump start inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump end inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

protected:

	/** Set up input action bindings */
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	

public:

	/** Returns the first person mesh **/
	USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }

	/** Returns first person camera component **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// Replaced Grabber Component Reference as component is mostly redundant and duplicates most interact() code
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsHandleComponent* PhysicsHandleComponent;

public:
	// Custom InputActionEvents
	// 
	// Handles Interact inputs from either controls or UI interfaces
	void Interact();

	void Grab();

	void Release();

public:
	// Custom Variables
	UPROPERTY(EditAnywhere, Category = "Interact")
	float MaxInteractionDistance = 300.0f; // Use to calc end of interaction trace sweep. Able to interact with objects 3meters in front of us

	UPROPERTY(EditAnywhere, Category = "Interact")
	float HoldDistance = 150.0f; // For Grabbable Items
	
	UPROPERTY(EditAnywhere, Category = "Interact")
	float InteractionSphereRadius = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Interact")
	bool bInteractDrawDebug = false;

	

private:
	// Custom Variables
	UPROPERTY(VisibleAnywhere, Category = "Interact")
	TArray<FName> ItemList; // FName > FString for lookup perfomance

	UPROPERTY(VisibleAnywhere, Category = "Interact", meta = (AllowPrivateAccess = true))
	bool bGrabberEnabled = true;

};

