// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "SpiderMovementComponent.h"
#include "SpiderPawn.generated.h"

UCLASS()
class MOVE_API ASpiderPawn : public APawn
{
    GENERATED_BODY()

private:
    USkeletalMeshComponent * GetMesh();
    
    bool TransitionToWall();

    FVector LastSurfaceNormal;

    FVector GetZVector();

    FVector DirectionSocketLocation;

    FVector UnderBellySocketLoc; 
    FVector FrontSocketLoc; 
    FVector BellySocketLoc; 
    FVector FLSocketLoc;
    FVector FRSocketLoc; 
    FVector BLSocketLoc; 
    FVector BRSocketLoc; 

    void StickToSurface();

public:
	// Sets default values for this pawn's properties
	ASpiderPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spider Move")
    float speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spider Move")
    float rotationSpeed;

    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void StopMovement();

    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void MoveForward();

    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void MoveBackward();
    
    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void RotateRight();

    UFUNCTION(BlueprintCallable, Category = "Spider Move")
    void RotateLeft();

    class USpiderMovementComponent* MovementComponent;

    virtual UPawnMovementComponent* GetMovementComponent() const override;
};
