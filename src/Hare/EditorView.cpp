/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#include "EditorView.h"

#include <stdlib.h>
#include <string.h>

#include <Button.h>
#include <CheckBox.h>
#include <Debug.h>
#include <Entry.h>
#include <LayoutBuilder.h>
#include <List.h>
#include <ListView.h>
#include <Menu.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <Message.h>
#include <Messenger.h>
#include <GridLayout.h>
#include <GroupLayout.h>
#include <OptionPopUp.h>
#include <GroupLayoutBuilder.h>
#include <GridLayoutBuilder.h>
#include <RadioButton.h>
#include <Rect.h>
#include <TextControl.h>
#include <String.h>

#include <ColumnTypes.h>

#include "GenreList.h"

#include "AppDefs.h"
#include "CommandConstants.h"
#include "GUIStrings.h"

EditorView::EditorView()
        :
        BView("editorView", B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE_JUMP)
{
        PRINT(("EditorView::EditorView(BRect)\n"));
}

EditorView::~EditorView()
{
        PRINT(("EditorView::~EditorView()\n"));
}

void
EditorView::InitView()
{
        PRINT(("EditorView::InitView()\n"));

        numSelected = 0;
        selectedIndexes = 0;

        artistCheckBox = new BCheckBox("artistCB", ARTIST_COLUMN, new BMessage(MSG_ARTIST_CB));
        artistTextControl = new BTextControl("artistTC", 0, "", 0);
        albumCheckBox = new BCheckBox("albumCB", ALBUM_COLUMN, new BMessage(MSG_ALBUM_CB));
        albumTextControl = new BTextControl("albumTC", 0, "", 0);
        titleCheckBox = new BCheckBox("titleCB", TITLE_COLUMN, new BMessage(MSG_TITLE_CB));
        titleTextControl = new BTextControl("titleTC", 0, "", 0);
        trackCheckBox = new BCheckBox("trackCB", TRACK_COLUMN, new BMessage(MSG_TRACK_CB));
        trackTextControl = new BTextControl("trackTC", 0, "", 0);
        yearCheckBox = new BCheckBox("yearCB", YEAR_COLUMN, new BMessage(MSG_YEAR_CB));
        yearTextControl = new BTextControl("yearTC", 0, "", 0);
        commentCheckBox = new BCheckBox("commentCB", COMMENT_COLUMN, new BMessage(MSG_COMMENT_CB));
        commentTextControl = new BTextControl("commentTC", 0, "", 0);
        genreCheckBox = new BCheckBox("genreCB", GENRE_COLUMN, new BMessage(MSG_GENRE_CB));
        genreBox = new BBox(B_FANCY_BORDER);

        // INSIDE THE BOX
        {
                BMenu* menu = new BMenu(GENRE_COLUMN);
                menu->SetLabelFromMarked(true);
                int genres = GenreList::NumGenres();
                BList genreList;
                GenreList genreObject;
                for (int i = 0; i < genres; i++) {
                	char* genre = (char*)GenreList::Genre(i).String();
                	genreList.AddItem(genre);
                }

                genreList.SortItems(&GenreList::GenreSort);
                char last = 'A';
                char current;
                for (int i = 0; i < genres; i++) {
                        char* genre = (char*)genreList.ItemAt(i);
                        current = genre[0];
                        // current = genreObject.Genre(0);  //was [0]
                        if (current != last) {
                                menu->AddSeparatorItem();
                        }
                        menu->AddItem(new BMenuItem(genre, new BMessage(GENRE_SEL_CHNGD)));
                        last = current;
                }

                genreMenuField = new BMenuField("genreMenuField", 0, menu);

                genreTextControl = new BTextControl("genreTextControl", 0, "", 0);
        }
        // DONE INSIDE THE BOX

        applyButton = new BButton("applyButton", APPLY_BTN, new BMessage(APPLY_MSG));
        
        //Build the simple layout in the genre box

		BLayoutBuilder::Group<>(genreBox, B_VERTICAL)
			.SetInsets(B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING) 
			.Add(genreMenuField)
			.Add(genreTextControl)
			.End();

		// Build the layout
        
    	BLayoutBuilder::Grid<>(this, B_USE_DEFAULT_SPACING, B_USE_SMALL_SPACING)
    		.SetInsets(B_USE_DEFAULT_SPACING, B_USE_BIG_INSETS, B_USE_DEFAULT_SPACING, B_USE_DEFAULT_SPACING)   
			.Add(artistCheckBox, 0, 0)
			.Add(artistTextControl,1, 0)
			.Add(albumCheckBox, 0, 1)
			.Add(albumTextControl,1, 1)
			.Add(titleCheckBox, 0, 2)
			.Add(titleTextControl,1, 2)
			.Add(trackCheckBox, 0, 3)
			.Add(trackTextControl, 1, 3)
			.Add(yearCheckBox, 0, 4)
			.Add(yearTextControl, 1, 4)                    
			.Add(commentCheckBox, 0, 5)
			.Add(commentTextControl, 1, 5)
			.Add(genreCheckBox, 0, 6)
			.Add(genreBox, 1, 6)
			.AddGroup(B_HORIZONTAL, 0, 1, 7)
				.AddGlue()
				.Add(applyButton)
			.End()
		.End();
}

