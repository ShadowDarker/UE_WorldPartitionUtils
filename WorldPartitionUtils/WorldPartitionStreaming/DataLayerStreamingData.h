#pragma once

#include "DataLayerStreamingData.generated.h"

enum class EDataLayerRuntimeState : uint8;

/**
 * @struct FDataLayerStreamingData
 * @brief Container of data layer assets and the target runtime state with recursive option.
 */
USTRUCT(BlueprintType)
struct FDataLayerStreamingData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Setup")
	TArray<UDataLayerAsset*> DataLayers;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Setup")
	EDataLayerRuntimeState DataLayerRuntimeState;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Setup")
	bool bRecursive = false;
};