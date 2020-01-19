// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPTest.h"
#include "UDPActorComponent.h"
#include "Engine.h"


// Sets default values for this component's properties
UUDPActorComponent::UUDPActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUDPActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FString address = TEXT("127.0.0.1");
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);
	Socket = FUdpSocketBuilder(TEXT("UDP Socket"))
		.AsNonBlocking()
		.AsReusable()
		.BoundToAddress(ip)
		.BoundToPort(8888)
		.WithMulticastLoopback();
}


// Called every frame
void UUDPActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...

	uint32 Bytes;
	if (Socket->HasPendingData(Bytes))
	{
		uint8 data[64] = { 0 };
		int32 read_bytes;
		Socket->Recv(data, sizeof(data), read_bytes);
		if (read_bytes > 0)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Yellow, *FString::Printf(TEXT("read_bytes=%d : %s"), read_bytes, data));
			AActor *actor = GetOwner();
			FVector t = actor->GetActorLocation();
			if (read_bytes == 1) t.X += 10;
			if (read_bytes == 2) t.Y += 10;
			if (read_bytes == 3) t.Z += 10;
			if (read_bytes == 4) t.X -= 10;
			if (read_bytes == 5) t.Y -= 10;
			if (read_bytes == 6) t.Z -= 10;
			actor->SetActorLocation(t);

		}

	}
}


void UUDPActorComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Socket)
	{
		Socket->Close();
		delete Socket;
	}
}


