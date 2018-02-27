#ifndef __ENCODER_LIST_VIEW_H__
#define __ENCODER_LIST_VIEW_H__

#include <ColumnListView.h>

class BBitmap;
class BMessage;
class BRect;

class EncoderListView : public BColumnListView {
public:
	EncoderListView();
	~EncoderListView();
	virtual void AttachedToWindow();
	virtual void MessageDropped(BMessage* message, BPoint point);
	virtual void MessageReceived(BMessage* message);
	virtual void SelectionChanged();
	BBitmap* GetCheckMark();
private:
	void InitView();
	BBitmap* checkMark;
};

#endif
