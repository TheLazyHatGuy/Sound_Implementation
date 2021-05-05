// Cameron Scholes (TheLazyHatGuy) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AlarmButton.generated.h"

class UBoxComponent;
class ASound_ImplementationCharacter;
class AAlarmTrigger;
class UFMODEvent;

UCLASS()
class SOUND_IMPLEMENTATION_API AAlarmButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlarmButton();

	UPROPERTY(EditAnywhere)
	AAlarmTrigger* AlarmTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* SM_AlarmButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Box_Collision;

	UPROPERTY(EditAnywhere, Category = FMOD)
	UFMODEvent* Press_Event;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PressButton();
	
private:
	UPROPERTY(VisibleAnywhere)
	ASound_ImplementationCharacter* PlayerRef;
};