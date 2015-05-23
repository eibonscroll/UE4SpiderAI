// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PawnMovementComponent.h"
#include "SpiderMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MOVE_API USpiderMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	
};
