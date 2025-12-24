// Main.cpp : main project file.
#include "MyForm.h"
using namespace FDCProject;
[STAThreadAttribute]
int Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles(); // Enabling Windows XP visual effects before any controls arecreated
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	Application::Run(gcnew MyForm());
	return 0;
}