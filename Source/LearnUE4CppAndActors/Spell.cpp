// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Spell.h"
#include "Monster.h"


ASpell::ASpell(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    Duration = 3;
    DamagePerSecond = 1;
    TimeAlive = 0;
    
    ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
    Particles = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("ParticleSystem"));
    RootComponent = Particles;
    ProxBox->AttachTo(RootComponent);
    
    PrimaryActorTick.bCanEverTick = true;
}


void ASpell::SetCaster(AActor* caster)
{
    Caster = caster;
    AttachRootComponentTo(caster->GetRootComponent());
}


void ASpell::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    
    // Search the proxbox for all actors in the volume.
    TArray<AActor*> actors;
    ProxBox->GetOverlappingActors( actors );
    
    // Damage each actor (except self) the sphere overlaps
    for(int i = 0; i < actors.Num(); i++)
    {
        if (actors[i] != Caster)
        {
            AMonster *monster = Cast<AMonster>(actors[i]);
            
            if (monster && ProxBox->IsOverlappingComponent(monster->GetCapsuleComponent()))
            {
                actors[i]->TakeDamage(DamagePerSecond*DeltaSeconds, FDamageEvent(), 0, this);
            }
        }
    }
    
    TimeAlive += DeltaSeconds;
    if (TimeAlive > Duration) { Destroy(); }
}

