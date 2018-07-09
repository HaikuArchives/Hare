#include "EncoderListView.h"

#include <string.h>

#include <Debug.h>
#include <ListView.h>
#include <Message.h>
#include <Rect.h>

#include <ColumnTypes.h>

#include "AppDefs.h"
#include "CheckMark.h"
#include "CommandConstants.h"
#include "GUIStrings.h"
#include "Settings.h"

EncoderListView::EncoderListView()
	:
	BColumnListView("listView",
		B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE | B_NAVIGABLE_JUMP,
		B_FANCY_BORDER, true)
{
	PRINT(("EncoderListView::EncoderListView(BRect)\n"));

	SetSelectionMode(B_MULTIPLE_SELECTION_LIST);

	InitView();
}

EncoderListView::~EncoderListView()
{
	PRINT(("EncoderListView::~EncoderListView()\n"));

	delete checkMark;

	BMessage columnState;
	SaveState(&columnState);
	settings->SetColumnsState(&columnState);
}

void
EncoderListView::InitView()
{
	PRINT(("EncoderListView::InitView()\n"));

	checkMark = new CheckMark();

	float minWidth;
	float maxWidth = 1000;
	int32 truncate = 3;
	
	AddColumn(new BBitmapColumn("Icon", 16, 16, 16, B_ALIGN_CENTER), COMPLETE_COLUMN_INDEX);
	
	minWidth = StringWidth(FILE_COLUMN) + 20;
	AddColumn(new BStringColumn(FILE_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), FILE_COLUMN_INDEX);

	minWidth = StringWidth(SAVE_AS_COLUMN) + 20;
	AddColumn(new BStringColumn(SAVE_AS_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), SAVE_AS_COLUMN_INDEX);

	minWidth = StringWidth(ARTIST_COLUMN) + 20;
	AddColumn(new BStringColumn(ARTIST_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), ARTIST_COLUMN_INDEX);

	minWidth = StringWidth(ALBUM_COLUMN) + 20;
	AddColumn(new BStringColumn(ALBUM_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), ALBUM_COLUMN_INDEX);

	minWidth = StringWidth(TITLE_COLUMN) + 20;
	AddColumn(new BStringColumn(TITLE_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), TITLE_COLUMN_INDEX);

	minWidth = StringWidth(TRACK_COLUMN) + 20;
	AddColumn(new BStringColumn(TRACK_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), TRACK_COLUMN_INDEX);

	minWidth = StringWidth(YEAR_COLUMN) + 20;
	AddColumn(new BStringColumn(YEAR_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), YEAR_COLUMN_INDEX);

	minWidth = StringWidth(COMMENT_COLUMN) + 20;
	AddColumn(new BStringColumn(COMMENT_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), COMMENT_COLUMN_INDEX);

	minWidth = StringWidth(GENRE_COLUMN) + 20;
	AddColumn(new BStringColumn(GENRE_COLUMN, minWidth, minWidth, maxWidth, truncate, B_ALIGN_LEFT), GENRE_COLUMN_INDEX);

	LoadState(settings->ColumnsState());
}

void
EncoderListView::AttachedToWindow()
{
	PRINT(("EncoderListView::AttachedToWindow()\n"));
}

void
EncoderListView::MessageDropped(BMessage* message, BPoint point)
{
	BMessenger messenger(Parent());
	messenger.SendMessage(message);
}

void
EncoderListView::MessageReceived(BMessage* message)
{
	PRINT(("EncoderListView::MessageReceived(BMessage*)\n"));

	switch (message->what) {
		default:
			BColumnListView::MessageReceived(message);
	}
}

void
EncoderListView::SelectionChanged()
{
	BMessage* listSelectMsg = new BMessage(LIST_SELECTION_MSG);
	listSelectMsg->AddPointer("source", this);
	
	for (int32 i = 0; i < CountRows(); i++) {
		if (RowAt(i)->IsSelected()) {
			listSelectMsg->AddInt32("index", i);
		}
	}
	
	BMessenger messenger(Parent());
	messenger.SendMessage(listSelectMsg);
	delete listSelectMsg;
}

BBitmap*
EncoderListView::GetCheckMark()
{
	return checkMark;
}
