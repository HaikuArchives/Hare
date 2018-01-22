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

	BRect WindowFrame();
	void SetWindowFrame(BRect value);

	bool IsEncoding();
	void SetEncoding(bool value);

	AEEncoder* Encoder();
	void SetEncoder(AEEncoder* value);

	const char* EncoderName();
	void SetEncoderName(const char* value);

	int32* ColumnDisplayOrder();
	void SetColumnDisplayOrder(const int32* value);

	bool* ColumnsShown();
	void SetColumnsShown(const bool* value);

	float* ColumnWidths();
	void SetColumnWidths(const float* value);

	const char* AddOnsDirectory();

	void PrintToStream();
private:
	BRect windowFrame;
	bool encoding;
	AEEncoder* encoder;
	char encoderName[B_FILE_NAME_LENGTH];
	char addonDirectory[B_PATH_NAME_LENGTH];
	int32 columnDisplayOrder[NUM_OF_COLUMNS];
	bool columnsShown[NUM_OF_COLUMNS];
	float columnWidths[NUM_OF_COLUMNS];

};

extern Settings* settings;

#endif
