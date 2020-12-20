/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, June 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "aws/dynamodb/model/UpdateReplicationGroupMemberAction.h"

#endif

#include "Model/ProvisionedThroughputOverride.h"
#include "Model/ReplicaGlobalSecondaryIndex.h"

#include "UpdateReplicationGroupMemberAction.generated.h"

USTRUCT(BlueprintType)
struct FUpdateReplicationGroupMemberAction {
GENERATED_BODY()

    /**
    *  <p>The Region where the replica exists.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamodb Client")
    FString regionName;

    /**
    *  <p>The AWS KMS customer master key (CMK) of the replica that should be used for AWS KMS encryption. To specify a CMK, use its key ID, Amazon Resource Name (ARN), alias name, or alias ARN. Note that you should only provide this parameter if the key is different from the default DynamoDB KMS master key alias/aws/dynamodb.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamodb Client")
    FString kMSMasterKeyId;

    /**
    *  <p>Replica-specific provisioned throughput. If not specified, uses the source table's provisioned throughput settings.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamodb Client")
    FProvisionedThroughputOverride provisionedThroughputOverride;

    /**
    *  <p>Replica-specific global secondary index settings.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamodb Client")
    TArray<FReplicaGlobalSecondaryIndex> globalSecondaryIndexes;

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE
public:
    Aws::DynamoDB::Model::UpdateReplicationGroupMemberAction toAWS() const {
        Aws::DynamoDB::Model::UpdateReplicationGroupMemberAction awsUpdateReplicationGroupMemberAction;

		if (!(this->regionName.IsEmpty())) {
            awsUpdateReplicationGroupMemberAction.SetRegionName(TCHAR_TO_UTF8(*this->regionName));
        }

		if (!(this->kMSMasterKeyId.IsEmpty())) {
            awsUpdateReplicationGroupMemberAction.SetKMSMasterKeyId(TCHAR_TO_UTF8(*this->kMSMasterKeyId));
        }

        if (!(this->provisionedThroughputOverride.IsEmpty())) {
            awsUpdateReplicationGroupMemberAction.SetProvisionedThroughputOverride(this->provisionedThroughputOverride.toAWS());
        }

        for (const FReplicaGlobalSecondaryIndex& elem : this->globalSecondaryIndexes) {
            awsUpdateReplicationGroupMemberAction.AddGlobalSecondaryIndexes(elem.toAWS());
        }

        return awsUpdateReplicationGroupMemberAction;
    }

    bool IsEmpty() const {
        return this->regionName.IsEmpty() && this->kMSMasterKeyId.IsEmpty() && this->provisionedThroughputOverride.IsEmpty() && this->globalSecondaryIndexes.Num() == 0;
    }
#endif
};
