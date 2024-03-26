// @2023 All rights reversed by Reverse-Alpha Studios


#include "AIHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UAIHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAIHealthBarWidget::SetBarValuePercent(float const Value)
{
	HealthValue->SetPercent(Value);
}
