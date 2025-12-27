#include "CropForm.h"
#include "MyForm.h"

using namespace FDCProject;
using namespace System;
using namespace System::IO;
using namespace msclr::interop;

System::Void CropForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (faceDetector->GetFaceCount() == 0) return;

	try
	{
		String^ tempFacePath = "temp_selected_target.jpg";
		marshal_context context;
		std::string tempPath = context.marshal_as<std::string>(tempFacePath);

		if (!faceDetector->SaveCurrentFace(currentFaceIndex, tempPath))
		{
			MessageBox::Show("SYSTEM ERROR: CANNOT SAVE TARGET", "ERROR",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		mainForm->SetSelectedTarget(tempFacePath);

		MessageBox::Show("TARGET SELECTED - RETURN TO MAIN SCREEN TO IDENTIFY", "SUCCESS",
			MessageBoxButtons::OK, MessageBoxIcon::Information);

		this->Close();
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("SYSTEM ERROR: " + ex->Message, "ERROR",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

