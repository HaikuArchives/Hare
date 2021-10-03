/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __MEDIA_MENU_ITEM_H__
#define __MEDIA_MENU_ITEM_H__

#include <MenuItem.h>
#include <MediaFormats.h>

class BArchivable;
class BMessage;

class MediaMenuItem : public BMenuItem {
public:
	MediaMenuItem(const char* label, media_file_format* mfi,
				  media_codec_info* mci);
	MediaMenuItem(BMessage* archive);
	virtual status_t Archive(BMessage* archive, bool deep = true) const;
	static BArchivable* Instantiate(BMessage* archive);

	const media_file_format* MediaFileFormat();
	const media_codec_info* MediaCodecInfo();

private:
	media_file_format mff;
	media_codec_info mci;
};

#endif