void
EditorView::AttachedToWindow()
{
        PRINT(("EditorView::AttachedToWindow()\n"));

        InitView();

        artistCheckBox->SetTarget(this);
        albumCheckBox->SetTarget(this);
        titleCheckBox->SetTarget(this);
        yearCheckBox->SetTarget(this);
        commentCheckBox->SetTarget(this);
        trackCheckBox->SetTarget(this);
        genreCheckBox->SetTarget(this);
        genreMenuField->Menu()->SetTargetForItems(this);
        applyButton->SetTarget(this);

        artistCheckBox->SetValue(B_CONTROL_OFF);
        albumCheckBox->SetValue(B_CONTROL_OFF);
        titleCheckBox->SetValue(B_CONTROL_OFF);
        yearCheckBox->SetValue(B_CONTROL_OFF);
        commentCheckBox->SetValue(B_CONTROL_OFF);
        trackCheckBox->SetValue(B_CONTROL_OFF);
        genreCheckBox->SetValue(B_CONTROL_OFF);

        EnableCheckBoxes(false);
        applyButton->SetEnabled(false);
        applyButton->MakeDefault(true);

        SetEnabled(artistCheckBox, artistTextControl);
        SetEnabled(albumCheckBox, albumTextControl);
        SetEnabled(titleCheckBox, titleTextControl);
        SetEnabled(yearCheckBox, yearTextControl);
        SetEnabled(commentCheckBox, commentTextControl);
        SetEnabled(trackCheckBox, trackTextControl);
        SetEnabled(genreCheckBox, genreMenuField);
        SetEnabled(genreCheckBox, genreTextControl);
}

void
EditorView::Apply()
{
        PRINT(("EditorView::Apply()\n"));

        BMessage message(APPLY_ATTRIBUTE_CHANGES);

        if (artistCheckBox->Value() == B_CONTROL_ON) {
                message.AddString("artist", artistTextControl->Text());
        }

        if (albumCheckBox->Value() == B_CONTROL_ON) {
                message.AddString("album", albumTextControl->Text());
        }

        if (titleCheckBox->Value() == B_CONTROL_ON) {
                message.AddString("title", titleTextControl->Text());
        }

        if (yearCheckBox->Value() == B_CONTROL_ON) {
                message.AddString("year", yearTextControl->Text());
        }

        if (commentCheckBox->Value() == B_CONTROL_ON) {
                message.AddString("comment", commentTextControl->Text());
        }

        if (trackCheckBox->Value() == B_CONTROL_ON) {
                message.AddString("track", trackTextControl->Text());
        }

        if (genreCheckBox->Value() == B_CONTROL_ON) {
                if (strcmp(genreTextControl->Text(), "") != 0) {
                        message.AddString("genre", genreTextControl->Text());
                } else {
                        BMenu* menu = genreMenuField->Menu();
                        menu->SetMaxContentWidth(StringWidth("contemporary classical WWWWW "));
                        BMenuItem* item = menu->FindMarked();
                        message.AddString("genre", item->Label());
                }
        }

        for (int i = 0; i < numSelected; i++) {
                message.AddInt32("index", selectedIndexes[i]);
        }

        BMessenger parentMessenger(Parent());
        parentMessenger.SendMessage(&message);
}

