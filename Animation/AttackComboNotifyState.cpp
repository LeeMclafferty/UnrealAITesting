// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComboNotifyState.h"
#include "MyProject/Player/CharacterBase.h"
#include "Kismet/GameplayStatics.h"

void UAttackComboNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	// Have to use mesh component and not use UGameplayStatics since that is the ref the notify has.
	if (ACharacterBase* pawn = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		pawn->is_attacking = true;
	}

}

void UAttackComboNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (ACharacterBase* pawn = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		pawn->is_attacking = false;
	}

}
