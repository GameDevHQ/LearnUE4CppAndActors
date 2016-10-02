// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Spell.generated.h"


UCLASS()
class LEARNUE4CPPANDACTORS_API ASpell : public AActor
{
    GENERATED_UCLASS_BODY()
	
    // Box defining volume of damage
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
    UBoxComponent* ProxBox;
    
    // The particle visualization of the spell
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
    UParticleSystemComponent* Particles;
    
    // How much damage the spell does per second
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spell)
    float DamagePerSecond;
    
    // How long the spell lasts
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Spell)
    float Duration;
    
    // Length of time the spell has been alive in the level
    float TimeAlive;
    
    // The original caster of the spell (source)
    AActor* Caster;
    
    // Parents this spell to a caster actor
    void SetCaster(AActor* caster);
    
	virtual void Tick(float DeltaSeconds) override;
};
