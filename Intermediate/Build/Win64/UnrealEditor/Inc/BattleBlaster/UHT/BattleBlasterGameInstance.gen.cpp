// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BattleBlaster/BattleBlasterGameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBattleBlasterGameInstance() {}

// ********** Begin Cross Module References ********************************************************
BATTLEBLASTER_API UClass* Z_Construct_UClass_UBattleBlasterGameInstance();
BATTLEBLASTER_API UClass* Z_Construct_UClass_UBattleBlasterGameInstance_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UGameInstance();
UPackage* Z_Construct_UPackage__Script_BattleBlaster();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBattleBlasterGameInstance ***********************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBattleBlasterGameInstance;
UClass* UBattleBlasterGameInstance::GetPrivateStaticClass()
{
	using TClass = UBattleBlasterGameInstance;
	if (!Z_Registration_Info_UClass_UBattleBlasterGameInstance.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BattleBlasterGameInstance"),
			Z_Registration_Info_UClass_UBattleBlasterGameInstance.InnerSingleton,
			StaticRegisterNativesUBattleBlasterGameInstance,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UBattleBlasterGameInstance.InnerSingleton;
}
UClass* Z_Construct_UClass_UBattleBlasterGameInstance_NoRegister()
{
	return UBattleBlasterGameInstance::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBattleBlasterGameInstance_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "BattleBlasterGameInstance.h" },
		{ "ModuleRelativePath", "BattleBlasterGameInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastLevelIndex_MetaData[] = {
		{ "Category", "BattleBlasterGameInstance" },
		{ "ModuleRelativePath", "BattleBlasterGameInstance.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurrentLevelIndex_MetaData[] = {
		{ "Category", "BattleBlasterGameInstance" },
		{ "ModuleRelativePath", "BattleBlasterGameInstance.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UBattleBlasterGameInstance constinit property declarations ***************
	static const UECodeGen_Private::FIntPropertyParams NewProp_LastLevelIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CurrentLevelIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UBattleBlasterGameInstance constinit property declarations *****************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBattleBlasterGameInstance>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBattleBlasterGameInstance_Statics

// ********** Begin Class UBattleBlasterGameInstance Property Definitions **************************
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBattleBlasterGameInstance_Statics::NewProp_LastLevelIndex = { "LastLevelIndex", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBattleBlasterGameInstance, LastLevelIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastLevelIndex_MetaData), NewProp_LastLevelIndex_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UBattleBlasterGameInstance_Statics::NewProp_CurrentLevelIndex = { "CurrentLevelIndex", nullptr, (EPropertyFlags)0x0010000000020001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UBattleBlasterGameInstance, CurrentLevelIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurrentLevelIndex_MetaData), NewProp_CurrentLevelIndex_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UBattleBlasterGameInstance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBattleBlasterGameInstance_Statics::NewProp_LastLevelIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UBattleBlasterGameInstance_Statics::NewProp_CurrentLevelIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBattleBlasterGameInstance_Statics::PropPointers) < 2048);
// ********** End Class UBattleBlasterGameInstance Property Definitions ****************************
UObject* (*const Z_Construct_UClass_UBattleBlasterGameInstance_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstance,
	(UObject* (*)())Z_Construct_UPackage__Script_BattleBlaster,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBattleBlasterGameInstance_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBattleBlasterGameInstance_Statics::ClassParams = {
	&UBattleBlasterGameInstance::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UBattleBlasterGameInstance_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UBattleBlasterGameInstance_Statics::PropPointers),
	0,
	0x009000A8u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBattleBlasterGameInstance_Statics::Class_MetaDataParams), Z_Construct_UClass_UBattleBlasterGameInstance_Statics::Class_MetaDataParams)
};
void UBattleBlasterGameInstance::StaticRegisterNativesUBattleBlasterGameInstance()
{
}
UClass* Z_Construct_UClass_UBattleBlasterGameInstance()
{
	if (!Z_Registration_Info_UClass_UBattleBlasterGameInstance.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBattleBlasterGameInstance.OuterSingleton, Z_Construct_UClass_UBattleBlasterGameInstance_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBattleBlasterGameInstance.OuterSingleton;
}
UBattleBlasterGameInstance::UBattleBlasterGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBattleBlasterGameInstance);
UBattleBlasterGameInstance::~UBattleBlasterGameInstance() {}
// ********** End Class UBattleBlasterGameInstance *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Projects_BattleBlaster_Source_BattleBlaster_BattleBlasterGameInstance_h__Script_BattleBlaster_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBattleBlasterGameInstance, UBattleBlasterGameInstance::StaticClass, TEXT("UBattleBlasterGameInstance"), &Z_Registration_Info_UClass_UBattleBlasterGameInstance, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBattleBlasterGameInstance), 1396284019U) },
	};
}; // Z_CompiledInDeferFile_FID_Projects_BattleBlaster_Source_BattleBlaster_BattleBlasterGameInstance_h__Script_BattleBlaster_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Projects_BattleBlaster_Source_BattleBlaster_BattleBlasterGameInstance_h__Script_BattleBlaster_3885682097{
	TEXT("/Script/BattleBlaster"),
	Z_CompiledInDeferFile_FID_Projects_BattleBlaster_Source_BattleBlaster_BattleBlasterGameInstance_h__Script_BattleBlaster_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Projects_BattleBlaster_Source_BattleBlaster_BattleBlasterGameInstance_h__Script_BattleBlaster_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
