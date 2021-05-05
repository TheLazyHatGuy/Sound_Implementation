// Cameron Scholes (TheLazyHatGuy) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlarmTrigger.generated.h"

class UBoxComponent;
class UFMODEvent;

UCLASS()
class SOUND_IMPLEMENTATION_API AAlarmTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlarmTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Box_Collision;
	
	UPROPERTY(EditAnywhere, Category = FMOD)
	UFMODEvent* Alarm_Event;

	UPROPERTY(VisibleAnywhere)
	bool bIsEnabled;

	UPROPERTY(VisibleAnywhere)
	bool bIsTriggered;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
		const FHitResult& SweepResult);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
