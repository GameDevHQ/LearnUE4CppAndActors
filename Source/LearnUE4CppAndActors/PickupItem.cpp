// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "PickupItem.h"


APickupItem::APickupItem(const class FObjectInitializer& PCIP): Super(PCIP)
{
    Name = "Unknown item";
    Quantity = 0;
    
    Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetSimulatePhysics(true);
    
    ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity sphere"));
    ProxSphere->AttachTo(Mesh);
    ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
}


void APickupItem::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                      int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
    if (Cast<AAvatar>(OtherActor) == nullptr)
    {
        return;
    }
    
    AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    avatar->Pickup(this);
    
    APlayerController* p_Controller = GetWorld()->GetFirstPlayerController();
    AMyHUD* p_HUD = Cast<AMyHUD>(p_Controller->GetHUD());
    p_HUD->addMessage(Message(Icon, FString("Picked up ") + FString::FromInt(Quantity) +
                              FString(" ") + Name, 5.f, FColor::White, FColor::Black)
                      );
    
    Destroy();
}


