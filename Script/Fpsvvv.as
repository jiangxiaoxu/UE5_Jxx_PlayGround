// Copyright Epic Games, Inc. All Rights Reserved.

event void FExampleDelegate(UObject Object, float Value);

class UAbilityTask_FX : UAngelscriptAbilityTask
{
	UPROPERTY()
	FExampleDelegate OnFuck;

	UPROPERTY()
	FExampleDelegate OnFuck_FInished;

	UPROPERTY()
	float CachedTimeBetweenActions;

	UPROPERTY()
	int32 TotalActionCount;

	UPROPERTY()
	int32 CurrentCount = 0;

	UPROPERTY()
	FTimerHandle Tiemrhandle;

	UFUNCTION(BlueprintOverride)
	void Activate()
	{
		Tiemrhandle = System::SetTimer(this, n"OnTicked", CachedTimeBetweenActions, true);
	}

	UFUNCTION()
	void OnTicked()
	{

		CurrentCount++;

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnFuck.Broadcast(this, CurrentCount);
		}
		if (ShouldBroadcastAbilityTaskDelegates())

			if (CurrentCount >= TotalActionCount)
			{
				System::InvalidateTimerHandle(Tiemrhandle);

				if (ShouldBroadcastAbilityTaskDelegates())
				{
					OnFuck_FInished.Broadcast(this, CurrentCount);
				}

				EndTask();
			}
	}
}

UFUNCTION(BlueprintCallable, Category = "Aasd|asks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "True"))
UAbilityTask_FX RepeatFuck(UGameplayAbility OwningAbility, float TimeBetweenActions, int32 TotalActionCount)
{
	UAbilityTask_FX myObj = Cast<UAbilityTask_FX>(AngelscriptAbilityTask::CreateAbilityTask(UAbilityTask_FX::StaticClass(), OwningAbility));

	myObj.TotalActionCount = 5;
	myObj.CachedTimeBetweenActions = 1.5;

	return myObj;
}

UFUNCTION()
void MyTestFunc()
{
	UFlowNode a;
#if EDITOR
#endif
}

FFlowPin MakeFlowPin(FName PinName, FString PinFriendlyName, FString PinToolTip = "")
{
	FFlowPin a1;
	a1.PinName = PinName;
	a1.PinFriendlyName = Text::Conv_StringToText(PinFriendlyName);
	a1.PinToolTip = PinToolTip;

	return a1;
}

UCLASS()
class UASFlowNVVVNode : UFlowNode
{
	default InputPins.Add(MakeFlowPin(n"In_x", "In_x"));

	UFUNCTION(BlueprintOverride)
	void OnActivate()
	{
		LogError("fffffffffff");
	}

	UFUNCTION(BlueprintOverride)
	void ExecuteInput(FName PinName)
	{
		TriggerFirstOutput(true);
	}
}