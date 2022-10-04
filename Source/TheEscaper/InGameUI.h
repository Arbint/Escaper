// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class THEESCAPER_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void UpdateHealth(float health, float delta, float maxHealth);
	
	UFUNCTION()
	void NewWeaponAquired(class AWeapon* newWeapon);

	UFUNCTION()
	void WeaponSwitchedTo(class AWeapon* weapon);

	void ShowGameOverScreen();

	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UValueGauge* healthBar;

	UPROPERTY(meta = (BindWidget))
	class UImage* crossHair;

	UPROPERTY(meta = (BindWidget))
	class UListView* WeaponList;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* UISwicher;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GameOverRoot;
	
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* GameplayUIRoot;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* PauseUIRoot;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* menuBtnRoot;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* ResumeBtn;


	UFUNCTION()
		void Resume();
	UFUNCTION()
		void ReStart();
	UFUNCTION()
		void Quit();

	void ParentMenuPanelTo(UCanvasPanel* newParent);

	class AEGameMode* gameMode;
};
