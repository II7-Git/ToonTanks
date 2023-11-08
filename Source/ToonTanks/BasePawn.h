// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	// 전방 선언: 아래 처럼 UCapsuleComponent에 대한 정의를 컴파일러가 모를 때 사용한다. 해당 클래스에 대한 정보가 없더라도 앞에 class를 선언하면 타입임을 컴파일러에게 알려서 오류를 발생시키지 않는다.
	// 사용 이유? 헤더 파일은 모든 내용이 프리프로세서에 의해 복사되기 때문에 그 크기를 작게 유지하는 것이 중요하다. 그래서 헤더파일에 include를 웬만해선 하지 않고 전방 선언으로 넘긴 뒤 본문에서 include하는 것이 좋다.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent *CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent *ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem *DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase *DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
