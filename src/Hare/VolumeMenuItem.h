/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __VOLUME_MENU_ITEM_H__
#define __VOLUME_MENU_ITEM_H__

#include <MenuItem.h>

class BMessage;
class BVolume;
struct fs_info;

class VolumeMenuItem : public BMenuItem {
public:
	VolumeMenuItem(BVolume* volume);
	VolumeMenuItem(fs_info* info);
	~VolumeMenuItem();
	dev_t GetDevice();
private:
	dev_t device;
};

#endif
