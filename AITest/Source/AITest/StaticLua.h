// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "StaticLua.generated.h"

/**
 * 
 */
UCLASS()
class AITEST_API AStaticLua : public AActor
{
	GENERATED_BODY()
public:
	AStaticLua();
	UFUNCTION(BlueprintCallable)
	UObject* PrintStuff();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ULuaState> mLuaState;
};
