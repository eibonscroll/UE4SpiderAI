// Fill out your copyright notice in the Description page of Project Settings.

#include "Move.h"
#include "SpiderPawn.h"


// Sets default values
ASpiderPawn::ASpiderPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpiderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpiderPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ASpiderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

