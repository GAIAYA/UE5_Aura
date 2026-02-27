// Copyright Gaia


#include "UI/Widgets/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* inWidgetController)
{
	WidgetController = inWidgetController;
	WidgetControllerSet();
}
