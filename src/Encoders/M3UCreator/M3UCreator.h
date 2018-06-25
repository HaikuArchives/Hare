#ifndef __OGG_ENCODER_H__
#define __OGG_ENCODER_H__

#include "AEEncoder.h"

#define ADDON_NAME "M3U Creator"

#define M3U_MIME_TYPE "text/x-playlist"

class BFile;
class BList;
class BMessage;

class M3UCreator : public AEEncoder {
public:
	M3UCreator();
	~M3UCreator();

	virtual int32 Encode(BMessage* encodeMessage);
	virtual int32 UninitEncoder();
	virtual const char* GetDefaultPattern();
private:
	BList fileList;
};

#endif
