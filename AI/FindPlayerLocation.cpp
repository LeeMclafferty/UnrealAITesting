// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/AI/FindPlayerLocation.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "UObject/UObjectGlobals.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

#include "MyProject/AI/BlackBoardKeys.h" 
#include "MyProject/AI/NpcController.h"
#include "MyProject/AI/NPC.h"
#include "MyProject//Player/CharacterBase.h"


UFindPlayerLocation::UFindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	if (ACharacterBase* player = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		if (ANpcController* npc_controller = Cast<ANpcController>(owner_comp.GetAIOwner()))
		{
			FVector player_location = player->GetActorLocation();

			if (search_random)
			{
				FNavLocation location;

				UNavigationSystemV1* nav_system = UNavigationSystemV1::GetCurrent(GetWorld());

				/* Just gets a point based on search_radius.Just like FindRandomLocation, but this is a smaller radius since the AI is looking for the player in that radius.*/
				if (nav_system->GetRandomPointInNavigableRadius(player_location, search_radius, location, nullptr))
				{
					npc_controller->GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location, location.Location);
				}
			}
			else
			{
				/*If search random is false, then we have found the player and now our target location is going to be the player. */
				npc_controller->GetBlackboardComponent()->SetValueAsVector(bb_keys::target_location, player_location);
			}
		}
	}
	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
