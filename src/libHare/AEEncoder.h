/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __AE_ENCDER_H__
#define __AE_ENCDER_H__

#include <Message.h>
#include <Menu.h>
#include <Volume.h>
#include <Archivable.h>
#include <String.h>

#ifdef __FSS_BUILD
#define __FSS_EXPORT __declspec(dllexport)
#else
#define __FSS_EXPORT __declspec(dllimport)
#endif

#define FSS_ENCODE 'enc'
#define FSS_SETMAX_STATUS_BAR 'max'
#define FSS_MENU_ITEM_SELECTED 'mnu'

#define FSS_INPUT_NOT_SUPPORTED 8000
#define FSS_EXE_NOT_FOUND 8001
#define FSS_CANCEL_ENCODING 8002

class AEEncoder {
public:
	AEEncoder(const char* encoderName);
	virtual ~AEEncoder();

	int32 InitCheck();
	const char* GetName();
	const char* GetPattern();
	void SetPattern(const char* value);
	BMenu* GetMenu();
	virtual int32 InitEncoder();
	virtual int32 Encode(BMessage* encodeMessage);
	virtual int32 UninitEncoder();
	virtual const char* GetDefaultPattern();

protected:
	int32 error;
	BString name;
	BString pattern;
	BMenu* menu;

	virtual int32 LoadDefaultMenu();

	int32 FindExecutable(const char* executable, char* path);
	bool CheckForCancel();

private:
	bool canceled;

	AEEncoder();
	AEEncoder(AEEncoder& enc);
	int32 LoadDefaultPattern();
	int32 LoadSettings();
	int32 SaveSettings();
	int32 QueryForExecutable(const char* executable,
							 BVolume* volume, char* path);
};

// extern "C" __FSS_EXPORT AEEncoder* load_encoder();

#endif
