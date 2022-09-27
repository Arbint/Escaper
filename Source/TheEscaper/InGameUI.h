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
	void WeaponEquiped(class AWeapon* weapon);

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* CrossHair;
};
