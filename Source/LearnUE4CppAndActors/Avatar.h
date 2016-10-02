#pragma once

#include "GameFramework/Character.h"
#include "PickupItem.h"
#include "Avatar.generated.h"


UCLASS()
class LEARNUE4CPPANDACTORS_API AAvatar : public ACharacter
{
    GENERATED_UCLASS_BODY()
    
    // A map for the backpack
    TMap<FString, int> Backpack;
    
    // A map for spells possible to cast by player
    TMap<FString, UClass*> Spells;
    
    // Individual maps for string name => Icon, Spell it casts, etc.
    TMap<FString, UTexture2D*> Icons;
    TMap<FString, UClass*> Classes;
    bool inventoryShowing;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerProperties)
    float CurrentHP;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerProperties)
    float MaxHP;
    
    int32 Experience;
    
    // Called to bind functionality to input
    void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    
    FVector Knockback;
    
    // Movement actions
    void MoveForward(float amount);
    void MoveStrafe(float amount);
    
    // Mouse rotate
    void Yaw(float amount);
    void Pitch(float amount);
    void Roll(float amount);
    
    // Inventory subsystem
    void ToggleInventory();
    void Pickup(APickupItem* item);
    void Drop(UClass *className);
    
    void MouseClicked();
    void passMouseActionToHUD();
    
    // Taking damage from a monster
    virtual void Tick(float DeltaSeconds) override;
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    // Spell casting
    void CastSpell(UClass* bpSpell);
    void MouseRightClicked();
};
