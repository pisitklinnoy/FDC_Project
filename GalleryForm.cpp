#include "GalleryForm.h"
#include "FaceDetectionWrapper.h"

using namespace FDCProject;
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace msclr::interop;

void GalleryForm::InitializeFaceDetector()
{
	faceDetector = new FaceDetectionWrapper();
}

System::Void GalleryForm::btnUploadFullImage_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		try
		{
			lblStatus->Text = "STATUS: PROCESSING IMAGE...";
			lblStatus->ForeColor = Color::FromArgb(255, 255, 0);

			msclr::interop::marshal_context context;
			std::string imgPath = context.marshal_as<std::string>(openFileDialog1->FileName);

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
				MessageBox::Show("ALERT: NO TARGETS DETECTED IN IMAGE", "NO DETECTION",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				lblStatus->Text = "STATUS: NO TARGETS FOUND";
				lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
				return;
			}

			String^ galleryPath = "faces";
			if (!Directory::Exists(galleryPath))
			{
				Directory::CreateDirectory(galleryPath);
			}

			// Find max Person ID
			int maxPersonId = 0;
			array<String^>^ existingFiles = Directory::GetFiles(galleryPath, "Person_*.jpg");
			for each(String ^ file in existingFiles)
			{
				String^ fileName = Path::GetFileNameWithoutExtension(file);
				array<String^>^ parts = fileName->Split('_');
				if (parts->Length >= 2)
				{
					int personId;
					if (Int32::TryParse(parts[1], personId))
					{
						if (personId > maxPersonId)
							maxPersonId = personId;
					}
				}
			}

			int savedCount = 0;
			for (int i = 0; i < faceCount; i++)
			{
				int newPersonId = maxPersonId + i + 1;
				String^ faceFileName = galleryPath + "\\Person_" + newPersonId + ".jpg";

				std::string faceFilePath = context.marshal_as<std::string>(faceFileName);

				if (faceDetector->SaveFaceImage(i, faceFilePath))
				{
					savedCount++;
				}
			}

			lblStatus->Text = "STATUS: " + savedCount + " RECORD(S) ADDED TO DATABASE";
			lblStatus->ForeColor = Color::FromArgb(0, 255, 0);

			MessageBox::Show("OPERATION COMPLETE: " + savedCount + " TARGET(S) SAVED TO DATABASE",
				"SUCCESS", MessageBoxButtons::OK, MessageBoxIcon::Information);
			LoadGalleryFaces();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("SYSTEM ERROR: " + ex->Message, "ERROR",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			lblStatus->Text = "STATUS: SYSTEM ERROR";
			lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
		}
	}
}

System::Void GalleryForm::btnClearAll_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ galleryPath = "faces";
	if (!Directory::Exists(galleryPath) || Directory::GetFiles(galleryPath, "*.jpg")->Length == 0)
	{
		MessageBox::Show("DATABASE IS ALREADY EMPTY", "INFO", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}

	System::Windows::Forms::DialogResult result = MessageBox::Show(
		"CONFIRM: DELETE ALL RECORDS FROM DATABASE?",
		"SECURITY CONFIRMATION",
		MessageBoxButtons::YesNo,
		MessageBoxIcon::Warning);

	if (result == System::Windows::Forms::DialogResult::Yes)
	{
		try
		{
			// 1. ??????? UI ???????
			flowLayoutPanel1->Controls->Clear();

			// 2. ????? Garbage Collector ??????????????????????? File Lock
			System::GC::Collect();
			System::GC::WaitForPendingFinalizers();

			// 3. ?????????????
			array<String^>^ files = Directory::GetFiles(galleryPath, "*.jpg");
			for each(String ^ file in files)
			{
				File::Delete(file);
			}

			lblStatus->Text = "STATUS: DATABASE CLEARED";
			lblStatus->ForeColor = Color::FromArgb(255, 150, 50);

			MessageBox::Show("ALL TARGETS REMOVED FROM DATABASE", "SUCCESS",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			LoadGalleryFaces();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("SYSTEM ERROR: " + ex->Message, "ERROR",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

void GalleryForm::LoadGalleryFaces()
{
	flowLayoutPanel1->Controls->Clear();

	String^ galleryPath = "faces";
	if (!Directory::Exists(galleryPath))
	{
		Directory::CreateDirectory(galleryPath);
		lblTotalFaces->Text = "RECORDS: 0";
		lblStatus->Text = "STATUS: DATABASE EMPTY";
		lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
		return;
	}

	array<String^>^ faceFiles = Directory::GetFiles(galleryPath, "*.jpg");
	lblTotalFaces->Text = "RECORDS: " + faceFiles->Length;

	if (faceFiles->Length > 0)
	{
		lblStatus->Text = "STATUS: DATABASE READY - " + faceFiles->Length + " RECORD(S)";
		lblStatus->ForeColor = Color::FromArgb(0, 255, 0);
	}

	for each(String ^ filePath in faceFiles)
	{
		Panel^ facePanel = gcnew Panel();
		facePanel->Size = System::Drawing::Size(140, 220);
		facePanel->BackColor = Color::FromArgb(25, 25, 30);
		facePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		facePanel->Margin = System::Windows::Forms::Padding(10);

		PictureBox^ facePictureBox = gcnew PictureBox();
		facePictureBox->Size = System::Drawing::Size(120, 120);
		facePictureBox->Location = System::Drawing::Point(10, 10);
		facePictureBox->BackColor = System::Drawing::Color::Black;
		facePictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;

		try
		{
			FileStream^ fs = gcnew FileStream(filePath, FileMode::Open, FileAccess::Read);
			facePictureBox->Image = Image::FromStream(fs);
			fs->Close();
			delete fs;
		}
		catch (Exception^ ex)
		{
			facePictureBox->Image = nullptr;
		}

		Label^ faceLabel = gcnew Label();
		faceLabel->Text = Path::GetFileNameWithoutExtension(filePath);
		faceLabel->Location = System::Drawing::Point(5, 135);
		faceLabel->Size = System::Drawing::Size(130, 40);
		faceLabel->Font = (gcnew System::Drawing::Font(L"Consolas", 7, System::Drawing::FontStyle::Regular));
		faceLabel->ForeColor = Color::FromArgb(100, 255, 100);
		faceLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;

		Button^ deleteButton = gcnew Button();
		deleteButton->Text = L"[DELETE]";
		deleteButton->Location = System::Drawing::Point(20, 180);
		deleteButton->Size = System::Drawing::Size(100, 30);
		deleteButton->BackColor = Color::FromArgb(60, 20, 20);
		deleteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		deleteButton->FlatAppearance->BorderColor = Color::FromArgb(255, 50, 50);
		deleteButton->FlatAppearance->BorderSize = 2;
		deleteButton->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Bold));
		deleteButton->ForeColor = Color::FromArgb(255, 100, 100);
		deleteButton->Tag = filePath;
		deleteButton->Click += gcnew EventHandler(this, &GalleryForm::DeleteFace_Click);
		deleteButton->MouseEnter += gcnew EventHandler(this, &GalleryForm::DeleteButton_MouseEnter);
		deleteButton->MouseLeave += gcnew EventHandler(this, &GalleryForm::DeleteButton_MouseLeave);

		facePanel->Controls->Add(facePictureBox);
		facePanel->Controls->Add(faceLabel);
		facePanel->Controls->Add(deleteButton);

		flowLayoutPanel1->Controls->Add(facePanel);
	}
}