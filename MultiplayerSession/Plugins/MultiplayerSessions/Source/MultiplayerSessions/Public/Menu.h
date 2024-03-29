// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "Menu.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSESSIONS_API UMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void MenuSetup(int32 NumberOfPublicConnections = 4,
				   FString TypeOfMatch = FString(TEXT("FreeForAll")),
				   FString LobbyPath = FString(TEXT("/Game/ThirdPerson/Maps/Lobby")));

protected:

	// Function called from the parent class
	virtual bool Initialize() override;
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	//
	// Callbacks for the custom delegates on the MultiplayerSessionsSubsystem
	//
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);
	void OnFindSessions(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);
	void OnJoinSession(EOnJoinSessionCompleteResult::Type Result);
	UFUNCTION()
	void OnStartSession(bool bWasSuccessful);
	UFUNCTION()
	void OnDestroySession(bool bWasSuccessful);

private:

	UPROPERTY(meta = (BindWidget)) // It binds the variable to the widget. It MUST have the same keys in Backend and Frontend
	class UButton* HostButton; // Doing forward declaration here allows me not to declare it in next variables of the same type

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UFUNCTION()
	void HostButtonClicked();

	UFUNCTION()
	void JoinButtonClicked();

	UFUNCTION()
	void MenuTearDown();

	void SetButtonsEnableState(bool bState);

	// The subsystem designed to handle all the online session functionality
	class UMultiplayerSessionsSubsystem* MSSubsystem;

	int32 NumPublicConnections{4};
	FString MatchType{TEXT("FreeForAll")};
	FString PathToLobby{TEXT("")};
};
