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
												"Save as"	/*B_EMPTY_STRING*/, str.String(), NULL);

	fileNamePatternTextControl->SetModificationMessage(new BMessage(FILE_NAME_PATTERN_CHANGED));

	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_BIG_INSETS, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)
		.AddGrid()
			.Add(artistStringView, 0, 0)
			.Add(albumStringView, 1, 0)
			.Add(titleStringView, 2, 0)
			.Add(yearStringView, 3, 0)
			.Add(trackStringView, 4, 0)
			.Add(genreStringView, 5, 0)
			.Add(commentStringView, 6, 0)
		.End()
		.AddGroup(B_VERTICAL, 0.0f)
			.Add(fileNamePatternTextControl)
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
}

void
FileNamePatternView::AttachedToWindow()
{
	PRINT(("FileNamePatternView::AttachedToWindow()\n"));

	InitView();

	fileNamePatternTextControl->SetTarget(this);
}

void
FileNamePatternView::GetPreferredSize(float* width, float* height)
{
	PRINT(("FileNamePatternView::GetPreferredSize(float*,float*)\n"));
	BBox::GetPreferredSize(width, height);
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
