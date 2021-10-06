/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __PREFERENCES_H__
#define __PREFERENCES_H__

#include <Archivable.h>

#include "CommandConstants.h"

class AEEncoder;
class BMessage;

class Settings : public BArchivable {
public:
	Settings();
	Settings(BMessage* archive);
	~Settings();

	virtual status_t Archive(BMessage* archive, bool deep = true) const;
	virtual BArchivable* Instantiate(BMessage* archive);

	static void OpenSettings();
	void SaveSettings();
/*
	BRect WindowFrame();
	void SetWindowFrame(BRect value);
*/
	bool IsEncoding();
	void SetEncoding(bool value);

	AEEncoder* Encoder();
	void SetEncoder(AEEncoder* value);

	const char* EncoderName();
	void SetEncoderName(const char* value);
	
	const char* PathPattern();
	void SetPathPattern(const char* value);

	const char* AddOnsDirectory();

	void SetColumnsState(BMessage* message);
	BMessage* ColumnsState();

	void PrintToStream();
private:
//	BRect windowFrame;
	bool encoding;
	AEEncoder* encoder;
	char encoderName[B_FILE_NAME_LENGTH];
	char pathPattern[B_PATH_NAME_LENGTH];
	char addonDirectory[B_PATH_NAME_LENGTH];
	BMessage columnsState;

};

extern Settings* settings;

#endif
