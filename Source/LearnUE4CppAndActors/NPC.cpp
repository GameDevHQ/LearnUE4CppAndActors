// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "NPC.h"
#include "Avatar.h"
#include "MyHUD.h"

// Sets default values
ANPC::ANPC(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
    ProxSphere->AttachTo(RootComponent);
    ProxSphere->SetSphereRadius(128.0f);
    ProxSphere->OnComponentBeginOverlap.AddDynamic( this, &ANPC::Prox );
    
    DefaultMessage = "Hi, I'm NPC!";
    Name = "Unknown NPC";
}


void ANPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp,
                               int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (Cast<AAvatar>(OtherActor) == nullptr)
    {
        return;
    }
    
    APlayerController* p_Controller = GetWorld()->GetFirstPlayerController();
    if (p_Controller)
    {
        AMyHUD* p_HUD = Cast<AMyHUD>(p_Controller->GetHUD());

        FString message = Name + FString(": ") + DefaultMessage;
        p_HUD -> addMessage(Message(Icon, Name + FString(": ") + DefaultMessage, 5.f, FColor::White, FColor::Black));
    }
}
