// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Avatar.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    MaxHP = 100.f;
    CurrentHP = 100.f;
    Backpack = TMap<FString, int>();
    Icons = TMap<FString, UTexture2D*>();
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
    InputComponent->BindAxis("Strafe", this, &AAvatar::MoveStrafe);
    
    // Mouse events
    InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
    InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
    
    // InventorySubsytems
    InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
}

void AAvatar::MoveForward(float amount)
{
    if (Controller && amount)
    {
        FVector forward = GetActorForwardVector();
        AddMovementInput(forward, amount);
    }
}


void AAvatar::MoveStrafe(float amount)
{
    if (Controller && amount)
    {
        FVector right = GetActorRightVector();
        AddMovementInput(right, amount);
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

void AAvatar::ToggleInventory()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(0, 0.5f, FColor::Red, "Showing inventory...");
    }
}

void AAvatar::Pickup(APickupItem* item)
{
    if(Backpack.Find(item->Name))
    {
        Backpack[item->Name] += item->Quantity;
    }
    else
    {
        Backpack.Add(item->Name, item->Quantity);
        Icons.Add(item->Name, item->Icon);
    }
}



