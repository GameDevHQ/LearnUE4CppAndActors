// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "MyHUD.h"
#include "Avatar.h"
#include "Spell.h"


AAvatar::AAvatar(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    CurrentHP = MaxHP = 100;
    inventoryShowing = false;
}


void AAvatar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
    check(InputComponent);
    
    // Bind movement actions
    InputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
    InputComponent->BindAxis("Strafe", this, &AAvatar::MoveStrafe);
    
    // Mouse events
    InputComponent->BindAxis("Yaw", this, &AAvatar::Yaw);
    InputComponent->BindAxis("Pitch", this, &AAvatar::Pitch);
    
    // InventorySubsytems
    InputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
    InputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
    InputComponent->BindAction("MouseClickedRMB", IE_Pressed, this, &AAvatar::MouseRightClicked);
}


void AAvatar::MouseClicked()
{
    if(inventoryShowing)
    {
        APlayerController* PController = GetWorld()->GetFirstPlayerController();
        AMyHUD* hud = Cast<AMyHUD>( PController->GetHUD() );
        hud->MouseClicked();
    }
}


void AAvatar::MoveForward(float amount)
{
    if (inventoryShowing) { return; }

    if (Controller && amount)
    {
        FVector forward = GetActorForwardVector();
        AddMovementInput(forward, amount);
    }
}


void AAvatar::MoveStrafe(float amount)
{
    if (inventoryShowing) { return; }

    if (Controller && amount)
    {
        FVector right = GetActorRightVector();
        AddMovementInput(right, amount);
    }
}


void AAvatar::Yaw(float amount)
{
    if (inventoryShowing)
    {
        passMouseActionToHUD();
    }
    else
    {
        float value = 200.f * amount * GetWorld()->GetDeltaSeconds();
        AddControllerYawInput(value);
    }
}


void AAvatar::Pitch(float amount)
{
    if (inventoryShowing)
    {
        passMouseActionToHUD();
    }
    else
    {
        float value = 200.f * amount * GetWorld()->GetDeltaSeconds();
        AddControllerPitchInput(value);
    }
}


void AAvatar::Pickup(APickupItem* item)
{
    if( Backpack.Contains( item->Name ) )
    {
        Backpack[item->Name] += item->Quantity;
    }
    else
    {
        Backpack.Add(item->Name, item->Quantity);
        Icons.Add(item->Name, item->Icon);
        Classes.Add(item->Name, item->GetClass());
        Spells.Add(item->Name, item->Spell);
    }
}


void AAvatar::ToggleInventory()
{
    APlayerController* p_Controller = GetWorld()->GetFirstPlayerController();
    AMyHUD* p_HUD = Cast<AMyHUD>(p_Controller->GetHUD());

    // If inventory is displayed, undisplay it
    if (inventoryShowing)
    {
        p_HUD->clearWidgets();
        p_Controller->bShowMouseCursor=false;
        inventoryShowing = false;
        return ;
    }

    // Otherwise, display the players inventory
    inventoryShowing = true;
    p_Controller->bShowMouseCursor = true;

    // Combine string name of the item, with quantity of it
    for(TMap<FString,int>::TIterator it = Backpack.CreateIterator(); it; ++it)
    {
        // Combine string name of the item, with quantity of it
        FString fs = it->Key + FString::Printf( TEXT(" x %d"), it->Value );
        UTexture2D* tex = NULL;
        if(Icons.Find(it->Key))
        {
            tex = Icons[it->Key];
            Widget new_widget(Icon(fs, tex ), Classes[it->Key]);
            new_widget.bpSpell = Spells[it->Key];
            p_HUD->addWidget(new_widget);
        }
    }
}


void AAvatar::passMouseActionToHUD()
{
    APlayerController* p_Controller = GetWorld()->GetFirstPlayerController();
    AMyHUD* p_HUD = Cast<AMyHUD>(p_Controller->GetHUD());
    p_HUD->MouseMoved();
}


void AAvatar::Tick( float DeltaSeconds )
{
    Super::Tick(DeltaSeconds);
    AddMovementInput(Knockback, 1.f);
    Knockback *= 0.5f;
}


float AAvatar::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    CurrentHP -= Damage;
    
    // Add some knockback that gets applied over a few frames
    Knockback = GetActorLocation() - DamageCauser->GetActorLocation();
    Knockback.Normalize();
    Knockback *= Damage * 500;
    
    // If he goes below 0 hp, he will die
    if(CurrentHP <= 0) { CurrentHP = 0; }
    return Damage;
}


void AAvatar::Drop(UClass *className)
{
    GetWorld()->SpawnActor<AActor>(
        className, GetActorLocation() + GetActorForwardVector()*200 + FVector(0, 0, 200), FRotator::ZeroRotator
    );
}


void AAvatar::CastSpell(UClass* bpSpell)
{
    ASpell* spell = GetWorld()->SpawnActor<ASpell>(bpSpell, FVector(0), FRotator(0));
    
    if (spell)
    {
        spell->SetCaster(this);
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Yellow, FString("can't cast ") + bpSpell->GetName());
    }
}


void AAvatar::MouseRightClicked()
{
    if (inventoryShowing)
    {
        APlayerController* PController = GetWorld()->GetFirstPlayerController();
        AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
        hud->MouseRightClicked();
    }
}


