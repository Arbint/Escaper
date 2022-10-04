// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ValueGauge.h"
#include "Components/ListView.h"
#include "Components/Image.h"
#include "Weapon.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"

void UInGameUI::UpdateHealth(float health, float delta, float maxHealth)
{
	healthBar->SetValue(health, delta, maxHealth);
}

void UInGameUI::NewWeaponAquired(AWeapon* newWeapon)
{
	WeaponList->AddItem(newWeapon);
}

void UInGameUI::WeaponSwitchedTo(AWeapon* weapon)
{
	WeaponList->ScrollIndexIntoView(WeaponList->GetIndexForItem(weapon));
	WeaponList->SetSelectedItem(weapon);
	UTexture2D* crossHairTexture = weapon->GetCrossHairTexture();
	if (crossHairTexture)
	{
		crossHair->SetBrushFromTexture(weapon->GetCrossHairTexture());
		crossHair->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		crossHair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInGameUI::ShowGameOverScreen()
{
	GetOwningPlayer()->bShowMouseCursor = true;
	UISwicher->SetActiveWidget(GameOverRoot);
	ParentMenuPanelTo(GameOverRoot);
	ResumeBtn->SetVisibility(ESlateVisibility::Hidden);
}	

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	ResumeBtn->OnReleased.AddDynamic(this, &UInGameUI::Resume);
	QuitBtn->OnReleased.AddDynamic(this, &UInGameUI::Quit);
	RestartBtn->OnReleased.AddDynamic(this, &UInGameUI::ReStart);
}

void UInGameUI::Resume()
{

}

void UInGameUI::ReStart()
{

}

void UInGameUI::Quit()
{

}

void UInGameUI::ParentMenuPanelTo(UCanvasPanel* newParent)
{
	newParent->AddChild(menuBtnRoot);
	UCanvasPanelSlot* menuBtnSlot = Cast<UCanvasPanelSlot>(menuBtnRoot->Slot);
	menuBtnSlot->SetAnchors(FAnchors(0, 0, 1, 1));
	menuBtnSlot->SetOffsets(FMargin(0, 0));
	menuBtnSlot->SetAlignment(FVector2D(0, 0));
}
