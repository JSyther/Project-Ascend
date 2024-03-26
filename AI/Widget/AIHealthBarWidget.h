// @2023 All rights reversed by Reverse-Alpha Studios

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AIHealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class ASCEND_API UAIHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetBarValuePercent(float const Value);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HealthValue = nullptr;
};
