// Fill out your copyright notice in the Description page of Project Settings.

#include "Move.h"
#include "SpiderPawn.h"


// Sets default values
ASpiderPawn::ASpiderPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    bUseControllerRotationRoll = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
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
        if (thisComp && thisComp->GetName() == "Mesh")
            break;
    }
    return thisComp;
}

void ASpiderPawn::UpdateSurface()
{
}

// Called every frame
void ASpiderPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

   // UpdateSurface();

    //Do Spider Traces
            FVector DirectionSocketLocation = GetMesh()->GetSocketLocation("DetectionSocket");

            FVector BellySocketLoc = GetMesh()->GetSocketLocation("Belly");
            FVector FLSocketLoc = GetMesh()->GetSocketLocation("FL");
            FVector FRSocketLoc = GetMesh()->GetSocketLocation("FR");
            FVector BLSocketLoc = GetMesh()->GetSocketLocation("BL");
            FVector BRSocketLoc = GetMesh()->GetSocketLocation("BR");

            FVector ChararacterForwardVector = GetActorForwardVector();
            FVector ChararacterLocation = GetActorLocation();

            //temp, up vector will only be up while on ground
            ChararacterLocation.Z = ChararacterLocation.Z - 84;

            //location in the ground and infront of spider
            FVector PointInFront = ChararacterLocation + (ChararacterForwardVector * 30.0);

            //location the PC is focused on
            const FVector Start = DirectionSocketLocation;


            const FVector End = PointInFront;

            //The trace data is stored here
            FHitResult HitData(ForceInit);

            static FName SpiderTraceIdent = FName(TEXT("SpidferTrace"));
            FCollisionQueryParams TraceParams(SpiderTraceIdent, true, this);
            TraceParams.bTraceAsyncScene = true;
            
            //const FName TraceTag("SpiderTraceTag");

            //GetWorld()->DebugDrawTraceTag = TraceTag;
            //TraceParams.TraceTag = TraceTag;
            FVector HitNormal;

            //Directly Under
            if (GetWorld()->LineTraceSingle(HitData, Start, BellySocketLoc, ECollisionChannel::ECC_Pawn, TraceParams))
            {
                HitNormal = HitData.ImpactNormal;

                FRotator newRot = HitNormal.Rotation();

                

               FTransform TheTransform = this->GetTransform();
               FRotator temp = FRotator(FQuat::FastLerp(TheTransform.Rotator().Quaternion(), newRot.Quaternion(), DeltaTime));
               temp.Roll = TheTransform.Rotator().Roll;
               temp.Yaw = TheTransform.Rotator().Yaw;

               TheTransform.SetRotation(temp.Quaternion());

                //TheTransform.ConcatenateRotation(rot.Quaternion());
                //TheTransform.NormalizeRotation();
                this->SetActorTransform(TheTransform);
                
                //if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
                //{
                //    //FString hitMessage = HitData.GetActor()->GetName();
                //    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
                //}
            }

            //Point directly in front
            if (GetWorld()->LineTraceSingle(HitData, Start, End, ECollisionChannel::ECC_Pawn, TraceParams))
            {
                HitNormal = HitData.ImpactNormal;
                if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
                {
                    TransitionToWall();
                    //FString hitMessage = HitData.GetActor()->GetName();
                    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
                }
            }

            //On all 4 corners
            //if (GetWorld()->LineTraceSingle(HitData, Start, FLSocketLoc, ECollisionChannel::ECC_Pawn, TraceParams))
            //{
            //    HitNormal = HitData.ImpactNormal;
            //    if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
            //    {
            //        //FString hitMessage = HitData.GetActor()->GetName();
            //        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
            //    }
            //}

            //if (GetWorld()->LineTraceSingle(HitData, Start, FRSocketLoc, ECollisionChannel::ECC_Pawn, TraceParams))
            //{
            //    HitNormal = HitData.ImpactNormal;
            //    if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
            //    {
            //        //FString hitMessage = HitData.GetActor()->GetName();
            //        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
            //    }
            //}

            //if (GetWorld()->LineTraceSingle(HitData, Start, BLSocketLoc, ECollisionChannel::ECC_Pawn, TraceParams))
            //{
            //    HitNormal = HitData.ImpactNormal;
            //    if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
            //    {
            //        //FString hitMessage = HitData.GetActor()->GetName();
            //        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
            //    }
            //}

            //if (GetWorld()->LineTraceSingle(HitData, Start, BRSocketLoc, ECollisionChannel::ECC_Pawn, TraceParams))
            //{
            //    HitNormal = HitData.ImpactNormal;
            //    if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
            //    {
            //        //FString hitMessage = HitData.GetActor()->GetName();
            //        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
            //    }
            //}
}

// Called to bind functionality to input
void ASpiderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ASpiderPawn::TransitionToWall()
{
    FTransform TheTransform = this->GetTransform();

    FRotator rot = FRotator(90, 0, 0);

    TheTransform.ConcatenateRotation(rot.Quaternion());
    TheTransform.NormalizeRotation();
    this->SetActorTransform(TheTransform);
}

void ASpiderPawn::MoveForward()
{
    FVector loc = GetActorLocation();
    FVector forward = GetActorForwardVector();
    FVector newLocation = loc + (forward * speed);
    SetActorLocation(newLocation);
}

void ASpiderPawn::MoveBackward()
{
    FVector loc = GetActorLocation();
    FVector forward = GetActorForwardVector();
    FVector newLocation = loc - (forward * speed);
    SetActorLocation(newLocation);
}

void ASpiderPawn::RotateRight()
{
    FTransform TheTransform = this->GetTransform();

    FRotator rot = FRotator(0, rotationSpeed, 0);

    TheTransform.ConcatenateRotation(rot.Quaternion());
    TheTransform.NormalizeRotation();
    this->SetActorTransform(TheTransform);
}

void ASpiderPawn::RotateLeft()
{
    FTransform TheTransform = this->GetTransform();

    FRotator rot = FRotator(0, -rotationSpeed, 0);

    TheTransform.ConcatenateRotation(rot.Quaternion());
    TheTransform.NormalizeRotation();
    this->SetActorTransform(TheTransform);
}
