// Cameron Scholes (TheLazyHatGuy) 2021


#include "AlarmTrigger.h"

#include "Components/BoxComponent.h"
#include "FMODEvent.h"
#include "FMODBlueprintStatics.h"

#include "Sound_ImplementationCharacter.h"

// Sets default values
AAlarmTrigger::AAlarmTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(20.0f, 50.0f, 100.0f));

	bIsEnabled = true;
	bIsTriggered = false;
}

// Called when the game starts or when spawned
void AAlarmTrigger::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAlarmTrigger::OnOverlapBegin);
}

// Called every frame
void AAlarmTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAlarmTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player") && bIsEnabled && !bIsTriggered)
	{
		ASound_ImplementationCharacter* PlayerRef = Cast<ASound_ImplementationCharacter>(OtherActor);
		
		bIsTriggered = true;

		PlayerRef->PlayFMODEvent(PlayerRef->Alarm_Dialogue_Event);
		
		UFMODBlueprintStatics::PlayEventAtLocation(this, Alarm_Event, 
			GetTransform(), true);
	}
}