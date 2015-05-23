// Fill out your copyright notice in the Description page of Project Settings.

#include "Move.h"
#include "SpiderPawn.h"


// Sets default values
ASpiderPawn::ASpiderPawn()
{
    LastSurfaceNormal = FVector(0,0,1);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    bUseControllerRotationRoll = false;
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;

    // Create an instance of our movement component, and tell it to update the root.
    MovementComponent = CreateDefaultSubobject<USpiderMovementComponent>(TEXT("CustomMovementComponent"));
    MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ASpiderPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

UPawnMovementComponent* ASpiderPawn::GetMovementComponent() const
{
    return MovementComponent;
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

// Called every frame
void ASpiderPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    //Do Spider Traces
            DirectionSocketLocation = GetMesh()->GetSocketLocation("DetectionSocket");

            UnderBellySocketLoc = GetMesh()->GetSocketLocation("UnderBelly");
            FrontSocketLoc = GetMesh()->GetSocketLocation("Front");
            BellySocketLoc = GetMesh()->GetSocketLocation("Belly");
            FLSocketLoc = GetMesh()->GetSocketLocation("FL");
            FRSocketLoc = GetMesh()->GetSocketLocation("FR");
            BLSocketLoc = GetMesh()->GetSocketLocation("BL");
            BRSocketLoc = GetMesh()->GetSocketLocation("BR");

            FVector ChararacterForwardVector = GetActorForwardVector();
            FVector ChararacterLocation = GetActorLocation();

            //temp, up vector will only be up while on ground
            ChararacterLocation.Z = ChararacterLocation.Z - 84;

            //location in the ground and infront of spider
            FVector PointInFront = ChararacterLocation + (ChararacterForwardVector * 30.0);


            //The trace data is stored here
            FHitResult HitData(ForceInit);

            static FName SpiderTraceIdent = FName(TEXT("SpidferTrace"));
            FCollisionQueryParams TraceParams(SpiderTraceIdent, true, this);
            TraceParams.bTraceAsyncScene = true;
            
            //const FName TraceTag("SpiderTraceTag");

            //GetWorld()->DebugDrawTraceTag = TraceTag;
            //TraceParams.TraceTag = TraceTag;
            FVector HitNormal;


            //Point directly in front
            if (GetWorld()->LineTraceSingle(HitData, BellySocketLoc, FrontSocketLoc, ECollisionChannel::ECC_Pawn, TraceParams))
            {
                HitNormal = HitData.ImpactNormal;
                //if (HitData.GetActor() && (HitNormal.Y <= -0.02 || HitNormal.Y >= 0.02 || HitNormal.X <= -0.02 || HitNormal.X >= 0.02))
                if (HitData.GetActor())
                {
                    TransitionToWall();
                    //FString hitMessage = HitData.GetActor()->GetName();
                    //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *hitMessage);
                }
            }

            if(! TransitionToWall() )
                StickToSurface();
}

// Called to bind functionality to input
void ASpiderPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

FVector ASpiderPawn::GetZVector()
{
    FVector DirectionSocketLocation = GetMesh()->GetSocketLocation("DetectionSocket");
    FVector BellySocketLoc = GetMesh()->GetSocketLocation("Belly");
    return DirectionSocketLocation - BellySocketLoc;
    
}

void ASpiderPawn::StickToSurface()
{
    //Grab a ref to the world here
    UWorld* world = GetWorld();

    FHitResult hitResultTrace;
    FCollisionQueryParams queryParams;
    FCollisionObjectQueryParams objQueryParams;

    queryParams.AddIgnoredActor(this);

    FVector under;

    FVector newUp;
    FVector newForward;
    FVector newRight;

    //Trace to get the floor normal under your actor
    if (world->LineTraceSingle(hitResultTrace, BellySocketLoc, UnderBellySocketLoc, queryParams, objQueryParams))
    {
        under = hitResultTrace.ImpactPoint;
        newUp = hitResultTrace.ImpactNormal;
    }

    //Some math to get the new Axis
    FVector currentRightVect = GetActorRightVector();
    newForward = FVector::CrossProduct(currentRightVect, newUp);
    newRight = FVector::CrossProduct(newUp, newForward);

    //Build the new transform!
    FTransform newTransform(newForward, newRight, newUp, under);
    SetActorTransform(newTransform);
}

bool ASpiderPawn::TransitionToWall()
{
    bool retval = false;

    //Grab a ref to the world here
    UWorld* world = GetWorld();

    FHitResult hitResultTrace;
    FCollisionQueryParams queryParams;
    FCollisionObjectQueryParams objQueryParams;

    queryParams.AddIgnoredActor(this);

    FVector under;

    FVector newUp;
    FVector newForward;
    FVector newRight;

    //Trace to get the surface normal in front of actor
    if (world->LineTraceSingle(hitResultTrace, BellySocketLoc, FrontSocketLoc, queryParams, objQueryParams))
    {
            under = hitResultTrace.ImpactPoint;
            newUp = hitResultTrace.ImpactNormal;

            //Some math to get the new Axis
            FVector currentRightVect = GetActorRightVector();
            newForward = FVector::CrossProduct(currentRightVect, newUp);
            newRight = FVector::CrossProduct(newUp, newForward);

            //Build the new transform!
            FTransform newTransform(newForward, newRight, newUp, under);
            SetActorTransform(newTransform);
            retval = true;
    }

    return retval;
}

void ASpiderPawn::MoveForward()
{
    if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
    {
        MovementComponent->AddInputVector(GetActorForwardVector() * speed);
    }
}

void ASpiderPawn::StopMovement()
{
    if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
    {
        MovementComponent->StopMovementImmediately();
    }
}

void ASpiderPawn::MoveBackward()
{
    if (MovementComponent && (MovementComponent->UpdatedComponent == RootComponent))
    {
        MovementComponent->AddInputVector(GetActorForwardVector() * -speed);
    }
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
