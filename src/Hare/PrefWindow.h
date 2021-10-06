/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef PREF_WINDOW_H
#define PREF_WINDOW_H

#include <Button.h>
#include <Box.h>
#include <StringView.h>
#include <TextControl.h>
#include <Window.h>

class PrefWindow : public BWindow {
public:
	PrefWindow();
	~PrefWindow();
	virtual void MessageReceived(BMessage* message);
private:
	void InitWindow();
	BBox* fileNamePatternBox;
	BStringView* artistStringView;
	BStringView* albumStringView;
	BStringView* titleStringView;
	BStringView* yearStringView;
	BStringView* commentStringView;
	BStringView* trackStringView;
	BStringView* genreStringView;
	BTextControl* fileNamePatternTextControl;
	BButton* applyButton;
	BButton* revertButton;
	BButton* encoderPatternButton;
};

#endif // PREF_WINDOW_H
