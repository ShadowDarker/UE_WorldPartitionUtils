#include "WorldPartitionStreaming/CheckWorldPartitionStreamingAsync.h"
#include "WorldPartition/WorldPartitionSubsystem.h"

UCheckWorldPartitionStreamingAsync* UCheckWorldPartitionStreamingAsync::CheckWorldPartitionStreamingAsync(UObject* WorldContext, const float TimeInterval)
{
	CheckWorldPartitionStreamingAsync* BlueprintNode = NewObject<CheckWorldPartitionStreamingAsync>();
	BlueprintNode->WorldContextObject = WorldContext;
	BlueprintNode->CheckInterval = TimeInterval;

	return BlueprintNode;
}

void UCheckWorldPartitionStreamingAsync::Activate()
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

void UCheckWorldPartitionStreamingAsync::CheckStreamingCompleted()
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

void UCheckWorldPartitionStreamingAsync::FinishStreaming()
{
	if (TimerHandle.IsValid() && World)
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

	SetReadyToDestroy();
}