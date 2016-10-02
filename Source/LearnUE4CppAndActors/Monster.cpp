// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Monster.h"
#include "Avatar.h"
#include "Bullet.h"
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


void AMonster::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    AddMovementInput(Knockback, 1.f);
    Knockback *= 0.5f;
    
    // move the monster towards the player
    AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if(!avatar) return;
    
    FVector playerPos = avatar->GetActorLocation();
    FVector toPlayer = playerPos - GetActorLocation();
    float distanceToPlayer = toPlayer.Size();
    
    // If the player is not the SightSphere of the monster,
    // go back
    if(distanceToPlayer > SightSphere->GetScaledSphereRadius())
    {
        // If the player is OS, then the enemy cannot chase
        return;
    }
    
    toPlayer /= distanceToPlayer;	// normalizes the vector
    
    // At least face the target
    // Gets you the rotator to turn something
    // that looks in the `toPlayer` direction.
    FRotator toPlayerRotation = toPlayer.Rotation();
    toPlayerRotation.Pitch = 0; // 0 off the pitch
    RootComponent->SetWorldRotation(toPlayerRotation);
    
    if(isInAttackRange(distanceToPlayer))
    {
        // Perform the attack.
        if(!TimeSinceLastStrike)
        {
            // If the cooldown is over, then attack again
            // This resets the hit parameter.
            Attack(avatar);
        }
        
        TimeSinceLastStrike += DeltaSeconds;
        if(TimeSinceLastStrike > AttackTimeout)
        {
            TimeSinceLastStrike = 0;
        }
        
        return;	// nothing else to do.
    }
    else
    {
        if(MeleeWeapon)
        {
            // rest the melee weapon (not swinging)
            MeleeWeapon->Rest();
        }
        // not in attack range, so walk towards player
        AddMovementInput(toPlayer, Speed*DeltaSeconds);
    }
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


void AMonster::Attack(AActor* thing)
{
    if(MeleeWeapon)
    {
        MeleeWeapon->Swing();
    }
    else if(BPBullet)
    {
        FVector fwd = GetActorForwardVector();
        FVector nozzle = GetMesh()->GetBoneLocation("RightHand");
        nozzle += fwd * 155;// move it fwd of the monster so it doesn't
        // collide with the monster model.
        
        FVector toOpponent = thing->GetActorLocation() - nozzle;
        toOpponent.Normalize();
        ABullet *bullet = GetWorld()->SpawnActor<ABullet>(BPBullet, nozzle, RootComponent->GetComponentRotation());
        
        if(bullet)
        {
            bullet->Firer = this;
            bullet->ProxSphere->AddImpulse(fwd*BulletLaunchImpulse);
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(
                0, 5.f, FColor::Yellow, "monster: no bullet actor could be spawned. is the bullet overlapping something?"
            );
        }
    }
}


float AMonster::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    
    HitPoints -= Damage;
    
    Knockback = GetActorLocation() - DamageCauser->GetActorLocation();
    Knockback.Normalize();
    Knockback *= 500;
    
    if( HitPoints <= 0 )
    {
        // award the avatar exp
        AAvatar *avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
        avatar->Experience += Experience;
        
        if (MeleeWeapon) { MeleeWeapon->Destroy(); }
        Destroy();
    }
    
    return Damage;
}


void AMonster::SwordSwung()
{
    if (MeleeWeapon)
    {
        MeleeWeapon->Swing();
    }
}

