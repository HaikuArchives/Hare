#include "Application.h"

#include <Application.h>
#include <Beep.h>
#include <Debug.h>
#include <Message.h>
#include <Messenger.h>

#include "AppDefs.h"
#include "AppWindow.h"
#include "CommandConstants.h"
#include "GUIStrings.h"
#include "Settings.h"

Application::Application()
	:
	BApplication(SIGNATURE)
{
	PRINT(("Application::Application()\n"));

	add_system_beep_event(SYSTEM_BEEP_ENCODING_DONE);

	window = AppWindow::GetInstance();
	window->Show();
	
	settings->PrintToStream();
}

Application::~Application()
{
	PRINT(("Application::~Application()\n"));

	delete settings;
}

void
Application::ArgvReceived(int32 argc, char** argv)
{
	PRINT(("Application::ArgvReceived(int32,char**)\n"));
}

void
Application::MessageReceived(BMessage* message)
{
	//PRINT(("Application::MessageReceived(BMessage*)\n"));

	switch (message->what) {
		case FILE_NAME_PATTERN_CHANGED: {
			BMessenger sender(window);
			sender.SendMessage(message);
			}
			break;
		default:
			BApplication::MessageReceived(message);
	}
}

void
Application::RefsReceived(BMessage* message)
{
	PRINT(("Application::RefsReceived(BMessage*)\n"));

	window->PostMessage(message);
}

int
main()
{
	PRINT(("main()\n"));

	new Application();
	be_app->Run();
	delete be_app;
	return 0;
}
