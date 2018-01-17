#include "FileNamePatternView.h"

#include <Button.h>
#include <Debug.h>
#include <LayoutBuilder.h>
#include <Message.h>
#include <Messenger.h>
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

	int space = 6;

	font_height fh;
	GetFontHeight(&fh);
	float height = fh.ascent + fh.descent + fh.leading;
	char* left[] = {ARTIST_LABEL, YEAR_LABEL, 0};
	char* center[] = {ALBUM_LABEL, TRACK_LABEL, 0};
	char* right[] = {TITLE_LABEL, GENRE_LABEL, 0};
	float leftWidth = 0;
	float centerWidth = 100;
	float rightWidth = 200;

	/*
		int i=0;
		while(left[i])
		{
			if(StringWidth(left[i]) > leftWidth)
			{
				leftWidth = StringWidth(left[i]);
			}
			i++;
		}

		i=0;
		while(center[i])
		{
			if(StringWidth(center[i]) > centerWidth)
			{
				centerWidth = StringWidth(center[i]);
			}
			i++;
		}

		i=0;
		while(right[i])
		{
			if(StringWidth(right[i]) > rightWidth)
			{
				rightWidth = StringWidth(right[i]);
			}
			i++;
		}
	*/


	artistStringView = new BStringView("artist", ARTIST_LABEL);

	yearStringView = new BStringView("year", YEAR_LABEL);

	commentStringView = new BStringView("comment", COMMENT_LABEL);

	albumStringView = new BStringView("album", ALBUM_LABEL);

	trackStringView = new BStringView("track", TRACK_LABEL);

	titleStringView = new BStringView("title", TITLE_LABEL);

	genreStringView = new BStringView("genre", GENRE_LABEL);

	AEEncoder* encoder = settings->Encoder();
	BString str;
	if (encoder) {
		str = encoder->GetPattern();
	}
	fileNamePatternTextControl = new BTextControl("fileNamePatternTextControl",
													B_EMPTY_STRING, str.String(), NULL);

	applyButton = new BButton("applyButton", APPLY_BTN,
							  new BMessage(FILE_NAME_PATTERN_CHANGED));
	
	BLayoutBuilder::Group<>(this, B_VERTICAL)
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
		.AddGroup(B_HORIZONTAL, 0.0f)
			.Add(fileNamePatternTextControl)
			.Add(applyButton)
		.End()
	.End();
}

void
FileNamePatternView::MakeFocus(bool focused)
{
	PRINT(("FileNamePatternView::MakeFocused(bool)\n"));

	fileNamePatternTextControl->MakeFocus(focused);
}

void
FileNamePatternView::SetEnabled(bool value)
{
	PRINT(("FileNamePatternView::SetEnabled(bool)\n"));

	fileNamePatternTextControl->SetEnabled(value);
	applyButton->SetEnabled(value);
}

void
FileNamePatternView::AttachedToWindow()
{
	PRINT(("FileNamePatternView::AttachedToWindow()\n"));

	InitView();

	fileNamePatternTextControl->SetTarget(this);
	applyButton->SetTarget(this);
}

void
FileNamePatternView::GetPreferredSize(float* width, float* height)
{
	PRINT(("FileNamePatternView::GetPreferredSize(float*,float*)\n"));

	int space = 6;

	*width = genreStringView->Frame().right + space;
	*height = fileNamePatternTextControl->Frame().bottom + 2 * space +
			  applyButton->Frame().Height();
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
					encoder->SetPattern(fileNamePatternTextControl->Text());
					parentMessenger.SendMessage(message);
				}
			}
			break;
		case ENCODER_CHANGED: {
				AEEncoder* encoder = settings->Encoder();
				if (encoder) {
					fileNamePatternTextControl->SetText(encoder->GetPattern());
					BMessage msg(FILE_NAME_PATTERN_CHANGED);
					parentMessenger.SendMessage(&msg);
				}
			}
			break;
		default:
			BBox::MessageReceived(message);
	}
}
