// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Networking.h"
#include "UDPActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDPTEST_API UUDPActorComponent : public UActorComponent
{
	GENERATED_BODY()
	FSocket* Socket;

public:	
	// Sets default values for this component's properties
	UUDPActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
};
