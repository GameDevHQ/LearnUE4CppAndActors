// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


struct Message
{
    FString message;
    float time;
    FColor color;
    UTexture2D* icon;
    
    Message()
    {
        time = 5.f;
        color = FColor::White;
    }
    
    Message(FString message, float time, FColor color, UTexture2D* icon)
    {
        this->message = message;
        this->time = time;
        this->color = color;
        this->icon = icon;
    }
};

/*
 *
*/
UCLASS()
class LEARNUE4CPPANDACTORS_API AMyHUD : public AHUD
{
	GENERATED_BODY()
    
    TArray<Message> messages;
    void DrawMessages();
    void DrawHealthBar();
    
    float barWidth = 200, barHeight = 15;
    float barPad = 1, barMargin = 25;
    
public:
    virtual void DrawHUD() override;
    virtual void addMessage(Message msg);
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=HUDFont)
    UFont* hudFont;
};
