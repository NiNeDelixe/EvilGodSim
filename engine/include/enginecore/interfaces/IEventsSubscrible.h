#pragma once
#ifndef INTERFACES_IEVENTSSUBSCRIBLE_H_
#define INTERFACES_IEVENTSSUBSCRIBLE_H_

#include "enginecore/core/EngineCoreApplication.h"

class IEventsSubscrible
{
public:
	IEventsSubscrible() = default;
	virtual ~IEventsSubscrible() = default;

	template<typename SENDER, typename RESIVER>
	void connect(const SENDER* sender, const delegates::runnable signal, const RESIVER* resiver, const delegates::runnable slot)
	{
		//EngiApp->events().addListener<SENDER>(std::bind(&slot, resiver, std::placeholders::_1))
	}

private:

};


#endif // !INTERFACES_IEVENTSSUBSCRIBLE_H_
