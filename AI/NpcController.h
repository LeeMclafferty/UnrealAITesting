// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NpcController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYPROJECT_API ANpcController : public AAIController
{
	GENERATED_BODY()


public:

	ANpcController(FObjectInitializer const& object_initializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* const pawn) override;
	
	class UBlackboardComponent* GetBlackboardComponent() const;
	
private:
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* behavior_tree_component;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* btree;
	
	class UBlackboardComponent* blackboard_component;
};
