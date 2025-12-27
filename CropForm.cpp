#include "CropForm.h"
#include "MyForm.h"
#include "FaceDetectionWrapper.h"

using namespace FDCProject;
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace msclr::interop;

void CropForm::InitializeFaceDetector()
{
	faceDetector = new FaceDetectionWrapper();
}

System::Void CropForm::btnDetect_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (currentImagePath == nullptr) return;

	try
	{
		lblStatus->Text = "STATUS: SCANNING FOR TARGETS...";
		lblStatus->ForeColor = Color::FromArgb(255, 255, 0);

		msclr::interop::marshal_context context;
		std::string imgPath = context.marshal_as<std::string>(currentImagePath);

		if (!faceDetector->LoadImageFile(imgPath))
		{
			MessageBox::Show("SYSTEM ERROR: CANNOT LOAD IMAGE", "ERROR",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			lblStatus->Text = "STATUS: ERROR - LOAD FAILED";
			lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
			return;
		}

		std::string cascadePath = "data\\haarcascades\\haarcascade_frontalface_default.xml";

		int faceCount = faceDetector->DetectFaces(cascadePath);

		if (faceCount == -1)
		{
			MessageBox::Show("SYSTEM ERROR: CANNOT LOAD CASCADE FILE", "ERROR",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			lblStatus->Text = "STATUS: ERROR - CASCADE FAILED";
			lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
			return;
		}
		else if (faceCount == 0)
		{
			MessageBox::Show("ALERT: NO TARGETS DETECTED", "NO DETECTION",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			lblStatus->Text = "STATUS: NO TARGETS FOUND";
			lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
			return;
		}

		currentFaceIndex = 0;
		ShowCurrentFace();
		UpdateFaceNavigation();

		lblStatus->Text = "STATUS: SCAN COMPLETE - " + faceCount + " TARGET(S) DETECTED";
		lblStatus->ForeColor = Color::FromArgb(0, 255, 0);

		MessageBox::Show("SCAN COMPLETE - " + faceCount + " TARGET(S) IDENTIFIED",
			"SUCCESS", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("SYSTEM ERROR: " + ex->Message, "ERROR",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		lblStatus->Text = "STATUS: SYSTEM ERROR";
		lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
	}
}

System::Void CropForm::btnPrev_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (currentFaceIndex > 0)
	{
		currentFaceIndex--;
		ShowCurrentFace();
		UpdateFaceNavigation();
	}
}

System::Void CropForm::btnNext_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (currentFaceIndex < faceDetector->GetFaceCount() - 1)
	{
		currentFaceIndex++;
		ShowCurrentFace();
		UpdateFaceNavigation();
	}
}

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

void CropForm::ShowCurrentFace()
{
	int faceCount = faceDetector->GetFaceCount();
	if (faceCount == 0) return;

	std::vector<unsigned char> buffer;
	if (faceDetector->GetImageWithRectangle(currentFaceIndex, buffer))
	{
		array<unsigned char>^ data = gcnew array<unsigned char>(buffer.size());
		System::Runtime::InteropServices::Marshal::Copy((IntPtr)buffer.data(), data, 0, buffer.size());

		System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(data);
		pictureBox1->Image = Image::FromStream(ms);
		pictureBox1->Refresh();
	}
}

void CropForm::UpdateFaceNavigation()
{
	int faceCount = faceDetector->GetFaceCount();
	lblFaceInfo->Text = "TARGET: " + (currentFaceIndex + 1) + " / " + faceCount;

	btnPrev->Enabled = (currentFaceIndex > 0);
	btnNext->Enabled = (currentFaceIndex < faceCount - 1);
	btnSearch->Enabled = (faceCount > 0);
}

