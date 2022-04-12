// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/AI/NpcController.h"
#include "NavigationSystem.h"
#include "NavigationData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "MyProject/AI/NPC.h"


ANpcController::ANpcController(FObjectInitializer const& object_initializer /*FObjectInitializer::Get()*/)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>bt_bp(TEXT("/Game/AI/NPC/NPC_BT"));
	if (bt_bp.Succeeded())
	{
		btree = bt_bp.Object;
	}

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("Behavior Tree Component"));

	blackboard_component = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Black Board Component"));
}

void ANpcController::BeginPlay()
{

	Super::BeginPlay();

	if(btree == nullptr)
	{ 
		UE_LOG(LogTemp, Error, TEXT("btree Not fonund, NpcController constructor."));
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("btree found."));
	}

	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}

void ANpcController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}

class UBlackboardComponent* ANpcController::GetBlackboardComponent() const
{
	return blackboard_component;
}

