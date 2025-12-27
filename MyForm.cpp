#include "MyForm.h"
#include "CropForm.h"
#include "GalleryForm.h"
#include "FaceDetectionWrapper.h"
#include <msclr/marshal_cppstd.h>

using namespace FDCProject;

System::Void MyForm::btnSelectTarget_Click(System::Object^ sender, System::EventArgs^ e)
{
	CropForm^ selectForm = gcnew CropForm(this);
	selectForm->ShowDialog();
}

System::Void MyForm::btnSearchPerson_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (selectedTargetPath == nullptr || !System::IO::File::Exists(selectedTargetPath))
	{
		MessageBox::Show("ALERT: NO TARGET SELECTED", "NO TARGET",
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	try
	{
		lblStatus->Text = "STATUS: SEARCHING DATABASE...";
		lblStatus->ForeColor = Color::FromArgb(255, 255, 0);

		String^ galleryPath = "faces";
		if (!System::IO::Directory::Exists(galleryPath))
		{
			System::IO::Directory::CreateDirectory(galleryPath);
		}

		array<String^>^ faceFiles = System::IO::Directory::GetFiles(galleryPath, "*.jpg");

		if (faceFiles->Length == 0)
		{
			MessageBox::Show("ALERT: DATABASE EMPTY - NO RECORDS FOUND", "NO DATA",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
			lblStatus->Text = "STATUS: DATABASE EMPTY";
			lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
			return;
		}

		FaceDetectionWrapper* faceDetector = new FaceDetectionWrapper();
		System::Collections::Generic::List<Tuple<String^, double>^>^ results =
			gcnew System::Collections::Generic::List<Tuple<String^, double>^>();

		msclr::interop::marshal_context context;
		std::string queryPath = context.marshal_as<std::string>(selectedTargetPath);

		for each (String^ filePath in faceFiles)
		{
			std::string galleryFilePath = context.marshal_as<std::string>(filePath);

			double distance = faceDetector->ComputeDistance(queryPath, galleryFilePath);
			if (distance >= 0)
			{
				results->Add(gcnew Tuple<String^, double>(filePath, distance));
			}
		}

		delete faceDetector;

		if (results->Count > 0)
		{
			for (int i = 0; i < results->Count - 1; i++)
			{
				for (int j = i + 1; j < results->Count; j++)
				{
					if (results[i]->Item2 > results[j]->Item2)
					{
						Tuple<String^, double>^ temp = results[i];
						results[i] = results[j];
						results[j] = temp;
					}
				}
			}

			int matchCount = Math::Min(3, results->Count);
			array<String^>^ topMatches = gcnew array<String^>(matchCount);
			array<double>^ scores = gcnew array<double>(matchCount);

			for (int i = 0; i < matchCount; i++)
			{
				topMatches[i] = results[i]->Item1;
				scores[i] = results[i]->Item2;
			}

			UpdateSearchResults(topMatches, scores);

			MessageBox::Show("IDENTIFICATION COMPLETE - " + matchCount + " MATCH(ES) FOUND",
				"SUCCESS", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			lblStatus->Text = "STATUS: NO MATCHES FOUND";
			lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
			MessageBox::Show("ALERT: NO MATCHES FOUND IN DATABASE", "NO MATCH",
				MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show("SYSTEM ERROR: " + ex->Message, "ERROR",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		lblStatus->Text = "STATUS: SYSTEM ERROR";
		lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
	}
}

System::Void MyForm::btnManageGallery_Click(System::Object^ sender, System::EventArgs^ e)
{
	GalleryForm^ galleryForm = gcnew GalleryForm();
	galleryForm->ShowDialog();
}