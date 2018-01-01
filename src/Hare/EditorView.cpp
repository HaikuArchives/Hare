
#include "EditorView.h"

#include <stdlib.h>
#include <string.h>

#include <Button.h>
#include <CheckBox.h>
#include <Debug.h>
#include <Entry.h>
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

#include <ColumnTypes.h>

#include "GenreList.h"

#include "AppDefs.h"
#include "CommandConstants.h"
#include "GUIStrings.h"

EditorView::EditorView(BRect frame)
        :
        BBox(frame, "editorView")
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

        SetLabel(EDITOR_LABEL);

        int space = 6;

        numSelected = 0;
        selectedIndexes = 0;

        font_height fh;
        GetFontHeight(&fh);
        float height = fh.ascent + fh.descent + fh.leading;

        char* left[] = {
                ARTIST_COLUMN,
                ALBUM_COLUMN,
                TITLE_COLUMN,
                TRACK_COLUMN,
                YEAR_COLUMN,
                0
        };
        char* right[] = {
                COMMENT_COLUMN,
                GENRE_COLUMN,
                0
        };
        //float leftWidth = 0;
        //float rightWidth = 400;

        int i = 0;

        /*
                while(left[i])
                {
                        if(StringWidth(left[i]) > leftWidth)
                        {
                                leftWidth = StringWidth(left[i]);
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

        //use cb to determine spacing of box at different fonts
        BCheckBox cb(BRect(0, 0, 0, 0), 0, 0, 0);
        cb.ResizeToPreferred();
       



        /*BRect leftCB = Bounds();
        leftCB.InsetBy(space, 2 * space);
        leftCB.right = 200; //leftCB.left + leftWidth + cb.Frame().Width();
        leftCB.bottom = 100; //leftCB.top + height;

        BRect leftTC = leftCB;
        leftTC.left = leftCB.right + space / 2;
        leftTC.right = leftTC.left + 110;

        BRect rightCB = leftCB;
                     .Add(reverbMenu->CreateLabelLayoutItem(), 0, 1)
                     .Add(reverbMenu->CreateMenuBarLayoutItem(), 1, 1)
        
                     .Add(inputMenu->CreateLabelLayoutItem(), 0, 2)
                     .Add(inputMenu->CreateMenuBarLayoutItem(), 1, 2)
        
                     .Add(volumeLabel, 0, 3)
                     .Add(volumeSlider, 1, 3)
        rightCB.left = leftTC.right + space;
        rightCB.right = rightCB.left + rightWidth + cb.Frame().Width();

        BRect rightTC = rightCB;
        rightTC.left = rightCB.right + space / 2;
        rightTC.right = rightTC.left + 110;*/

        artistCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "artistCB", ARTIST_COLUMN,
                                                                    new BMessage(MSG_ARTIST_CB));

        artistTextControl = new BTextControl(BRect(0, 0, 16, 16), "artistTC", 0, "", 0);

        albumCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "albumCB", ALBUM_COLUMN,
                                                                    new BMessage(MSG_ALBUM_CB));

        albumTextControl = new BTextControl(BRect(0, 0, 16, 16), "albumTC", 0, "", 0);
       
        titleCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "titleCB", TITLE_COLUMN,
                                                                        new BMessage(MSG_TITLE_CB));
        titleTextControl = new BTextControl(BRect(0, 0, 16, 16), "titleTC", 0, "", 0);

        trackCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "trackCB", TRACK_COLUMN, new BMessage(MSG_TRACK_CB));

        trackTextControl = new BTextControl(BRect(0, 0, 16, 16), "trackTC", 0, "", 0);

        yearCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "yearCB", YEAR_COLUMN, new BMessage(MSG_YEAR_CB));

        yearTextControl = new BTextControl(BRect(0, 0, 16, 16), "yearTC", 0, "", 0);

        commentCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "commentCB", COMMENT_COLUMN, new BMessage(MSG_COMMENT_CB));

        commentTextControl = new BTextControl(BRect(0, 0, 16, 16), "commentTC", 0, "", 0);
       
        genreCheckBox = new BCheckBox(BRect(0, 0, 1, 1), "genreCB", GENRE_COLUMN, new BMessage(MSG_GENRE_CB));


        // Build the layout
        SetLayout(new BGroupLayout(B_HORIZONTAL));
        
    AddChild(BGroupLayoutBuilder(B_VERTICAL, 10)
          .Add(BGridLayoutBuilder(10,10)
     
                    .Add(artistCheckBox, 0, 0)
                                .Add(artistTextControl,1, 0)
                                .Add(albumCheckBox, 0, 1)
                                .Add(albumTextControl,1, 1)
                                .Add(titleCheckBox, 0, 2)
                                .Add(titleTextControl,1, 2)
                                .Add(trackCheckBox, 0, 3)
                            .Add(trackTextControl,1, 3)
                                .Add(yearCheckBox, 0, 4)
                                .Add(yearTextControl, 1, 4)
                        
                                .Add(commentCheckBox, 3, 0)
                                .Add(commentTextControl, 4, 0)
                                .Add(genreCheckBox, 3, 1)
                )
        );


        genreBox = new BBox(BRect(0,0,100,100), "genreBox");

        // INSIDE THE BOX
        {
                BMenu* menu = new BMenu(GENRE_COLUMN);
                menu->SetLabelFromMarked(true);
                int genres = GenreList::NumGenres();
                BList genreList;
                for (int i = 0; i < genres; i++) {
                        char* genre = GenreList::Genre(i);
                        genreList.AddItem(genre);
                }

                genreList.SortItems(&GenreList::GenreSort);
                char last = 'A';
                char current;
                for (int i = 0; i < genres; i++) {
                        char* genre = (char*)genreList.ItemAt(i);
                        current = genre[0];
                        if (current != last) {
                                menu->AddSeparatorItem();
                        }
                        menu->AddItem(new BMenuItem(genre,
                                                                                new BMessage(GENRE_SEL_CHNGD)));
                        last = current;
                }

                BRect ctrlFrame = genreBox->Bounds();
                ctrlFrame.InsetBy(space, space);
                ctrlFrame.bottom = ctrlFrame.top + height;
                genreMenuField = new BMenuField(ctrlFrame, "genreMenuField", 0, menu);

                ctrlFrame.OffsetBy(0, height + (2 * space));
                genreTextControl = new BTextControl(ctrlFrame, "genreTextControl", 0, "", 0);
        }
        // DONE INSIDE THE BOX

        applyButton = new BButton(BRect(0, 1, 80, 1), "applyButton", APPLY_BTN,
                                                          new BMessage(APPLY_MSG), B_FOLLOW_RIGHT | B_FOLLOW_BOTTOM);

        /*AddChild(artistCheckBox);
        AddChild(artistTextControl);

        AddChild(albumCheckBox);
        AddChild(albumTextControl);

        AddChild(titleCheckBox);
        AddChild(titleTextControl);

        AddChild(trackCheckBox);
        AddChild(trackTextControl);

        AddChild(yearCheckBox);
        AddChild(yearTextControl);

        AddChild(commentCheckBox);
        AddChild(commentTextControl);

        AddChild(genreCheckBox);
        AddChild(genreBox);
        genreBox->AddChild(genreMenuField);
        genreBox->AddChild(genreTextControl);

        AddChild(applyButton);

        ResizeToPreferred();*/
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
EditorView::GetPreferredSize(float* width, float* height)
{
        PRINT(("EditorView::GetPreferredSize(float* float*)\n"));

        int space = 6;

        *width = commentTextControl->Frame().right + space;
        *height = yearTextControl->Frame().bottom + space;
        float ht = 100; //genreBox->Frame().bottom + 3*space +
        //      applyButton->Frame().Height();
        if (ht > *height) {
                *height = ht;
        }
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
                case LIST_SELECTION_MSG:
                        ListSelectionChanged(message);
                        break;
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
                        BBox::MessageReceived(message);
        }
}
