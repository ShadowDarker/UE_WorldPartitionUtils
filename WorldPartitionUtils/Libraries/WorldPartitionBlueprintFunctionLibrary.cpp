#include "Libraries/WorldPartitionBlueprintFunctionLibrary.h"
#include "WorldPartitionStreaming/DataLayerStreamingData.h"
#include "WorldPartition/DataLayer/DataLayerAsset.h"
#include "WorldPartition/DataLayer/DataLayerManager.h"

bool UWorldPartitionBlueprintFunctionLibrary::HandleDataLayerStreamingOperations(UObject* WorldContextObject, TArray<FDataLayerStreamingData> DataLayerStreamingDataContainers)
{
	if (DataLayerStreamingDataContainers.IsEmpty())
	{
		return false;
	}

	UDataLayerManager* DataLayerManager = UDataLayerManager::GetDataLayerManager(WorldContextObject);

	if (DataLayerManager == nullptr)
	{
		return false;
	}
	
	for (FDataLayerStreamingData DataLayerStreamingData : DataLayerStreamingDataContainers)
	{
		for (UDataLayerAsset* DataLayerAsset : DataLayerStreamingData.DataLayers)
		{
			if (DataLayerAsset == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Tried to set state on null Datalayer reference"));
				continue;
			}
			
			const bool bSuccess = DataLayerManager->SetDataLayerInstanceRuntimeState(DataLayerManager->GetDataLayerInstance(DataLayerAsset), DataLayerStreamingData.DataLayerRuntimeState, DataLayerStreamingData.bRecursive);

			if (!bSuccess)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Failed to set runtime state %s in DataLayer: %s"), GetDataLayerRuntimeStateName(DataLayerStreamingData.DataLayerRuntimeState), *DataLayerAsset->GetName()));
				UE_LOG(LogTemp, Warning, TEXT("Failed to set runtime state %s in DataLayer: %s"), GetDataLayerRuntimeStateName(DataLayerStreamingData.DataLayerRuntimeState), *DataLayerAsset->GetName());
				
				return false;
			}
		}
	}

	return true;
}