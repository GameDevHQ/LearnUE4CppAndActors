

#pragma once

#include "GameFramework/Character.h"
#include "Avatar.generated.h"

UCLASS()
class LEARNUE4CPPANDACTORS_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Movement actions
    void MoveForward(float amount);
    void MoveLeft(float amount);
    void MoveRight(float amount);
    void MoveBackward(float amount);
    
    // Mouse rotate
    void Yaw(float amount);
    void Pitch(float amount);
    void Roll(float amount);
};
