// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Bullet.h"


ABullet::ABullet(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    Damage = 1;
    Firer = nullptr;
    
    ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
    ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::Prox);
    RootComponent = ProxSphere;
    
    Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
    Mesh->AttachTo(ProxSphere);
}


void ABullet::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult & SweepResult)
{
    // Don't let a bullet hit the person that shot it
    if(OtherActor == Firer)
    {
        return;
    }
    
    if(OtherComp != OtherActor->GetRootComponent())
    {
        // don't collide w/ anything other than the actor's root component
        return;
    }
    
    OtherActor->TakeDamage(Damage, FDamageEvent(), NULL, this);
    Destroy();
}