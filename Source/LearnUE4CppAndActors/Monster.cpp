// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Monster.h"
#include "Avatar.h"
#include "MeleeWeapon.h"


AMonster::AMonster(const class FObjectInitializer& PCIP): Super(PCIP)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Speed = 20;
    HitPoints = 20;
    Experience = 0;
    BPLoot = nullptr;
    BPMeleeWeapon = nullptr;
    AttackTimeout = 1.5f;
    TimeSinceLastStrike = 0;
    MeleeWeapon = nullptr;
    
    SightSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
    SightSphere->AttachTo(RootComponent);
    
    AttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
    AttackRangeSphere->AttachTo(RootComponent);
}


void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!avatar) return;
    
    FVector playerPos = avatar->GetActorLocation();
    FVector toPlayer = playerPos - GetActorLocation();
    
    // If the player is not in the SightSphere of the monster, go back
    float distanceToPlayer = toPlayer.Size();
    if (!isInSightRange(distanceToPlayer)) return;
    
    toPlayer.Normalize(); // Normalize the vector
    
    // At least face the target.
    // Gets you the rotator to turn something. That looks in the `toPlayer` direction
    FRotator toPlayerRotation = toPlayer.Rotation();
    toPlayerRotation.Pitch = 0;
    RootComponent->SetWorldRotation(toPlayerRotation);
    
    // Move the monster towards to player a bit
    AddMovementInput(toPlayer, Speed * DeltaTime);
    
}


void AMonster::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    
    // Instantiate the melee weapon if a bp was selected
    if(BPMeleeWeapon)
    {
        MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BPMeleeWeapon, FVector(0), FRotator(0));
        
        if(MeleeWeapon)
        {
            MeleeWeapon->WeaponHolder = this;
            MeleeWeapon->AttachRootComponentTo(GetMesh(), FName(TEXT("RightHandSocket")), EAttachLocation::SnapToTarget);
        }
        else
        {
            FString message = GetName() + FString(" cannot instantiate meleeweapon ") + BPMeleeWeapon->GetName();
            GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Yellow, message);
        }
    }
}


void AMonster::SwordSwung()
{
    if (MeleeWeapon)
    {
        MeleeWeapon->Swing();
    }
}