void
EditorView::ListSelectionChanged(BMessage* message)
{
        PRINT(("EditorView::ListSelectionChanged(BMessage*)\n"));

        free(selectedIndexes);

        BColumnListView* colListView;
        message->FindPointer("source", (void**)&colListView);

        type_code index_type;
        message->GetInfo("index", &index_type, &numSelected);

        selectedIndexes = (int32*)malloc(numSelected * sizeof(int32));

        for (int i = 0; i < numSelected; i++) {
                message->FindInt32("index", i, &(selectedIndexes[i]));
        }

        int32 index;
        message->FindInt32("index", &index);

        if (numSelected == 0) {
                artistCheckBox->SetValue(B_CONTROL_OFF);
                albumCheckBox->SetValue(B_CONTROL_OFF);
                titleCheckBox->SetValue(B_CONTROL_OFF);
                yearCheckBox->SetValue(B_CONTROL_OFF);
                commentCheckBox->SetValue(B_CONTROL_OFF);
                trackCheckBox->SetValue(B_CONTROL_OFF);
                genreCheckBox->SetValue(B_CONTROL_OFF);

                EnableCheckBoxes(false);
                applyButton->SetEnabled(false);
                SetControlValues(0);
        } else if (numSelected == 1) {
                artistCheckBox->SetValue(B_CONTROL_ON);
                albumCheckBox->SetValue(B_CONTROL_ON);
                titleCheckBox->SetValue(B_CONTROL_ON);
                yearCheckBox->SetValue(B_CONTROL_ON);
                commentCheckBox->SetValue(B_CONTROL_ON);
                trackCheckBox->SetValue(B_CONTROL_ON);
                genreCheckBox->SetValue(B_CONTROL_ON);

                EnableCheckBoxes(true);
                applyButton->SetEnabled(true);

				BRefRow* row = (BRefRow*)colListView->RowAt(index);
				SetControlValues(row);
        } else {
                artistCheckBox->SetValue(B_CONTROL_ON);
                albumCheckBox->SetValue(B_CONTROL_ON);
                titleCheckBox->SetValue(B_CONTROL_OFF);
                yearCheckBox->SetValue(B_CONTROL_ON);
                commentCheckBox->SetValue(B_CONTROL_ON);
                trackCheckBox->SetValue(B_CONTROL_OFF);
                genreCheckBox->SetValue(B_CONTROL_ON);

                EnableCheckBoxes(true);
                applyButton->SetEnabled(true);

				BRefRow* row = (BRefRow*)colListView->RowAt(index);
				SetControlValues(row);
        }

        SetEnabled(artistCheckBox, artistTextControl);
        SetEnabled(albumCheckBox, albumTextControl);
        SetEnabled(titleCheckBox, titleTextControl);
        SetEnabled(yearCheckBox, yearTextControl);
        SetEnabled(commentCheckBox, commentTextControl);
        SetEnabled(trackCheckBox, trackTextControl);
        SetEnabled(genreCheckBox, genreMenuField);
        SetEnabled(genreCheckBox, genreTextControl);
}

void
EditorView::EnableCheckBoxes(bool value)
{
        artistCheckBox->SetEnabled(value);
        albumCheckBox->SetEnabled(value);
        titleCheckBox->SetEnabled(value);
        yearCheckBox->SetEnabled(value);
        commentCheckBox->SetEnabled(value);
        trackCheckBox->SetEnabled(value);
        genreCheckBox->SetEnabled(value);
}

