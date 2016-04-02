// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "NPC.h"
#include "Avatar.h"
#include "MyHUD.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity sphere"));
    ProxSphere->AttachTo(RootComponent);
    ProxSphere->SetSphereRadius(128.0f);
    ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
    DefaultMessage = "Hi, I'm NPC!";
    Name = "NPC";
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
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
        p_HUD -> addMessage(Message(message, 5.f, FColor::White, Icon));
    }
}
