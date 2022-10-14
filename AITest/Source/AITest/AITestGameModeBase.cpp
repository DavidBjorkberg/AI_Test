// Copyright Epic Games, Inc. All Rights Reserved.


#include "AITestGameModeBase.h"

#include "LuaGlobalNameComponent.h"
#include "TestLuaState.h"

void AAITestGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	AActor* spawnedActor = GetWorld()->SpawnActor(AActor::StaticClass());
	const FTransform& transform = spawnedActor->GetTransform();
	spawnedActor->AddComponentByClass(UStaticMeshComponent::StaticClass(), false, transform,false);
	ULuaGlobalNameComponent* comp = Cast<ULuaGlobalNameComponent>(spawnedActor->AddComponentByClass(
		ULuaGlobalNameComponent::StaticClass(), false,
		transform
		, true));
	comp->LuaState = UTestLuaState::StaticClass();
	comp->LuaGlobalName = "Pontus";
	spawnedActor->FinishAddComponent(comp, false, transform);
}
