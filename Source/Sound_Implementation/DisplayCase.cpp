// Cameron Scholes (TheLazyHatGuy) 2021


#include "DisplayCase.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FMODEvent.h"
#include "FMODBlueprintStatics.h"

#include "Sound_ImplementationCharacter.h"

// Sets default values
ADisplayCase::ADisplayCase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(130.0f, 50.0f, 60.0f));

	SM_DisplayCase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Case"));
	SM_DisplayCase->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SM_DisplayCase_Glass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Display Case Glass"));
	SM_DisplayCase_Glass->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SM_DisplayCase_Glass_Broken = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("Display Case Broken Glass"));
	SM_DisplayCase_Glass_Broken->SetHiddenInGame(true, false);

	SM_Jewellery_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jewellery 1"));
	SM_Jewellery_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jewellery 2"));
	SM_Jewellery_3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Jewellery 3"));

	RootComponent = SM_DisplayCase;

	Smashed = false;
	Jewels_Taken = false;
}

// Called when the game starts or when spawned
void ADisplayCase::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ADisplayCase::OnOverlapBegin);
	Box_Collision->OnComponentEndOverlap.AddDynamic(this, &ADisplayCase::OnOverlapEnd);
}

// Called every frame
void ADisplayCase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADisplayCase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player") && !Jewels_Taken)
	{
		if (PlayerRef == nullptr)
			PlayerRef = Cast<ASound_ImplementationCharacter>(OtherActor);

		if(!Smashed)
			PlayerRef->UI_Prompt = FString(TEXT("Press E to smash glass"));
		else
			PlayerRef->UI_Prompt = FString(TEXT("Press E to take jewels"));
		
		PlayerRef->bShowPrompt = true;
		PlayerRef->Display_Case_Ref = this;
	}
}

void ADisplayCase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		PlayerRef->bShowPrompt = false;
		PlayerRef->Display_Case_Ref = nullptr;
	}
}

void ADisplayCase::Smash()
{
	if(Smashed && !Jewels_Taken)
	{
		TakeJewels();
		return;
	}
	
	
	const FVector Translation = FVector(0.0f, 0.0f, 0.0f);
	const FVector Scale = FVector(1.0f, 1.0f, 1.0f);
	const FQuat Rotation = FQuat(0.0f, 0.0f, 0.0f, 0.0f);
	// const FTransform Transform = FTransform(Rotation, Translation, Scale);
	const FTransform Transform = this->GetTransform();;
	
	UFMODBlueprintStatics::PlayEventAtLocation(this, Smash_Event, 
		Transform, true);


	SM_DisplayCase_Glass->SetHiddenInGame(true, false);
	SM_DisplayCase_Glass_Broken->SetHiddenInGame(false, false);

	Smashed = true;
	PlayerRef->UI_Prompt = FString(TEXT("Press E to take jewels"));
}

void ADisplayCase::TakeJewels()
{
	const FTransform Transform = this->GetTransform();;

	UFMODBlueprintStatics::PlayEventAtLocation(this, Pickup_Event,
		Transform, true);

	SM_Jewellery_1->SetHiddenInGame(true, false);
	SM_Jewellery_2->SetHiddenInGame(true, false);
	SM_Jewellery_3->SetHiddenInGame(true, false);

	Jewels_Taken = true;
	PlayerRef->bShowPrompt = false;
	PlayerRef->Display_Case_Ref = nullptr;
	PlayerRef->Cash += 25000;
}
