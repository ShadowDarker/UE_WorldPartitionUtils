#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CheckWorldPartitionStreaming.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWorldPartitionStreamingDelegate);

/**
 * @class UCheckWorldPartitionStreaming
 * @brief Async event action class that returns a callback when World Partition streaming has finished loading.
 */
UCLASS()
class WORLDPARTITIONUTILS_API UCheckWorldPartitionStreaming : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	/**
	 * @brief Async class instance call.
	 * @param WorldContext World reference.
	 * @param TimeInterval Interval in seconds to repeat data layer load check.
	 * @return StreamDataLayers reference.
	 */
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContext", BlueprintInternalUseOnly = "true"), Category = "LevelStreaming")
	static UCheckWorldPartitionStreaming* CheckWorldPartitionStreaming(UObject* WorldContext, const float TimeInterval = 0.2f);

	/**
	 * @brief Streaming completed callback.
	 */
	UPROPERTY(BlueprintAssignable, Category = "LevelStreaming")
	FWorldPartitionStreamingDelegate OnStreamingCompleted;

	/**
	 * @brief Streaming failed callback.
	 */
	UPROPERTY(BlueprintAssignable, Category = "LevelStreaming")
	FWorldPartitionStreamingDelegate OnStreamingFailed;

private:

	virtual void Activate() override;

	void CheckStreamingCompleted();

	void FinishStreaming();

private:

	UPROPERTY()
	UObject* WorldContextObject;

	UPROPERTY()
	UWorld* World;

	float CheckInterval = 0.2f;

	FTimerHandle TimerHandle;
};