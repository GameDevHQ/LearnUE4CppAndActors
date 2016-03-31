// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Avatar.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAvatar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
    
    // Bind movement actions
    InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
    InputComponent->BindAxis("Left", this, &AAvatar::MoveLeft);
    InputComponent->BindAxis("Right", this, &AAvatar::MoveRight);
    InputComponent->BindAxis("Backward", this, &AAvatar::MoveBackward);
    
    // Mouse events
    InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
    InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
}

void AAvatar::MoveForward(float amount)
{
    if (Controller && amount)
    {
        FVector forward = GetActorForwardVector();
        AddMovementInput(forward, amount);
    }
}

void AAvatar::MoveLeft(float amount)
{
    if (Controller && amount)
    {
        FVector left = -GetActorRightVector();
        AddMovementInput(left, amount);
    }
}

void AAvatar::MoveRight(float amount)
{
    if (Controller && amount)
    {
        FVector right = GetActorRightVector();
        AddMovementInput(right, amount);
    }
}

void AAvatar::MoveBackward(float amount)
{
    if (Controller && amount)
    {
        FVector backward = -GetActorForwardVector();
        AddMovementInput(backward, amount);
    }
}

void AAvatar::Yaw(float amount)
{
    float value = 200.f * amount * GetWorld()->GetDeltaSeconds();
    AddControllerYawInput(value);
}

void AAvatar::Pitch(float amount)
{
    float value = 200.f * amount * GetWorld()->GetDeltaSeconds();
    AddControllerPitchInput(value);
}
