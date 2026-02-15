// Copyright Gaia


#include "UI/WidgetController/AuraWidgetController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& params)
{
	PlayerController = params.PlayerController;
	PlayerState = params.PlayerState;
	AbilitySystemComponent = params.AbilitySystemComponent;
	AttributeSet = params.AttributeSet;
}
