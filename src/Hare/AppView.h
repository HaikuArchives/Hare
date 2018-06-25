#ifndef __APP_VIEW_H__
#define __APP_VIEW_H__

#include <Box.h>
#include <Node.h>
#include <View.h>

#include "RefRow.h"

class BButton;
class BMessage;
class BRect;
class BStatusBar;
class BStringView;
class BTextControl;
class EditorView;
class EncoderListView;
class PrefWindow;

class AppView : public BView {
public:
	AppView();
	~AppView();
	virtual void AttachedToWindow();
	virtual void MessageReceived(BMessage* message);
	virtual void RefsReceived(BMessage* message);
private:
	void InitView();
	void InitializeColumn(BRefRow* row);
	void SetSaveAsColumn(BRefRow* row);
	void ApplyAttributeChanges(BMessage* message);
	void RemoveNodeFromList(node_ref* ref);
	void RemoveDeviceItemsFromList(int32 device);
	int32 UpdateItem(BMessage* message);
	static int32 RefsRecievedWrapper(void* args);
	static int32 RemoveItemsFromList(void* args);
	void Encode();
	void Cancel();
	void AlertUser(const char* message);
	static int32 EncodeThread(void* args);
	PrefWindow* prefWin;
	EncoderListView* listView;
	EditorView* editorView;
	BBox* editorBoxView;
	BScrollView* editorScrollView;
	BButton* encodeButton;
	BButton* cancelButton;
	BStatusBar* statusBar;
	bool cancel;
};

#endif
