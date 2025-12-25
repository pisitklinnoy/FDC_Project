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
		String^ tempFacePath = "temp_search_face.jpg";
		marshal_context context;
		std::string tempPath = context.marshal_as<std::string>(tempFacePath);

		if (!faceDetector->SaveCurrentFace(currentFaceIndex, tempPath))
		{
			MessageBox::Show("Cannot save face for search");
			return;
		}

		array<String^>^ topMatches = gcnew array<String^>(3);
		array<double>^ scores = gcnew array<double>(3);

		FindTopMatches(tempFacePath, topMatches, scores);

		if (File::Exists(tempFacePath))
			File::Delete(tempFacePath);

		mainForm->UpdateSearchResults(topMatches, scores);
		this->Close();
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("Search error: " + ex->Message);
	}
}

