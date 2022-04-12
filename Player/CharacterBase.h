// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProjectCharacter.h"
#include "CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ACharacterBase : public AMyProjectCharacter
{
	GENERATED_BODY()
	
	ACharacterBase();

public:

	UPROPERTY(BlueprintReadOnly)
	bool is_attacking;

	int32 GetComboCounter() { return combo_counter; }
	void SetComboCounter(int new_combo) { combo_counter = new_combo; }

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* weapon_mesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* shield_mesh;

	//Sword attack montages, will be moved later to be more dynamic. (Each weapon will probably store its animations)
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UAnimMontage* sword_attack1;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UAnimMontage* sword_attack2;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	class UAnimMontage* sword_attack3;

private:

	void OnPressAttackButton();
	void OnReleaseAttachButton();
	int32 combo_counter;
};
