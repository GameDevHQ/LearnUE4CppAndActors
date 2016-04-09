#pragma once

#include "GameFramework/Character.h"
#include "PickupItem.h"
#include "Avatar.generated.h"

UCLASS()
class LEARNUE4CPPANDACTORS_API AAvatar : public ACharacter
{
	GENERATED_BODY()
    
    bool inventoryShowing;
    
    // A map for the players backpack
    TMap<FString, int> Backpack;
    
    // The icons for the items in the backpack, lookup by string
    TMap<FString, UTexture2D*> Icons;
    
public:
	// Sets default values for this character's properties
	AAvatar();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerAttributes)
    float MaxHP;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=PlayerAttributes)
    float CurrentHP;
    
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

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
};