void
EditorView::SetControlValues(BRefRow* row)
{
	artistTextControl->SetText("");
	albumTextControl->SetText("");
	titleTextControl->SetText("");
	yearTextControl->SetText("");
	commentTextControl->SetText("");
	trackTextControl->SetText("");
	genreTextControl->SetText("");

	BStringField* tmpStringField;

	if (row) {
		tmpStringField = (BStringField*)row->GetField(ARTIST_COLUMN_INDEX);
		const char* artist = tmpStringField->String();
		if (!artist) artist = "";
		tmpStringField = (BStringField*)row->GetField(ALBUM_COLUMN_INDEX);
		const char* album = tmpStringField->String();
		if (!album) album = "";
		tmpStringField = (BStringField*)row->GetField(TITLE_COLUMN_INDEX);
		const char* title = tmpStringField->String();
		if (!title) title = "";
		tmpStringField = (BStringField*)row->GetField(YEAR_COLUMN_INDEX);
		const char* year = tmpStringField->String();
		if (!year) year = "";
		tmpStringField = (BStringField*)row->GetField(COMMENT_COLUMN_INDEX);
		const char* comment = tmpStringField->String();
		if (!comment) comment = "";
		tmpStringField = (BStringField*)row->GetField(TRACK_COLUMN_INDEX);
		const char* track = tmpStringField->String();
		if (!track) track = "";
		tmpStringField = (BStringField*)row->GetField(GENRE_COLUMN_INDEX);
		const char* genre = tmpStringField->String();
		if (!genre) genre = "";

                artistTextControl->SetText(artist);
                albumTextControl->SetText(album);
                titleTextControl->SetText(title);
                yearTextControl->SetText(year);
                commentTextControl->SetText(comment);
                trackTextControl->SetText(track);

                BMenu* menu = genreMenuField->Menu();
                menu->SetMaxContentWidth(StringWidth("contemporary classical WWWWW "));
                BMenuItem* menuItem = menu->FindItem(genre);

                if (menuItem && (strcmp(genre, "") != 0)) {
                        menuItem->SetMarked(true);
                } else {
                        menuItem = menu->FindItem("Other");
                        menuItem->SetMarked(true);
                        genreTextControl->SetText(genre);
                }
        }
}

void
EditorView::MakeFocus(bool focused)
{
        PRINT(("EditorView::MakeFocus(bool)\n"));

        artistCheckBox->MakeFocus(focused);
}

void
EditorView::SetEnabled(bool value)
{
        PRINT(("EditorView::SetEnabled(bool)\n"));

        EnableCheckBoxes(value);
        artistTextControl->SetEnabled(value);
        albumTextControl->SetEnabled(value);
        titleTextControl->SetEnabled(value);
        yearTextControl->SetEnabled(value);
        commentTextControl->SetEnabled(value);
        trackTextControl->SetEnabled(value);
        genreTextControl->SetEnabled(value);
        genreMenuField->SetEnabled(value);
        applyButton->SetEnabled(value);

        if (value) {
                SetEnabled(artistCheckBox, artistTextControl);
                SetEnabled(albumCheckBox, albumTextControl);
                SetEnabled(titleCheckBox, titleTextControl);
                SetEnabled(yearCheckBox, yearTextControl);
                SetEnabled(commentCheckBox, commentTextControl);
                SetEnabled(trackCheckBox, trackTextControl);
                SetEnabled(genreCheckBox, genreMenuField);
                SetEnabled(genreCheckBox, genreTextControl);
        }
}

void
EditorView::SetEnabled(BCheckBox* checkbox, BControl* control)
{
        PRINT(("EditorView::SetEnabled(BCheckBox*,BControl*)\n"));

        if (checkbox->Value() == B_CONTROL_ON) {
                control->SetEnabled(true);
        } else {
                control->SetEnabled(false);
        }
}

void
EditorView::SetEnabled(BCheckBox* checkbox, BMenuField* menufield)
{
        PRINT(("EditorView::SetEnabled(BCheckBox*,BMenuField*)\n"));

        if (checkbox->Value() == B_CONTROL_ON) {
                menufield->SetEnabled(true);
        } else {
                menufield->SetEnabled(false);
        }
}

void
EditorView::MessageReceived(BMessage* message)
{
        //PRINT(("EditorView::MessageReceived(BMessage*)\n"));

        switch (message->what) {
                case APPLY_MSG:
                        Apply();
                        break;
                case MSG_ARTIST_CB:
                        SetEnabled(artistCheckBox, artistTextControl);
                        break;
                case MSG_ALBUM_CB:
                        SetEnabled(albumCheckBox, albumTextControl);
                        break;
                case MSG_TITLE_CB:
                        SetEnabled(titleCheckBox, titleTextControl);
                        break;
                case MSG_YEAR_CB:
                        SetEnabled(yearCheckBox, yearTextControl);
                        break;
                case MSG_COMMENT_CB:
                        SetEnabled(commentCheckBox, commentTextControl);
                        break;
                case MSG_TRACK_CB:
                        SetEnabled(trackCheckBox, trackTextControl);
                        break;
                case MSG_GENRE_CB:
                        SetEnabled(genreCheckBox, genreMenuField);
                        SetEnabled(genreCheckBox, genreTextControl);
                        break;
                case GENRE_SEL_CHNGD:
                        genreTextControl->SetText("");
                        break;
                default:
                        BView::MessageReceived(message);
        }
}
