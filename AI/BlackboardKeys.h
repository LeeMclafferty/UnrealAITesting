#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

/*Header with no data that just stores keys for a black board. All blackboard keys are stored as a char / string.*/
namespace bb_keys 
{
	const FName target_location =  TEXT("TargetLocation");
	const FName can_see_player = TEXT("CanSeePlayer");

}
