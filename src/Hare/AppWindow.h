/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __APP_WINDOW_H__
#define __APP_WINDOW_H__

#include <Window.h>

class AppView;
class BMessage;
class BMessenger;
class BMenu;
class BMenuBar;
class BVolumeRoster;

class AppWindow : public BWindow {
public:
	AppWindow();
	~AppWindow();
	static AppWindow* GetInstance();
	BMenuBar* MenuBar();
	virtual void AboutRequested();
	virtual void FrameResized(float width, float height);
	virtual void MessageReceived(BMessage* message);
	virtual void RefsReceived(BMessage* message);
	virtual bool QuitRequested();
private:
	void InitWindow();
	void InitMenus();
	void LoadCDMenu();
	void LoadEncoderMenu();
	void MenuItemSelected(BMessage* message);
	void AddVolumeToList(const char* name);
	void AddVolumeToList(dev_t device);
	AppView* appView;
	BMenuBar* menuBar;
	BMenu* loadCdMenu;
	BMenu* encoderMenu;
	BMessenger* windowMessenger;
	BMessenger* viewMessenger;
	BVolumeRoster* volumes;
	image_id encoderAddon;
};

#endif
