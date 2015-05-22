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

USkeletalMeshComponent* ASpiderPawn::GetMesh()
{
    TArray<UActorComponent*> comps;
    USkeletalMeshComponent* thisComp = nullptr;

    GetComponents(comps);
    for (int i = 0; i < comps.Num(); ++i)
    {
        thisComp = Cast<USkeletalMeshComponent>(comps[i]);
        if (thisComp->GetName() == "Mesh")
            break;
    }
    return thisComp;
}

// Called every frame
void ASpiderPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    //Do Spider Traces
            FVector DirectionSocketLocation = GetMesh()->GetSocketLocation("DetectionSocket");
            FVector ChararacterForwardVector = GetActorForwardVector();
            FVector ChararacterLocation = GetActorLocation();

            //temp, up vector will only be up while on ground
            ChararacterLocation.Z = ChararacterLocation.Z - 84;

            //location in the ground and infront of spider
            FVector PointInFront = ChararacterLocation + (ChararacterForwardVector * 120.0);

            //location the PC is focused on
            const FVector Start = DirectionSocketLocation;


            const FVector End = PointInFront;

            //The trace data is stored here
            FHitResult HitData(ForceInit);

            static FName SpiderTraceIdent = FName(TEXT("SpidferTrace"));
            FCollisionQueryParams TraceParams(SpiderTraceIdent, true, this);
            TraceParams.bTraceAsyncScene = true;
            
            const FName TraceTag("SpiderTraceTag");

            GetWorld()->DebugDrawTraceTag = TraceTag;
            TraceParams.TraceTag = TraceTag;
  
            if (GetWorld()->LineTraceSingle(HitData, Start, End, ECollisionChannel::ECC_Pawn, TraceParams))
            {
                //Print out the name of the traced actor
                if (HitData.GetActor())
                {
                    //print(HitData.GetActor()->GetName());
                    //print(HitData.GetComponent()->GetName());
                }
            }
}

// Called to bind functionality to input
void ASpiderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ASpiderPawn::MoveForward()
{
    FVector loc = GetActorLocation();
    FVector forward = GetActorForwardVector();
    FVector newLocation = loc + (forward * speed);
    SetActorLocation(newLocation);
}

void ASpiderPawn::Rotate(int32 direction)
{

}
