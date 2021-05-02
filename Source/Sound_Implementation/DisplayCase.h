// Cameron Scholes (TheLazyHatGuy) 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisplayCase.generated.h"

class UBoxComponent;

UCLASS()
class SOUND_IMPLEMENTATION_API ADisplayCase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADisplayCase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool Smashed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_DisplayCase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_DisplayCase_Glass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_DisplayCase_Glass_Broken;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Jewellery_1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Jewellery_2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* SM_Jewellery_3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep,
			const FHitResult& SweepResult);

	void Smash();

	void TakeJewels();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
