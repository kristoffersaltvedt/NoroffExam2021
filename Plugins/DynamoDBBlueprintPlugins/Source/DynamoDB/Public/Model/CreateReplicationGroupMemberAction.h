/* Copyright (C) Siqi.Wu - All Rights Reserved
* Written by Siqi.Wu<lion547016@gmail.com>, June 2020
*/

#pragma once

#include "CoreMinimal.h"

#if WITH_DYNAMODBCLIENTSDK && WITH_CORE

#include "aws/dynamodb/model/CreateReplicationGroupMemberAction.h"

#endif

#include "Model/ProvisionedThroughputOverride.h"
#include "Model/ReplicaGlobalSecondaryIndex.h"

#include "CreateReplicationGroupMemberAction.generated.h"

USTRUCT(BlueprintType)
struct FCreateReplicationGroupMemberAction {
GENERATED_BODY()

    /**
    *  <p>The Region where the new replica will be created.</p>
    **/
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamodb Client")
    FString regionName;

    /**
    *  <p>The AWS KMS customer master key (CMK) that should be used for AWS KMS encryption in the new replica. To specify a CMK, use its key ID, Amazon Resource Name (ARN), alias name, or alias ARN. Note that you should only provide this parameter if the key is different from the default DynamoDB KMS master key alias/aws/dynamodb.</p>
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
    Aws::DynamoDB::Model::CreateReplicationGroupMemberAction toAWS() const {
        Aws::DynamoDB::Model::CreateReplicationGroupMemberAction awsCreateReplicationGroupMemberAction;

		if (!(this->regionName.IsEmpty())) {
            awsCreateReplicationGroupMemberAction.SetRegionName(TCHAR_TO_UTF8(*this->regionName));
        }

		if (!(this->kMSMasterKeyId.IsEmpty())) {
            awsCreateReplicationGroupMemberAction.SetKMSMasterKeyId(TCHAR_TO_UTF8(*this->kMSMasterKeyId));
        }

        if (!(this->provisionedThroughputOverride.IsEmpty())) {
            awsCreateReplicationGroupMemberAction.SetProvisionedThroughputOverride(this->provisionedThroughputOverride.toAWS());
        }

        for (const FReplicaGlobalSecondaryIndex& elem : this->globalSecondaryIndexes) {
            awsCreateReplicationGroupMemberAction.AddGlobalSecondaryIndexes(elem.toAWS());
        }

        return awsCreateReplicationGroupMemberAction;
    }

    bool IsEmpty() const {
        return this->regionName.IsEmpty() && this->kMSMasterKeyId.IsEmpty() && this->provisionedThroughputOverride.IsEmpty() && this->globalSecondaryIndexes.Num() == 0;
    }
#endif
};
