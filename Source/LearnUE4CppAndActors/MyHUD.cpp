// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "MyHUD.h"
#include "Avatar.h"


AMyHUD::AMyHUD(const class FObjectInitializer& PCIP) : Super(PCIP)
{
    heldWidget = nullptr;
}


void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    dims.X = Canvas->SizeX;
    dims.Y = Canvas->SizeY;

    DrawMessages();
    DrawHealthBar();
    DrawWidgets();
}


void AMyHUD::DrawMessages()
{
    float pad = 10.f;
    int sizeX = Canvas->SizeX;
    
    for(int i=messages.Num()-1; i>=0; i--)
    {
        float outputWight, outputHeigh;
        GetTextSize(messages[i].message, outputWight, outputHeigh, hudFont, 1.f);
        
        float messageHeight = outputHeigh + 2.f * pad;
        float x = 0.f, y = i * messageHeight;
        
        if (messages[i].icon != nullptr)
        {
            DrawTexture(messages[i].icon, x, y, messageHeight, messageHeight, 0, 0, 1, 1);
            x += messageHeight;
        }
        
        DrawRect(FLinearColor::Black, x, y, sizeX, messageHeight);
        DrawText(messages[i].message, messages[i].frontColor, x + pad, y + pad, hudFont);
        
        messages[i].time -= GetWorld()->GetDeltaSeconds();
        
        if (messages[i].time < 0)
        {
            messages.RemoveAt(i);
        }
    }
}


void AMyHUD::DrawWidgets()
{
    for(int i=0; i<widgets.Num(); i++)
    {
        DrawTexture(widgets[i].icon.icon, widgets[i].pos.X, widgets[i].pos.Y,
                    widgets[i].size.X, widgets[i].size.Y, 0, 0, 1, 1);
        DrawText(widgets[i].icon.name, FLinearColor::White,
                 widgets[i].pos.X, widgets[i].pos.Y, hudFont, .3f, false);
    }
}


void AMyHUD::DrawHealthBar()
{
    AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
    if (avatar == nullptr)
    {
        return;
    }
    
    float percentageHp = avatar->CurrentHP / avatar->MaxHP;
    
    DrawRect(FColor::White,
             Canvas->SizeX - barWidth - barPad - barMargin,
             Canvas->SizeY - barHeight - barPad - barMargin,
             barWidth + 2 * barPad, barHeight + 2 * barPad);
    
    DrawRect(FLinearColor(1 - percentageHp, percentageHp, 0, 1),
             Canvas->SizeX - barWidth - barMargin,
             Canvas->SizeY - barHeight - barMargin,
             barWidth * percentageHp, barHeight);
}


void AMyHUD::MouseClicked()
{
    FVector2D mouse;
    
    APlayerController *PController = GetWorld()->GetFirstPlayerController();
    PController->GetMousePosition(mouse.X, mouse.Y);
    
    for(int i=0; i<widgets.Num(); i++)
    {
        if(widgets[i].hit(mouse))
        {
            heldWidget = &widgets[i];
            return;
        }
    }
}


void AMyHUD::MouseMoved()
{
    APlayerController *PController = GetWorld()->GetFirstPlayerController();
    float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);
    
    static FVector2D lastMouse;
    FVector2D thisMouse, dMouse;
    PController->GetMousePosition( thisMouse.X, thisMouse.Y );
    dMouse = thisMouse - lastMouse;
    
    if(time > 0.f && heldWidget)
    {
        heldWidget->pos.X += dMouse.X;
        heldWidget->pos.Y += dMouse.Y;
    }
    
    lastMouse = thisMouse;
}


void AMyHUD::addMessage(Message msg)
{
    messages.Add(msg);
}


void AMyHUD::clearWidgets()
{
    widgets.Empty();
}


void AMyHUD::addWidget(Widget widget)
{
    FVector2D start(150, 150), pad(12, 12);
    widget.size = FVector2D(50, 50);
    widget.pos = start;

    // Compute the position here
    for(int i=0; i<widgets.Num(); i++)
    {
        // Move the position to the right a bit
        widget.pos.X += widget.size.X + pad.X;

        // If there is no more room to the right then, jump to the next line
        if( widget.pos.X + widget.size.X > dims.X )
        {
            widget.pos.X = start.X;
            widget.pos.Y += widget.size.Y + pad.Y;
        }
    }
    widgets.Add(widget);
}


void AMyHUD::debug(int slot, FColor color, FString message)
{
    if(GEngine)
    {
        GEngine->AddOnScreenDebugMessage(slot, 5.f, color, message);
    }
}
