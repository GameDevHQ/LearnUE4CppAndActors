// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"


struct Message
{
    FString message;
    float time;
    FColor frontColor;
    FColor backColor;
    UTexture2D* icon;
    
    Message()
    {
        // Set the default time.
        time = 5.f;
        frontColor = FColor::White;
        backColor = FColor::Black;
    }
    
    Message( FString iMessage, float iTime, FColor iFrontColor, FColor iBackColor )
    {
        message = iMessage;
        time = iTime;
        frontColor = iFrontColor;
        backColor = iBackColor;
        icon = 0;
    }
    
    Message( UTexture2D* iTex, FString iMessage, float iTime, FColor iFrontColor, FColor iBackColor )
    {
        icon = iTex;
        message = iMessage;
        time = iTime;
        frontColor = iFrontColor;
        backColor = iBackColor;
    }
};

struct Icon
{
    FString name;
    UTexture2D* icon;
    
    Icon()
    {
        name = "UNKNOWN ICON";
        icon = 0;
    }
    
    Icon( FString& iName, UTexture2D* iTex )
    {
        name = iName;
        icon = iTex;
    }
};

struct Widget
{
    Icon icon;
    // in case you need to drop an item, this is the class the item was from
    UClass *className;
    // blueprint of the spell this widget casts
    UClass* bpSpell;
    FVector2D pos, size;
    Widget(Icon iicon, UClass *iClassName)
    {
        icon = iicon;
        className = iClassName;
    }
    float left(){ return pos.X; }
    float right(){ return pos.X + size.X; }
    float top(){ return pos.Y; }
    float bottom(){ return pos.Y + size.Y; }
    bool hit( FVector2D v )
    {
        // +---+ top (0)
        // |   |
        // +---+ bottom (2) (bottom > top)
        // L   R
        return v.X > left() && v.X < right() && v.Y > top() && v.Y < bottom();
    }
};


UCLASS()
class LEARNUE4CPPANDACTORS_API AMyHUD : public AHUD
{
    GENERATED_UCLASS_BODY()
    
    // The font used to render the text in the HUD.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
    UFont* hudFont;
    
    FVector2D dims;
    TArray<Message> messages;
    TArray<Widget> widgets;
    Widget* heldWidget;
    
    float barWidth = 200, barHeight = 15;
    float barPad = 1, barMargin = 25;
    
    void DrawMessages();
    void DrawWidgets();
    void DrawHealthBar();
    virtual void DrawHUD() override;
    
    void MouseClicked();
    void MouseRightClicked();
    void MouseMoved();
    
    void addMessage(Message msg);
    void addWidget(Widget widget);
    void clearWidgets();
    
    void debug(int slot, FColor color, FString message);
};
