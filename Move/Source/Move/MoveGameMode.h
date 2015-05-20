// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MoveGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MOVE_API AMoveGameMode : public AGameMode
{
	GENERATED_BODY()
	
    virtual void StartPlay() override;
	
    AMoveGameMode(const FObjectInitializer& ObjectInitializer);
};
