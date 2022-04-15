// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/AI/NpcController.h"
#include "NavigationSystem.h"
#include "NavigationData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"


#include "MyProject/AI/NPC.h"
#include "MyProject/Player/CharacterBase.h"
#include "MyProject/AI/BlackboardKeys.h"

ANpcController::ANpcController(FObjectInitializer const& object_initializer /*FObjectInitializer::Get()*/)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>bt_bp(TEXT("/Game/AI/NPC/NPC_BT"));
	if (bt_bp.Succeeded())
	{
		btree = bt_bp.Object;
	}

	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("Behavior Tree Component"));

	blackboard_component = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Black Board Component"));

	SetupPerceptionSystem();
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

void ANpcController::ActorsPerceptionUpdated(TArray<AActor*> const& UpdatedActors)
{

}

void ANpcController::OnTargetDetected(AActor* actor, FAIStimulus stimulus)
{
	// Searching for player character class. Returns true to the bb key if found.
	if (const ACharacterBase* player = Cast<ACharacterBase>(actor))
	{
		GetBlackboardComponent()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

void ANpcController::SetupPerceptionSystem()
{
	// Set up all defaults for sight config.
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	perception_comp = CreateDefaultSubobject<UAIPerceptionComponent>((TEXT("Perception Comp")));
	SetPerceptionComponent(*perception_comp);

	sight_config->SightRadius = 500.f;
	sight_config->LoseSightRadius = sight_config->SightRadius + 50.f;
	sight_config->PeripheralVisionAngleDegrees = 90.f;
	sight_config->AutoSuccessRangeFromLastSeenLocation = 900.f;
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(sight_config->GetSenseImplementation());

	/*This is like other AddDynamic functions(overlaps ect.) and will call this function when a stimuli is detected.*/
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ANpcController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*sight_config);


}

