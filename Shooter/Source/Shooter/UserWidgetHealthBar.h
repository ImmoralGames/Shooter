// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "UserWidgetHealthBar.generated.h"

/**
 * 
 */
UCLASS(abstract, BlueprintType, Blueprintable)
class SHOOTER_API UUserWidgetHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Pawn|UI")
	virtual void UpdateHealth_Implementation(int32 current, int32 max) PURE_VIRTUAL(UUserWidgetHealthBar::UpdateHealth, );

public:

	UFUNCTION(BlueprintNativeEvent, Category = "Pawn|UI")
	void UpdateHealth(int32 current, int32 max);
};
