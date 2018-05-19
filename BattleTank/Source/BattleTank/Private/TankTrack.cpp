// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}
void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"));
}
//增加坦克的横向力
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//加速度
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime*GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = CorrectionAcceleration*(TankRoot->GetMass())/2;
	//UE_LOG(LogTemp, Warning, TEXT("CorrectionForce:%s"), *CorrectionForce.ToString());
	TankRoot->AddForce(CorrectionForce);

}


void UTankTrack::SetThrottle(float Throtttle)
{
	auto ForceAppiled = GetForwardVector()*Throtttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceAppiled, ForceLocation);
	auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s: is: %f"), *Name, Throtttle);
}
