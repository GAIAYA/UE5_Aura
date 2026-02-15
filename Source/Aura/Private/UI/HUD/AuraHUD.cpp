// Copyright Gaia


#include "UI/HUD/AuraHUD.h"
#include "UI/Widgets/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& params)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(params);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* pc, APlayerState* ps, UAbilitySystemComponent* asc, UAttributeSet* as)
{
	checkf(OverlayWidgetClass, TEXT("Error: OverlayWidgetClass Not Init!"));
	checkf(OverlayWidgetControllerClass, TEXT("Error: OverlayWidgetControllerClass Not Init!"));

	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(widget);
	const FWidgetControllerParams params(pc, ps, asc, as);
	UOverlayWidgetController* widgetController = GetOverlayWidgetController(params);
	OverlayWidget->SetWidgetController(widgetController);
	widgetController->BroadcastInitialValues();

	widget->AddToViewport();
}

