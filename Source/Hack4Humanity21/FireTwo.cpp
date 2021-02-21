// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTwo.h"

// Sets default values for this component's properties
UFireTwo::UFireTwo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
    
}


// Called when the game starts
void UFireTwo::BeginPlay()
{
	Super::BeginPlay();

	// ...
    AActor* Owner = GetOwner();
    InitialHealth = Owner->GetActorScale().X;
    CurrentHealth = InitialHealth;
    
    Owner->OnTakeAnyDamage.AddDynamic(this, &UFireTwo::TakeDamage);
}

void UFireTwo::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser) {

    if (Damage <= 0 || CurrentHealth <= 0) {
        return;
    }
    
    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, 100.f);
    
    if (CurrentHealth <= 0) {
        GetOwner()->Destroy();
    }
    
    float newScale = (CurrentHealth / InitialHealth);
    FVector newScaleVector = FVector(newScale);
    GetOwner()->SetActorScale3D(newScaleVector);
}



