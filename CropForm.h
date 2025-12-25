#pragma once
#include "FaceDetectionWrapper.h"
#include <msclr/marshal_cppstd.h>
#include <vector>
#include <string>
#include <algorithm>

namespace FDCProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	ref class MyForm;

	public ref class CropForm : public System::Windows::Forms::Form
	{
	public:
		CropForm(MyForm^ mainForm)
		{
			InitializeComponent();
			this->mainForm = mainForm;
			currentFaceIndex = 0;
			faceDetector = new FaceDetectionWrapper();
		}

	protected:
		~CropForm()
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

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ btnUpload;
	private: System::Windows::Forms::Button^ btnDetect;
	private: System::Windows::Forms::Button^ btnPrev;
	private: System::Windows::Forms::Button^ btnNext;
	private: System::Windows::Forms::Button^ btnSearch;
	private: System::Windows::Forms::Label^ lblFaceInfo;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	public:
		MyForm^ mainForm;
		FaceDetectionWrapper* faceDetector;
		int currentFaceIndex;
		String^ currentImagePath;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->btnUpload = (gcnew System::Windows::Forms::Button());
			this->btnDetect = (gcnew System::Windows::Forms::Button());
			this->btnPrev = (gcnew System::Windows::Forms::Button());
			this->btnNext = (gcnew System::Windows::Forms::Button());
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->lblFaceInfo = (gcnew System::Windows::Forms::Label());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(50, 50);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(500, 380);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// btnUpload
			// 
			this->btnUpload->Location = System::Drawing::Point(50, 450);
			this->btnUpload->Name = L"btnUpload";
			this->btnUpload->Size = System::Drawing::Size(100, 35);
			this->btnUpload->TabIndex = 1;
			this->btnUpload->Text = L"Upload";
			this->btnUpload->UseVisualStyleBackColor = true;
			this->btnUpload->Click += gcnew System::EventHandler(this, &CropForm::btnUpload_Click);
			// 
			// btnDetect
			// 
			this->btnDetect->Location = System::Drawing::Point(170, 450);
			this->btnDetect->Name = L"btnDetect";
			this->btnDetect->Size = System::Drawing::Size(100, 35);
			this->btnDetect->TabIndex = 2;
			this->btnDetect->Text = L"Detect";
			this->btnDetect->UseVisualStyleBackColor = true;
			this->btnDetect->Click += gcnew System::EventHandler(this, &CropForm::btnDetect_Click);
			// 
			// btnPrev
			// 
			this->btnPrev->Enabled = false;
			this->btnPrev->Location = System::Drawing::Point(290, 450);
			this->btnPrev->Name = L"btnPrev";
			this->btnPrev->Size = System::Drawing::Size(50, 35);
			this->btnPrev->TabIndex = 3;
			this->btnPrev->Text = L"<";
			this->btnPrev->UseVisualStyleBackColor = true;
			this->btnPrev->Click += gcnew System::EventHandler(this, &CropForm::btnPrev_Click);
			// 
			// btnNext
			// 
			this->btnNext->Enabled = false;
			this->btnNext->Location = System::Drawing::Point(360, 450);
			this->btnNext->Name = L"btnNext";
			this->btnNext->Size = System::Drawing::Size(50, 35);
			this->btnNext->TabIndex = 4;
			this->btnNext->Text = L">";
			this->btnNext->UseVisualStyleBackColor = true;
			this->btnNext->Click += gcnew System::EventHandler(this, &CropForm::btnNext_Click);
			// 
			// btnSearch
			// 
			this->btnSearch->Enabled = false;
			this->btnSearch->Location = System::Drawing::Point(430, 450);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(120, 35);
			this->btnSearch->TabIndex = 5;
			this->btnSearch->Text = L"Search";
			this->btnSearch->UseVisualStyleBackColor = true;
			this->btnSearch->Click += gcnew System::EventHandler(this, &CropForm::btnSearch_Click);
			// 
			// lblFaceInfo
			// 
			this->lblFaceInfo->AutoSize = true;
			this->lblFaceInfo->Location = System::Drawing::Point(250, 500);
			this->lblFaceInfo->Name = L"lblFaceInfo";
			this->lblFaceInfo->Size = System::Drawing::Size(72, 16);
			this->lblFaceInfo->TabIndex = 6;
			this->lblFaceInfo->Text = L"Face 0 of 0";
			// 
			// lblTitle
			// 
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Bold));
			this->lblTitle->Location = System::Drawing::Point(226, 9);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(160, 29);
			this->lblTitle->TabIndex = 7;
			this->lblTitle->Text = L"Search Face";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png;*.bmp";
			// 
			// CropForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 540);
			this->Controls->Add(this->lblTitle);
			this->Controls->Add(this->lblFaceInfo);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->btnNext);
			this->Controls->Add(this->btnPrev);
			this->Controls->Add(this->btnDetect);
			this->Controls->Add(this->btnUpload);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"CropForm";
			this->Text = L"Search Person";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: 
		System::Void btnUpload_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				currentImagePath = openFileDialog1->FileName;
				pictureBox1->Image = Image::FromFile(currentImagePath);
				currentFaceIndex = 0;
				UpdateFaceNavigation();
			}
		}

	private: 
		System::Void btnDetect_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (currentImagePath == nullptr) return;

			try
			{
				msclr::interop::marshal_context context;
				std::string imgPath = context.marshal_as<std::string>(currentImagePath);
				
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
					MessageBox::Show("No faces detected");
					return;
				}

				currentFaceIndex = 0;
				ShowCurrentFace();
				UpdateFaceNavigation();
				MessageBox::Show("Detected " + faceCount + " face(s)");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Error: " + ex->Message);
			}
		}

	private: 
		System::Void btnPrev_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (currentFaceIndex > 0)
			{
				currentFaceIndex--;
				ShowCurrentFace();
				UpdateFaceNavigation();
			}
		}

	private: 
		System::Void btnNext_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			if (currentFaceIndex < faceDetector->GetFaceCount() - 1)
			{
				currentFaceIndex++;
				ShowCurrentFace();
				UpdateFaceNavigation();
			}
		}

	public: 
		System::Void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);

	public:
		void ShowCurrentFace()
		{
			int faceCount = faceDetector->GetFaceCount();
			if (faceCount == 0) return;

			std::vector<uchar> buffer;
			if (faceDetector->GetImageWithRectangle(currentFaceIndex, buffer))
			{
				array<unsigned char>^ data = gcnew array<unsigned char>(buffer.size());
				System::Runtime::InteropServices::Marshal::Copy((IntPtr)buffer.data(), data, 0, buffer.size());
				
				System::IO::MemoryStream^ ms = gcnew System::IO::MemoryStream(data);
				pictureBox1->Image = Image::FromStream(ms);
			}
		}

		void UpdateFaceNavigation()
		{
			int faceCount = faceDetector->GetFaceCount();
			lblFaceInfo->Text = "Face " + (currentFaceIndex + 1) + " of " + faceCount;
			
			btnPrev->Enabled = (currentFaceIndex > 0);
			btnNext->Enabled = (currentFaceIndex < faceCount - 1);
			btnSearch->Enabled = (faceCount > 0);
		}

		void FindTopMatches(String^ queryFacePath, array<String^>^% matches, array<double>^% scores)
		{
			String^ galleryPath = "faces";
			if (!Directory::Exists(galleryPath))
			{
				Directory::CreateDirectory(galleryPath);
			}

			array<String^>^ faceFiles = Directory::GetFiles(galleryPath, "*.jpg");
			
			if (faceFiles->Length == 0)
			{
				MessageBox::Show("No faces in gallery");
				return;
			}

			System::Collections::Generic::List<Tuple<String^, double>^>^ results = 
				gcnew System::Collections::Generic::List<Tuple<String^, double>^>();

			msclr::interop::marshal_context context;
			std::string queryPath = context.marshal_as<std::string>(queryFacePath);

			for each (String^ filePath in faceFiles)
			{
				std::string galleryFilePath = context.marshal_as<std::string>(filePath);
				
				double distance = faceDetector->ComputeDistance(queryPath, galleryFilePath);
				if (distance >= 0)
				{
					results->Add(gcnew Tuple<String^, double>(filePath, distance));
				}
			}

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
				for (int i = 0; i < matchCount; i++)
				{
					matches[i] = results[i]->Item1;
					scores[i] = results[i]->Item2;
				}
			}
		}
	};
}
