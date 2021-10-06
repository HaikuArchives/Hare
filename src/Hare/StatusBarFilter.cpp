/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#include "StatusBarFilter.h"

#include <Handler.h>
#include <Message.h>
#include <StatusBar.h>

#include "AEEncoder.h"

#include "Settings.h"

StatusBarFilter::StatusBarFilter()
	:
	BMessageFilter(B_PROGRAMMED_DELIVERY, B_LOCAL_SOURCE)
{
}

filter_result
StatusBarFilter::Filter(BMessage* message, BHandler** target)
{

	filter_result result = B_DISPATCH_MESSAGE;
	switch (message->what) {
		case B_UPDATE_STATUS_BAR:
			if (settings->IsEncoding()) {
				message->RemoveName("text");
				message->RemoveName("trailing_text");
			} else {
				result = B_SKIP_MESSAGE;
			}
			break;
		case B_RESET_STATUS_BAR: {
				result = B_SKIP_MESSAGE;
			}
			break;
		case FSS_SETMAX_STATUS_BAR: {
				float max;
				if (message->FindFloat("max", &max) == B_OK) {
					BStatusBar* statusBar = (BStatusBar*) * target;
					statusBar->SetMaxValue(max);
					result = B_SKIP_MESSAGE;
				}
			}
			break;
		default:
			result = BMessageFilter::Filter(message, target);
	}

	return result;
}
