#pragma once
#include "FaceDetectionWrapper.h"
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <string>

namespace FDCProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class GalleryForm : public System::Windows::Forms::Form
	{
	public:
		GalleryForm(void)
		{
			InitializeComponent();
			faceDetector = new FaceDetectionWrapper();
			LoadGalleryFaces();
		}

	protected:
		~GalleryForm()
		{
			if (components)
			{
				delete components;
			}
			if (faceDetector)
			{
				delete faceDetector;
			}
		}

	private: System::Windows::Forms::Button^ btnUploadFullImage;
	private: System::Windows::Forms::Label^ lblTotalFaces;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private:
		System::ComponentModel::Container ^components;
		FaceDetectionWrapper* faceDetector;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnUploadFullImage = (gcnew System::Windows::Forms::Button());
			this->lblTotalFaces = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			this->btnUploadFullImage->Location = System::Drawing::Point(20, 20);
			this->btnUploadFullImage->Name = L"btnUploadFullImage";
			this->btnUploadFullImage->Size = System::Drawing::Size(160, 40);
			this->btnUploadFullImage->TabIndex = 0;
			this->btnUploadFullImage->Text = L"Upload Full Image";
			this->btnUploadFullImage->UseVisualStyleBackColor = true;
			this->btnUploadFullImage->Click += gcnew System::EventHandler(this, &GalleryForm::btnUploadFullImage_Click);
			this->lblTotalFaces->AutoSize = true;
			this->lblTotalFaces->Location = System::Drawing::Point(220, 32);
			this->lblTotalFaces->Name = L"lblTotalFaces";
			this->lblTotalFaces->Size = System::Drawing::Size(144, 16);
			this->lblTotalFaces->TabIndex = 1;
			this->lblTotalFaces->Text = L"Total faces in gallery: 0";
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel1->Location = System::Drawing::Point(20, 80);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(660, 480);
			this->flowLayoutPanel1->TabIndex = 2;
			this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png;*.bmp";
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(700, 580);
			this->Controls->Add(this->btnUploadFullImage);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->lblTotalFaces);
			this->Name = L"GalleryForm";
			this->Text = L"Gallery - Face Database";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void btnUploadFullImage_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				try
				{
					msclr::interop::marshal_context context;
					std::string imgPath = context.marshal_as<std::string>(openFileDialog1->FileName);
					
					if (!faceDetector->LoadImageFile(imgPath))
					{
						MessageBox::Show("Cannot load image");
						return;
					}

					std::string cascadePath = "C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";
					
					int faceCount = faceDetector->DetectFaces(cascadePath);

					if (faceCount == -1)
					{
						MessageBox::Show("Cannot load Haar Cascade file");
						return;
					}
					else if (faceCount == 0)
					{
						MessageBox::Show("No faces detected in image");
						return;
					}

					String^ galleryPath = "faces";
					if (!Directory::Exists(galleryPath))
					{
						Directory::CreateDirectory(galleryPath);
					}

					int savedCount = 0;
					for (int i = 0; i < faceCount; i++)
					{
						String^ faceFileName = galleryPath + "\\Person_" + 
							DateTime::Now.Ticks.ToString() + "_" + i + ".jpg";
						
						std::string faceFilePath = context.marshal_as<std::string>(faceFileName);
						
						if (faceDetector->SaveFaceImage(i, faceFilePath))
						{
							savedCount++;
						}
					}

					MessageBox::Show("Detected and saved " + savedCount + " face(s)");
					LoadGalleryFaces();
				}
				catch (Exception^ ex)
				{
					MessageBox::Show("Error: " + ex->Message);
				}
			}
		}

	private:
		void LoadGalleryFaces()
		{
			flowLayoutPanel1->Controls->Clear();

			String^ galleryPath = "faces";
			if (!Directory::Exists(galleryPath))
			{
				Directory::CreateDirectory(galleryPath);
				lblTotalFaces->Text = "Total faces in gallery: 0";
				return;
			}

			array<String^>^ faceFiles = Directory::GetFiles(galleryPath, "*.jpg");
			lblTotalFaces->Text = "Total faces in gallery: " + faceFiles->Length;

			for each (String^ filePath in faceFiles)
			{
				Panel^ facePanel = gcnew Panel();
				facePanel->Size = System::Drawing::Size(140, 200);
				facePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				facePanel->Margin = System::Windows::Forms::Padding(10);

				PictureBox^ facePictureBox = gcnew PictureBox();
				facePictureBox->Size = System::Drawing::Size(120, 120);
				facePictureBox->Location = System::Drawing::Point(10, 10);
				facePictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				facePictureBox->Image = Image::FromFile(filePath);

				Label^ faceLabel = gcnew Label();
				faceLabel->Text = Path::GetFileNameWithoutExtension(filePath);
				faceLabel->Location = System::Drawing::Point(10, 135);
				faceLabel->Size = System::Drawing::Size(120, 20);

				Button^ deleteButton = gcnew Button();
				deleteButton->Text = "Delete";
				deleteButton->Location = System::Drawing::Point(30, 160);
				deleteButton->Size = System::Drawing::Size(80, 30);
				deleteButton->Tag = filePath;
				deleteButton->Click += gcnew EventHandler(this, &GalleryForm::DeleteFace_Click);

				facePanel->Controls->Add(facePictureBox);
				facePanel->Controls->Add(faceLabel);
				facePanel->Controls->Add(deleteButton);

				flowLayoutPanel1->Controls->Add(facePanel);
			}
		}

		void DeleteFace_Click(Object^ sender, EventArgs^ e)
		{
			Button^ btn = safe_cast<Button^>(sender);
			String^ filePath = safe_cast<String^>(btn->Tag);

			auto result = MessageBox::Show("Delete this face?", "Confirm", 
				MessageBoxButtons::YesNo, MessageBoxIcon::Question);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				try
				{
					File::Delete(filePath);
					LoadGalleryFaces();
				}
				catch (Exception^ ex)
				{
					MessageBox::Show("Error deleting file: " + ex->Message);
				}
			}
		}
	};
}
