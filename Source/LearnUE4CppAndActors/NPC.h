// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "NPC.generated.h"


UCLASS()
class LEARNUE4CPPANDACTORS_API ANPC : public ACharacter
{
    GENERATED_UCLASS_BODY()
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Collision)
    USphereComponent* ProxSphere;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NPCMessage)
    FString Name;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NPCMessage)
    FString DefaultMessage;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=NPCMessage)
    UTexture2D* Icon;
    
    UFUNCTION(BlueprintNativeEvent, Category = Collision)
    void Prox(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
              bool bFromSweep, const FHitResult & SweepResult);
};

