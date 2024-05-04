// Copyright Epic Games, Inc. All Rights Reserved.

#include "bbun.h"
#include "bbunStyle.h"
#include "bbunCommands.h"
#include "BlueprintActionDatabase.h"
#include "K2Node_LatentAbilityCall.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "ClassGenerator/ASClass.h"

static const FName bbunTabName("bbun");

#define LOCTEXT_NAMESPACE "FbbunModule"

void FbbunModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FbbunStyle::Initialize();
	FbbunStyle::ReloadTextures();

	FbbunCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FbbunCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FbbunModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FbbunModule::RegisterMenus));
}

void FbbunModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FbbunStyle::Shutdown();

	FbbunCommands::Unregister();
}

void FbbunModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FbbunModule::PluginButtonClicked()")),
							FText::FromString(TEXT("bbun.cpp"))
					   );


	for (TObjectIterator<UASClass> ClassIt; ClassIt; ++ClassIt)
	{
		UClass* const Class = (*ClassIt);

		FString NameStr = Class->GetName();

		if (NameStr.StartsWith("Module_")&& NameStr.EndsWith("Statics"))
		{
			FBlueprintActionDatabase::Get().RefreshClassActions(Class);
		}
	}

	//FBlueprintActionDatabase::Get().RefreshClassActions(UK2Node_LatentGameplayTaskCall::StaticClass());


	

	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FbbunModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FbbunCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FbbunCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FbbunModule, bbun)