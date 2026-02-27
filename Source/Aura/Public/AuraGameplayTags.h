// Copyright Gaia

#pragma once

#include "CoreMinimal.h"


/*
* 单例模式
* 有指针和非指针两种实现方式：
* 非指针方式更简单，不需要考虑内存管理问题且C++11保证线程安全。
* 如果是非指针类内静态成员，可能会存在静态初始化顺序问题，导致访问未初始化的对象。
* 指针方式需要手动管理内存，有地方逻辑可能跟实例析构有关联，不好管理析构，且可能存在线程安全问题。
*/
struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get()
	{
		static FAuraGameplayTags instance;
		return instance;
	}
	static void InitializeNativeGameplayTags();
private:
	FAuraGameplayTags() = default;
	FAuraGameplayTags(const FAuraGameplayTags&) = delete;
	FAuraGameplayTags& operator=(const FAuraGameplayTags&) = delete;

private:

};

