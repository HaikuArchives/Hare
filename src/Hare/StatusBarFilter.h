/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __STATUS_BAR_FILTER_H__
#define __STATUS_BAR_FILTER_H__

#include <MessageFilter.h>

class BHandler;
class BMessage;

class StatusBarFilter : public BMessageFilter {
public:
	StatusBarFilter();
	virtual filter_result Filter(BMessage* message, BHandler** target);
};

#endif
