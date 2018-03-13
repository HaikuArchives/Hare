#include "FileNamePatternView.h"

#include <Button.h>
#include <Debug.h>
#include <FindDirectory.h>
#include <LayoutBuilder.h>
#include <Message.h>
#include <Messenger.h>
#include <Path.h>
#include <Rect.h>
#include <String.h>
#include <StringView.h>
#include <TextControl.h>

#include "AEEncoder.h"

#include "AppDefs.h"
#include "CommandConstants.h"
#include "GUIStrings.h"
#include "Settings.h"

FileNamePatternView::FileNamePatternView()
	:
	BBox("fileNamePatternBox")
{
	PRINT(("FileNamePatternView::FileNamePatternView(BRect)\n"));
}

FileNamePatternView::~FileNamePatternView()
{
	PRINT(("FileNamePatternView::~FileNamePatternView()\n"));
}

void
FileNamePatternView::InitView()
{
	PRINT(("FileNamePatternView::InitView()\n"));

	SetLabel(FILE_NAME_PATTERN_BOX_LABEL);

	artistStringView = new BStringView("artist", ARTIST_LABEL);

	yearStringView = new BStringView("year", YEAR_LABEL);

	commentStringView = new BStringView("comment", COMMENT_LABEL);

	albumStringView = new BStringView("album", ALBUM_LABEL);

	trackStringView = new BStringView("track", TRACK_LABEL);

	titleStringView = new BStringView("title", TITLE_LABEL);

	genreStringView = new BStringView("genre", GENRE_LABEL);

	AEEncoder* encoder = settings->Encoder();
	BString patternStr;
	if (encoder) {
		patternStr = encoder->GetPattern();
	}
	
	BPath defaultPath;
	find_directory(B_USER_DIRECTORY, &defaultPath);
	
	filePathTextControl = new BTextControl("filePathTextControl",
													"File Path:", defaultPath.Path(), NULL);
	namePatternTextControl = new BTextControl("namePatternTextControl",
													"File Pattern:", patternStr.String(), NULL);

	applyButton = new BButton("applyButton", APPLY_BTN,
							  new BMessage(FILE_NAME_PATTERN_CHANGED));

	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_BIG_INSETS, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)
		.Add(artistStringView)
		.Add(albumStringView)
		.Add(titleStringView)
		.Add(yearStringView)
		.Add(trackStringView)
		.Add(genreStringView)
		.Add(commentStringView)
		.Add(filePathTextControl)
		.Add(namePatternTextControl)
		.Add(applyButton)
	.End();
}

void
FileNamePatternView::MakeFocus(bool focused)
{
	PRINT(("FileNamePatternView::MakeFocused(bool)\n"));

	filePathTextControl->MakeFocus(focused);
}

void
FileNamePatternView::SetEnabled(bool value)
{
	PRINT(("FileNamePatternView::SetEnabled(bool)\n"));

	filePathTextControl->SetEnabled(value);
	namePatternTextControl->SetEnabled(value);
	applyButton->SetEnabled(value);
}

void
FileNamePatternView::AttachedToWindow()
{
	PRINT(("FileNamePatternView::AttachedToWindow()\n"));

	InitView();

	filePathTextControl->SetTarget(this);
	namePatternTextControl->SetTarget(this);
	applyButton->SetTarget(this);
}

void
FileNamePatternView::MessageReceived(BMessage* message)
{
	//PRINT(("FileNamePatternView::MessageReceived(BMessage*)\n"));

	BMessenger parentMessenger(Parent());

	switch (message->what) {
		case FILE_NAME_PATTERN_CHANGED: {
				AEEncoder* encoder = settings->Encoder();
				if (encoder) {
					encoder->SetFilePath(filePathTextControl->Text());
					encoder->SetPattern(namePatternTextControl->Text());
					parentMessenger.SendMessage(message);
				}
			}
			break;
		case ENCODER_CHANGED: {
				AEEncoder* encoder = settings->Encoder();
				if (encoder) {
					filePathTextControl->SetText(encoder->GetFilePath());
					namePatternTextControl->SetText(encoder->GetPattern());
					BMessage msg(FILE_NAME_PATTERN_CHANGED);
					parentMessenger.SendMessage(&msg);
				}
			}
			break;
		default:
			BBox::MessageReceived(message);
	}
}
