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
#include "EGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "kismet/KismetSystemLibrary.h"

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
	GetOwningPlayer()->SetShowMouseCursor(true);
	UISwicher->SetActiveWidget(GameOverRoot);
	ParentMenuPanelTo(GameOverRoot);
	ResumeBtn->SetVisibility(ESlateVisibility::Hidden);
}
void UInGameUI::TooglePause()
{
	if (UISwicher->GetActiveWidget() == PauseUIRoot)
	{
		GetOwningPlayer()->SetShowMouseCursor(false);
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		UISwicher->SetActiveWidget(GameplayUIRoot);
	}
	else
	{
		GetOwningPlayer()->SetShowMouseCursor(true);
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		UISwicher->SetActiveWidget(PauseUIRoot);
		ParentMenuPanelTo(PauseUIRoot);
		ResumeBtn->SetVisibility(ESlateVisibility::Visible);
	}
}


void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	ResumeBtn->OnReleased.AddDynamic(this, &UInGameUI::Resume);
	QuitBtn->OnReleased.AddDynamic(this, &UInGameUI::Quit);
	RestartBtn->OnReleased.AddDynamic(this, &UInGameUI::ReStart);
	gameMode = Cast<AEGameMode>(UGameplayStatics::GetGameMode(this));
}

void UInGameUI::Resume()
{
	TooglePause();
}

void UInGameUI::ReStart()
{
	if (gameMode)
	{
		gameMode->RestartCurrentLevel();
	}
}

void UInGameUI::Quit()
{
	if (gameMode)
	{
		gameMode->QuitGame(GetOwningPlayer());
	}
}

void UInGameUI::ParentMenuPanelTo(UCanvasPanel* newParent)
{
	newParent->AddChild(menuBtnRoot);
	UCanvasPanelSlot* menuBtnSlot = Cast<UCanvasPanelSlot>(menuBtnRoot->Slot);
	menuBtnSlot->SetAnchors(FAnchors(0, 0, 1, 1));
	menuBtnSlot->SetOffsets(FMargin(0, 0));
	menuBtnSlot->SetAlignment(FVector2D(0, 0));
}
