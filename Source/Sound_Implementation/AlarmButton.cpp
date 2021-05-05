// Cameron Scholes (TheLazyHatGuy) 2021


#include "AlarmButton.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "FMODEvent.h"
#include "FMODBlueprintStatics.h"

#include "AlarmTrigger.h"
#include "Sound_ImplementationCharacter.h"

// Sets default values
AAlarmButton::AAlarmButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	Box_Collision->SetBoxExtent(FVector(130.0f, 50.0f, 60.0f));
	
	SM_AlarmButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Alarm Button"));
	SM_AlarmButton->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	RootComponent = SM_AlarmButton;
}

// Called when the game starts or when spawned
void AAlarmButton::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &AAlarmButton::OnOverlapBegin);
	Box_Collision->OnComponentEndOverlap.AddDynamic(this, &AAlarmButton::OnOverlapEnd);
}

// Called every frame
void AAlarmButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAlarmButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		if (PlayerRef == nullptr)
			PlayerRef = Cast<ASound_ImplementationCharacter>(OtherActor);

		PlayerRef->UI_Prompt = FString(TEXT("Press E to disable alarm"));
		
		PlayerRef->bShowPrompt = true;
		PlayerRef->Alarm_Button_Ref = this;
	}
}

void AAlarmButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		PlayerRef->bShowPrompt = false;
		PlayerRef->Alarm_Button_Ref = nullptr;
	}
}

void AAlarmButton::PressButton()
{
	if (AlarmTrigger -> bIsEnabled)
	{
		UFMODBlueprintStatics::PlayEventAtLocation(this, Press_Event, GetTransform(), true);

		AlarmTrigger -> bIsEnabled = false;
		PlayerRef->bShowPrompt = false;
		PlayerRef->Alarm_Button_Ref = nullptr;

		PlayerRef->PlayFMODEvent(PlayerRef->Alarm_Disabled_Dialogue_Event);
	}
}

