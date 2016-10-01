// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Monster.generated.h"

class AMeleeWeapon;


UCLASS()
class LEARNUE4CPPANDACTORS_API AMonster : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    float Speed;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    float HitPoints;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    int32 Experience;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    UClass* BPLoot;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    TSubclassOf<AActor> BPMeleeWeapon;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    float BaseAttackDamage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=MonsterProperties)
    float AttackTimeout;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
    float TimeSinceLastStrike;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
    USphereComponent* SightSphere;
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
    USphereComponent* AttackRangeSphere;
    
    UFUNCTION(BlueprintCallable, Category=Collision)
    void SwordSwung();
    
    // The melee weapon instance (set if the character is using a melee weapon)
    AMeleeWeapon* MeleeWeapon;
    
    // Called every frame
    virtual void Tick(float DeltaSeconds) override;
    
    // Utility functions
    inline bool isInAttackRange(float d) {return d < AttackRangeSphere->GetScaledSphereRadius();}
    inline bool isInSightRange(float d) {return d < SightSphere->GetScaledSphereRadius();}
    
    virtual void PostInitializeComponents() override;
};
