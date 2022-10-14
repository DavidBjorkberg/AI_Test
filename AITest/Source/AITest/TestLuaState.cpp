// Fill out your copyright notice in the Description page of Project Settings.


#include "TestLuaState.h"

#include "LuaBlueprintFunctionLibrary.h"

UTestLuaState::UTestLuaState()
{
	// allow to call native UFunctions with implicit FLuaValue conversions
	bRawLuaFunctionCall = true;
}

void UTestLuaState::LuaStateInit()
{
	UserDataMetaTable = CreateLuaTable();
	UserDataMetaTable.SetField("__index", UTestLuaState::MetaMethodIndex_C);
	UserDataMetaTable.SetField("__newindex", UTestLuaState::MetaMethodNewIndex_C);
	UserDataMetaTable.SetField("__eq", UTestLuaState::MetaMethodEq_C);
	UserDataMetaTable.SetField("__tostring", UTestLuaState::MetaMethodToString_C);
}

TArray<FLuaValue> UTestLuaState::MetaMethodIndex(TArray<FLuaValue> LuaArgs)
{
	TArray<FLuaValue> ReturnValues;

	UObject* Object = LuaArgs[0].Object;
	FString Key = LuaArgs[1].ToString();

	// skip nullptr and classes
	if (!Object || Object->IsA<UClass>())
	{
		return ReturnValues;
	}

	ELuaReflectionType ReflectionType = ELuaReflectionType::Unknown;
	ULuaBlueprintFunctionLibrary::GetLuaReflectionType(Object, Key, ReflectionType);

	if (ReflectionType == ELuaReflectionType::Property)
	{
		ReturnValues.Add(GetLuaValueFromProperty(Object, Key));
	}
	else if (ReflectionType == ELuaReflectionType::Function)
	{
		ReturnValues.Add(FLuaValue::FunctionOfObject(Object, FName(Key)));
	}

	return ReturnValues;
}

TArray<FLuaValue> UTestLuaState::MetaMethodNewIndex(TArray<FLuaValue> LuaArgs)
{
	TArray<FLuaValue> ReturnValues;

	UObject* Object = LuaArgs[0].Object;
	FString Key = LuaArgs[1].ToString();
	FLuaValue Value = LuaArgs[2];

	// skip nullptr and classes
	if (!Object || Object->IsA<UClass>())
	{
		return ReturnValues;
	}

	ELuaReflectionType ReflectionType = ELuaReflectionType::Unknown;
	ULuaBlueprintFunctionLibrary::GetLuaReflectionType(Object, Key, ReflectionType);

	if (ReflectionType == ELuaReflectionType::Property)
	{
		SetPropertyFromLuaValue(Object, Key, Value);
	}

	return ReturnValues;
}

TArray<FLuaValue> UTestLuaState::MetaMethodEq(TArray<FLuaValue> LuaArgs)
{
	TArray<FLuaValue> ReturnValues;

	UObject* Object = LuaArgs[0].Object;
	UObject* OtherObject = LuaArgs[1].Object;

	if (!Object || !OtherObject)
	{
		ReturnValues.Add(FLuaValue(false));
	}
	else
	{
		ReturnValues.Add(FLuaValue(Object == OtherObject));
	}

	return ReturnValues;
}

TArray<FLuaValue> UTestLuaState::MetaMethodToString(TArray<FLuaValue> LuaArgs)
{
	TArray<FLuaValue> ReturnValues;

	UObject* Object = LuaArgs[0].Object;

	// skip nullptr and classes
	if (!Object || Object->IsA<UClass>())
	{
		return ReturnValues;
	}

	ReturnValues.Add(Object->GetFullName());

	return ReturnValues;
}