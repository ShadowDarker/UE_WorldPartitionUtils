#include "WorldPartitionStreaming/CheckWorldPartitionStreaming.h"
#include "WorldPartition/WorldPartitionSubsystem.h"

UCheckWorldPartitionStreaming* UCheckWorldPartitionStreaming::CheckWorldPartitionStreaming(UObject* WorldContext, const float TimeInterval)
{
	UCheckWorldPartitionStreaming* BlueprintNode = NewObject<UCheckWorldPartitionStreaming>();
	BlueprintNode->WorldContextObject = WorldContext;
	BlueprintNode->CheckInterval = TimeInterval;

	return BlueprintNode;
}

void UCheckWorldPartitionStreaming::Activate()
{
	World = WorldContextObject->GetWorld();

#if WITH_EDITOR	
	// If world is not valid, but editor is, use the current editor world
	if (!World && GEditor)
	{
		World = GEditor->GetEditorWorldContext().World();
	}
#endif	

	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("World is not valid"));
		OnStreamingFailed.Broadcast();
		return;
	}
		
	World->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::CheckStreamingCompleted, CheckInterval, true);
}

void UCheckWorldPartitionStreaming::CheckStreamingCompleted()
{
	UWorldPartitionSubsystem* WorldPartitionSubsystem = World->GetSubsystem<UWorldPartitionSubsystem>(World);

	if (!WorldPartitionSubsystem)
	{
		OnStreamingFailed.Broadcast();
		FinishStreaming();
		return;
	}

	if (WorldPartitionSubsystem->IsAllStreamingCompleted())
	{
		OnStreamingCompleted.Broadcast();
		FinishStreaming();
	}
}

void UCheckWorldPartitionStreaming::FinishStreaming()
{
	if (TimerHandle.IsValid() && World)
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

	SetReadyToDestroy();
}