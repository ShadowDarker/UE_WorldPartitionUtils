#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WorldPartitionBlueprintFunctionLibrary.generated.h"

struct FDataLayerStreamingData;
/**
 * 
 */
UCLASS()
class WORLDPARTITIONUTILS_API UWorldPartitionBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "DataLayer")
	static bool HandleDataLayerStreamingOperations(UObject* WorldContextObject, TArray<FDataLayerStreamingData> DataLayerStreamingDataContainers);
};