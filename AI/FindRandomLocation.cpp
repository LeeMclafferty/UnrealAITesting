// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/AI/FindRandomLocation.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "UObject/UObjectGlobals.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "MyProject/AI/BlackBoardKeys.h" //This is my header that just stores the key string data
#include "MyProject/AI/NpcController.h"
#include "MyProject/AI/NPC.h"

UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& object_initializer)
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	/* Cast to AI controller.Owner comp will be the Behavior tree and that is owned by the controller.
	Also try to have the habit of making these case const when you can.*/
	const ANpcController* controller = Cast<ANpcController>(owner_comp.GetAIOwner());

	const ANPC* npc = Cast<ANPC>(controller->GetPawn());

	/*starting location of your NPC*/
	FVector starting_location = npc->GetActorLocation();

	/*Where the random location will be stored*/
	FNavLocation rand_location;

	/*Get the nav system then generate a random location on the nav mesh.
	*GetCurrent returns the current navigation system.
	* GetRandomPointInNavigabvleRadius uses main nav data if you pass in null
	*/
	UNavigationSystemV1* nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (nav_sys->GetRandomPointInNavigableRadius(starting_location, search_radius, rand_location, nullptr))
	{
		/*Pass in the bb_keys::target location from my key strings header.*/
		controller->GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location, rand_location.Location);
	}

	/*Specify when the task is complete, in this case it is when the AI succeeds at the task, but there could be an option for failure in other cases.*/
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
