#ifndef __FILE_NAME_PATTERN_VIEW_H__
#define __FILE_NAME_PATTERN_VIEW_H__

#include <Box.h>

class BButton;
class BMessage;
class BRect;
class BStringView;
class BTextControl;

class FileNamePatternView : public BBox {
public:
	FileNamePatternView();
	~FileNamePatternView();
	virtual void AttachedToWindow();
	virtual void MessageReceived(BMessage* message);
	virtual void MakeFocus(bool focused = true);
	void SetEnabled(bool value);
private:
	void InitView();
	BStringView* artistStringView;
	BStringView* albumStringView;
	BStringView* titleStringView;
	BStringView* yearStringView;
	BStringView* commentStringView;
	BStringView* trackStringView;
	BStringView* genreStringView;
	BTextControl* filePathTextControl;
	BTextControl* namePatternTextControl;
	BButton* applyButton;
};

#endif
