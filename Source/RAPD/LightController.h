// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Misc/DateTime.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFilemanager.h"
#include "FoveHMD.h"
#include "TimerManager.h"
#include "Engine/StaticMeshActor.h"
#include "LightController.generated.h"

UCLASS()
class RAPD_API ALightController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightController();
	UPROPERTY(EditAnywhere, Category = "Materials")
	TArray<UMaterial*> Left_and_right;

	UPROPERTY(BlueprintReadWrite, Category = "Materials")
	TArray<UMaterialInstanceDynamic*> D_left_and_right;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterial* Dark_Material;

	UPROPERTY(EditAnywhere, Category = "Protocol Properties")
	int32 repititions;

	UPROPERTY(EditAnywhere, Category = "Protocol Properties")
	float initial_light_intensity;

	UPROPERTY(EditAnywhere, Category = "Protocol Properties")
	float light_duration;
	
	UPROPERTY(EditAnywhere, Category = "Protocol Properties")
	float dark_duration;
		
	UPROPERTY(EditAnywhere, Category = "Protocol Properties") 
	float dropoff;

	TArray<FString> CSV_file = {"TimeStamp,Intensity_Left,Pupil_Diameter_Left,Intensity_Right,Pupil_Diameter_Right"};
	FString SavingLocation = "C:\\Users\\znasi\\Documents\\Unreal Projects\\RAPD\\Saved\\Processed_Data";

	TArray<float> current_intensity = {0, 0};
	bool eye_tracking_ready = false;

	FFoveHMD* hmd;
	
	UPROPERTY(EditAnywhere, Category = "Subject_ID")
	FString ID;
	FTimerHandle LightTimerHandle, DarkTimerHandle;
	float Elapsed_time = 0.0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Function")
		void IncreaseLuminance(TArray<AStaticMeshActor*> lights);

	UFUNCTION(BlueprintCallable, Category = "Function")
		void Darkness(TArray<AStaticMeshActor*> lights);
	
	UFUNCTION(BlueprintCallable, Category = "Function")
		void TestProtocol(TArray<AStaticMeshActor*> lights);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Load"))
		static bool LoadTextFromFile(FString FileName, TArray<FString>& TextArray, FString& TextString);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
		static bool SaveArrayText(FString SaveDirectory, FString FileName, TArray<FString> SaveText, bool AllowOverwriting);

	UFUNCTION(BlueprintCallable, Category = "Custom", meta = (Keywords = "Save"))
		static bool DeleteTextFile(FString SaveDirectory, FString FileName);
};
