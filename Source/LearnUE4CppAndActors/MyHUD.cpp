// Fill out your copyright notice in the Description page of Project Settings.

#include "LearnUE4CppAndActors.h"
#include "MyHUD.h"
#include "Avatar.h"


void AMyHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawMessages();
    DrawHealthBar();
}

void AMyHUD::addMessage(Message msg)
{
    messages.Add(msg);
}


void AMyHUD::DrawMessages()
{
    float pad = 10.f;
    int sizeX = Canvas->SizeX;
    
    for(int i=messages.Num() - 1; i>=0; i--)
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
        DrawText(messages[i].message, messages[i].color, x + pad, y + pad, hudFont);
        
        messages[i].time -= GetWorld()->GetDeltaSeconds();
        
        if (messages[i].time < 0)
        {
            messages.RemoveAt(i);
        }
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
