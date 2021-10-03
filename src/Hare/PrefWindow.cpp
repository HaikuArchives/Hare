/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#include "PrefWindow.h"

#include <Application.h>
#include <Box.h>
#include <Button.h>
#include <LayoutBuilder.h>
#include <StringView.h>
#include <TextControl.h>

#include "AEEncoder.h"
#include "AppDefs.h"
#include "CommandConstants.h"
#include "GUIStrings.h"
#include "Settings.h"

PrefWindow::PrefWindow()
	:
	BWindow(BRect(), PREFS, B_FLOATING_WINDOW_LOOK, B_MODAL_APP_WINDOW_FEEL,
				B_ASYNCHRONOUS_CONTROLS | B_AUTO_UPDATE_SIZE_LIMITS |
				B_NOT_MINIMIZABLE | B_NOT_ZOOMABLE)
{
	InitWindow();
	CenterOnScreen();	
}

PrefWindow::~PrefWindow()
{
}

void
PrefWindow::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case SAVE_PREFS: {
				AEEncoder* encoder = settings->Encoder();
				if (encoder) {
					encoder->SetPattern(fileNamePatternTextControl->Text());
					settings->SetPathPattern(fileNamePatternTextControl->Text());
				}
				be_app_messenger.SendMessage(new BMessage(FILE_NAME_PATTERN_CHANGED));
			}
			break;
		case REVERT_PREFS: {
				fileNamePatternTextControl->SetText(settings->PathPattern());
			}
			break;
		case ENCODER_PATTERN_PREFS: {
			AEEncoder* encoder = settings->Encoder();
			if (encoder) {
				fileNamePatternTextControl->SetText(encoder->GetDefaultPattern());		
			}
			}
			break;
		default:
			BWindow::MessageReceived(message);
	}
}

void
PrefWindow::InitWindow()
{
	BBox* fileNamePatternBox = new BBox("fileNamePatternBox");
	fileNamePatternBox->SetLabel(FILE_NAME_PATTERN_BOX_LABEL);
	
	artistStringView = new BStringView("artist", ARTIST_LABEL);
	yearStringView = new BStringView("year", YEAR_LABEL);
	commentStringView = new BStringView("comment", COMMENT_LABEL);
	albumStringView = new BStringView("album", ALBUM_LABEL);
	trackStringView = new BStringView("track", TRACK_LABEL);
	titleStringView = new BStringView("title", TITLE_LABEL);
	genreStringView = new BStringView("genre", GENRE_LABEL);

	const char* str = "";
	str = settings->PathPattern();
	fileNamePatternTextControl = new BTextControl("fileNamePatternTextControl",
													B_EMPTY_STRING, str, NULL);

	applyButton = new BButton("applyButton", APPLY_BTN,
							  new BMessage(SAVE_PREFS));
	revertButton = new BButton("revertButton", REVERT_BTN,
							  new BMessage(REVERT_PREFS));
	encoderPatternButton = new BButton("encoderPatternButton", ENCODER_PATTERN_BTN,
							  new BMessage(ENCODER_PATTERN_PREFS));
	
	BLayoutBuilder::Group<>(fileNamePatternBox, B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_BIG_INSETS, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)
		.AddGrid(1.0f, 0.0f)
			.Add(artistStringView, 0, 0)
			.Add(albumStringView, 1, 0)
			.Add(titleStringView, 2, 0)
			.Add(yearStringView, 0, 1)
			.Add(trackStringView, 1, 1)
			.Add(genreStringView, 2, 1)
			.Add(commentStringView, 0, 2)
		.End()
		.Add(fileNamePatternTextControl)
	.End();
	
	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)
		.Add(fileNamePatternBox, 0.0f)
		.AddGroup(B_HORIZONTAL)
			.Add(revertButton, 0.0f)
			.Add(encoderPatternButton, 0.0f)
			.Add(applyButton, 1.0f)
		.End()
	.End();				
}
