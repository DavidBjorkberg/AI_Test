// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticLua.h"

#include "LuaBlueprintFunctionLibrary.h"

AStaticLua::AStaticLua()
{
}

UObject* AStaticLua::PrintStuff()
{
	// FLuaValue test = ULuaBlueprintFunctionLibrary::LuaRunFile(GetWorld(), mLuaState, "Hello.lua", false);
	FLuaValue test = ULuaBlueprintFunctionLibrary::LuaRunString(GetWorld(),mLuaState,"return GetWorld()");
	// FLuaValue test = ULuaBlueprintFunctionLibrary::LuaRunString(GetWorld(),mLuaState,"Pontus.K2_AddActorLocalRotation({Yaw=10, Pitch=0, Roll=0})");
	return ULuaBlueprintFunctionLibrary::Conv_LuaValueToObject(test);	
}
