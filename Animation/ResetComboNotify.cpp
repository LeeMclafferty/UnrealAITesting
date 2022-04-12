// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetComboNotify.h"
#include "MyProject/Player/CharacterBase.h"

void UResetComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (ACharacterBase* pawn = Cast<ACharacterBase>(MeshComp->GetOwner()))
	{
		pawn->is_attacking = false;
		pawn->SetComboCounter(0);
	}
}
