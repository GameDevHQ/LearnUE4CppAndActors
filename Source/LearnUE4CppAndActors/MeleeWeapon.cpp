// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "MeleeWeapon.h"
#include "Monster.h"


AMeleeWeapon::AMeleeWeapon(const class FObjectInitializer& PCIP): Super(PCIP)
{
    AttackDamage = 1;
    Swinging = false;
    WeaponHolder = nullptr;
    
    Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
    RootComponent = Mesh;
    
    ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
    ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::Prox);
    ProxBox->AttachTo(RootComponent);
}


void AMeleeWeapon::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                       int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult & SweepResult)
{
    if (OtherComp != OtherActor->GetRootComponent()) return;
    
    // Avoid hitting things while sword isn't swigging,
    // Avoid hitting youself, and
    // Avoid hitting the same OtherActor twice
    if (Swinging && OtherActor != WeaponHolder && !ThingsHit.Contains(OtherActor))
    {
        OtherActor->TakeDamage(AttackDamage + WeaponHolder->BaseAttackDamage, FDamageEvent(),
                               NULL, this);
        ThingsHit.Add(OtherActor);
    }
}


void AMeleeWeapon::Swing()
{
    ThingsHit.Empty();
    Swinging = true;
}


void AMeleeWeapon::Rest()
{
    ThingsHit.Empty();
    Swinging = false;
}
