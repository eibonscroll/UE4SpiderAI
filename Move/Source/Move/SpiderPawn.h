// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "SpiderPawn.generated.h"

UCLASS()
class MOVE_API ASpiderPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpiderPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void MoveForward();
    
    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void Rotate(int32 direction);

};
