// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}




void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied =  CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel =ForceApplied/Wheels.Num();
	for (ASprungWheel*Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}

}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* child:Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(child);
		if (!SpawnPointChild) continue;
		
		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		if (!SpawnedChild) continue;
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		ResultArray.Add(SprungWheel);
	}
	return ResultArray;
}