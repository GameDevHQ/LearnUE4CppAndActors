// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "PickupItem.h"


// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Name = "Unknown item";
    Quantity = 0;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity sphere"));
    
    RootComponent = Mesh;
    Mesh->SetSimulatePhysics(true);

    ProxSphere->AttachTo(Mesh);
    ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
}


// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void APickupItem::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

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
        FString(" ") + Name, 5.f, FColor::White, FColor::Black )
    );
    
    Destroy();
}