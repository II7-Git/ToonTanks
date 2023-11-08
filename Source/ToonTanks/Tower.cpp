// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (InFireRange())
    {

        RotateTurret(Tank->GetActorLocation());
    }
}
void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}
void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // GetWorldTimerManager().SetTimer(FTimerHandle & InOutHandle,UserClass * InObj, InTimerMethod, float InRate, bool InbLoop)
    // GetWorldTimerManager().SetTimer(FTimerHandle,실행할 객체(this),실행할 함수의 주소,이 시간이 지나면 콜백 함수 호출,함수를 반복 실행할지 여부)
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
    if (Tank == nullptr)
    {
        return;
    }
    if (InFireRange() && Tank->bAlive)
    {

        Fire();
    }
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}