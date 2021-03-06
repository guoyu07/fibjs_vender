/*
 *  fbEvent.cpp
 *  Created on: Mar 19, 2012
 *
 *  Copyright (c) 2012 by Leo Hoo
 *  lion@9465.net
 */

#include "service.h"

namespace exlib
{
void Event::wait()
{
	m_lock.lock();
	if (!m_set)
	{
		Task_base* current = Thread_base::current();
		assert(current != 0);

		m_blocks.putTail(current);
		current->suspend(m_lock);
	}
	else
		m_lock.unlock();
}

void Event::pulse()
{
	List<Task_base> blocks;

	m_lock.lock();
	m_blocks.getList(blocks);
	m_lock.unlock();

	Task_base* fb;
	while ((fb = blocks.getHead()) != 0)
		fb->resume();
}

void Event::set()
{
	List<Task_base> blocks;

	m_lock.lock();
	m_set = true;
	m_blocks.getList(blocks);
	m_lock.unlock();

	Task_base* fb;
	while ((fb = blocks.getHead()) != 0)
		fb->resume();
}

void Event::reset()
{
	m_lock.lock();
	m_set = false;
	m_lock.unlock();
}

bool Event::isSet()
{
	m_lock.lock();
	bool r = m_set;
	m_lock.unlock();

	return r;
}

}
