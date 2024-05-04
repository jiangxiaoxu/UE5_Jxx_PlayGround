// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_LatentGameplayTaskCall.h"
#include "K2Node_MyTaskCall.generated.h"

/**
 * 
 */

class FBlueprintActionDatabaseRegistrar;

UCLASS()
class BBUN_API UK2Node_MyTaskCall : public UK2Node_LatentGameplayTaskCall
{
	GENERATED_BODY()


public:
	UK2Node_MyTaskCall(const FObjectInitializer& ObjectInitializer);

	// UEdGraphNode interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	virtual bool IsCompatibleWithGraph(UEdGraph const* TargetGraph) const override;
	virtual void ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const override;
	// End of UEdGraphNode interface

protected:
	virtual bool IsHandling(TSubclassOf<UGameplayTask> TaskClass) const override;
	
};
