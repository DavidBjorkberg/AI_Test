// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"

#include "TestLuaState.generated.h"

/**
 * 
 */
UCLASS()
class AITEST_API UTestLuaState : public ULuaState
{
	GENERATED_BODY()
	UTestLuaState();
protected:
	virtual void LuaStateInit() override;

	// __index(object, key) -> returning 1 value
	LUACFUNCTION(UTestLuaState, MetaMethodIndex, 1, 2);

	// __newindex(object, key, value)
	LUACFUNCTION(UTestLuaState, MetaMethodNewIndex, 0, 3);

	// __eq(object1, object2) -> returning bool
	LUACFUNCTION(UTestLuaState, MetaMethodEq, 1, 2);

	// __string(object) -> returning string
	LUACFUNCTION(UTestLuaState, MetaMethodToString, 1, 1);
};
