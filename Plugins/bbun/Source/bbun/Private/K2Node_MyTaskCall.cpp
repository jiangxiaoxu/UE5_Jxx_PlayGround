// Fill out your copyright notice in the Description page of Project Settings.


#include "K2Node_MyTaskCall.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintFunctionNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "Kismet2/CompilerResultsLog.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Tasks/AbilityTask.h"

#define LOCTEXT_NAMESPACE "K2Node"
static FName FK2Node_LatentAbilityCallHelper_RequiresConnection(TEXT("RequiresConnection"));

UK2Node_MyTaskCall::UK2Node_MyTaskCall(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	if (HasAnyFlags(RF_ClassDefaultObject) == true)
	{
		UK2Node_LatentGameplayTaskCall::RegisterSpecializedTaskNodeClass(GetClass());
	}
}

bool UK2Node_MyTaskCall::IsHandling(TSubclassOf<UGameplayTask> TaskClass) const
{
	UClass* Class = TaskClass.GetGCPtr();

		FString NameStr = Class->GetName();

		if (NameStr.StartsWith("Module_") && NameStr.EndsWith("Statics"))
		{
			return true;
		}

	return false;
}

bool UK2Node_MyTaskCall::IsCompatibleWithGraph(UEdGraph const* TargetGraph) const
{
	return false;
}

void UK2Node_MyTaskCall::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	struct GetMenuActions_Utils
	{
		static void SetNodeFunc(UEdGraphNode* NewNode, bool /*bIsTemplateNode*/, TWeakObjectPtr<UFunction> FunctionPtr)
		{
			UK2Node_MyTaskCall* AsyncTaskNode = CastChecked<UK2Node_MyTaskCall>(NewNode);
			if (FunctionPtr.IsValid())
			{
				UFunction* Func = FunctionPtr.Get();
				FObjectProperty* ReturnProp = CastFieldChecked<FObjectProperty>(Func->GetReturnProperty());

				AsyncTaskNode->ProxyFactoryFunctionName = Func->GetFName();
				AsyncTaskNode->ProxyFactoryClass = Func->GetOuterUClass();
				AsyncTaskNode->ProxyClass = ReturnProp->PropertyClass;
			}
		}
	};

	UClass* NodeClass = GetClass();
	ActionRegistrar.RegisterClassFactoryActions<UAbilityTask>(FBlueprintActionDatabaseRegistrar::FMakeFuncSpawnerDelegate::CreateLambda([NodeClass](const UFunction* FactoryFunc)->UBlueprintNodeSpawner*
		{
			UBlueprintNodeSpawner* NodeSpawner = UBlueprintFunctionNodeSpawner::Create(FactoryFunc);
			check(NodeSpawner != nullptr);
			NodeSpawner->NodeClass = NodeClass;

			TWeakObjectPtr<UFunction> FunctionPtr = MakeWeakObjectPtr(const_cast<UFunction*>(FactoryFunc));
			NodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(GetMenuActions_Utils::SetNodeFunc, FunctionPtr);

			return NodeSpawner;
		}));
}

void UK2Node_MyTaskCall::ValidateNodeDuringCompilation(class FCompilerResultsLog& MessageLog) const
{
	Super::ValidateNodeDuringCompilation(MessageLog);

	UFunction* DelegateSignatureFunction = NULL;
	for (TFieldIterator<FProperty> PropertyIt(ProxyClass); PropertyIt; ++PropertyIt)
	{
		if (FMulticastDelegateProperty* Property = CastField<FMulticastDelegateProperty>(*PropertyIt))
		{
			if (Property->GetBoolMetaData(FK2Node_LatentAbilityCallHelper_RequiresConnection))
			{
				if (UEdGraphPin* DelegateExecPin = FindPin(Property->GetFName()))
				{
					if (DelegateExecPin->LinkedTo.Num() < 1)
					{
						const FText MessageText = FText::Format(LOCTEXT("NoConnectionToRequiredExecPin", "@@ - Unhandled event.  You need something connected to the '{0}' pin"), FText::FromName(Property->GetFName()));
						MessageLog.Warning(*MessageText.ToString(), this);
					}
				}
			}
		}
	}
}


#undef LOCTEXT_NAMESPACE