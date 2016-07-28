/*
 *  jssdk-v8.h
 *  Created on: Jun 4, 2016
 *
 *  Copyright (c) 2016 by Leo Hoo
 *  lion@9465.net
 */

#ifndef _jssdk_v8_h__
#define _jssdk_v8_h__

#include "jssdk.h"
#include <v8/include/v8.h>

namespace js
{

#define _api v8_api

class Api_v8;
class v8_Runtime;

class Locker
{
public:
	Locker(Runtime* rt) : m_rt(rt)
	{
		rt->Locker_enter(*this);
	}

	~Locker()
	{
		m_rt->Locker_leave(*this);
	}

private:
	Runtime* m_rt;
	char m_locker[sizeof(v8::Locker)];

	friend class v8_Runtime;
};

class Unlocker
{
public:
	Unlocker(Runtime* rt) : m_rt(rt)
	{
		rt->Unlocker_enter(*this);
	}

	~Unlocker()
	{
		m_rt->Unlocker_leave(*this);
	}

private:
	Runtime* m_rt;
	char m_unlocker[sizeof(v8::Unlocker)];

	friend class v8_Runtime;
};

class Scope
{
public:
	Scope(Runtime* rt) : m_rt(rt)
	{
		rt->Scope_enter(*this);
	}

	~Scope()
	{
		m_rt->Scope_leave(*this);
	}

private:
	Runtime* m_rt;
	char m_locker[sizeof(v8::Locker)];
	char m_handle_scope[sizeof(v8::HandleScope)];

	friend class v8_Runtime;
};

typedef v8::Local<v8::Value> js_value;

}

#include "jssdk-pub.h"

#endif // _jssdk_v8_h__