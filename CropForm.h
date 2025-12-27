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

			// Apply CCTV theme
			this->BackColor = Color::FromArgb(15, 15, 20);

			// Start timers
			recTimer = gcnew System::Windows::Forms::Timer();
			recTimer->Interval = 500;
			recTimer->Tick += gcnew EventHandler(this, &CropForm::RecTimer_Tick);
			recTimer->Start();

			timestampTimer = gcnew System::Windows::Forms::Timer();
			timestampTimer->Interval = 1000;
			timestampTimer->Tick += gcnew EventHandler(this, &CropForm::TimestampTimer_Tick);
			timestampTimer->Start();
			UpdateTimestamp();
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
			if (recTimer != nullptr)
			{
				recTimer->Stop();
				delete recTimer;
			}
			if (timestampTimer != nullptr)
			{
				timestampTimer->Stop();
				delete timestampTimer;
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
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::Label^ lblRecording;
	private: System::Windows::Forms::Label^ lblTimestamp;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Timer^ recTimer;
	private: System::Windows::Forms::Timer^ timestampTimer;
	private: bool recBlinkState;

	public:
		MyForm^ mainForm;
		FaceDetectionWrapper* faceDetector;
		int currentFaceIndex;
		String^ currentImagePath;

	private:
		System::ComponentModel::Container^ components;

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
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->lblRecording = (gcnew System::Windows::Forms::Label());
			this->lblTimestamp = (gcnew System::Windows::Forms::Label());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// lblTitle
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Consolas", 16, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = Color::FromArgb(0, 255, 0);
			this->lblTitle->Location = System::Drawing::Point(150, 15);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(350, 26);
			this->lblTitle->TabIndex = 7;
			this->lblTitle->Text = L"╔═══ TARGET IDENTIFICATION ═══╗";

			// lblRecording
			this->lblRecording->AutoSize = true;
			this->lblRecording->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblRecording->ForeColor = Color::FromArgb(255, 0, 0);
			this->lblRecording->Location = System::Drawing::Point(15, 50);
			this->lblRecording->Name = L"lblRecording";
			this->lblRecording->Size = System::Drawing::Size(70, 14);
			this->lblRecording->TabIndex = 8;
			this->lblRecording->Text = L"● REC";

			// lblTimestamp
			this->lblTimestamp->AutoSize = true;
			this->lblTimestamp->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular));
			this->lblTimestamp->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblTimestamp->Location = System::Drawing::Point(410, 52);
			this->lblTimestamp->Name = L"lblTimestamp";
			this->lblTimestamp->Size = System::Drawing::Size(180, 14);
			this->lblTimestamp->TabIndex = 9;
			this->lblTimestamp->Text = L"2025-01-01 00:00:00";

			// lblStatus
			this->lblStatus->AutoSize = true;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblStatus->Location = System::Drawing::Point(15, 75);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(210, 14);
			this->lblStatus->TabIndex = 10;
			this->lblStatus->Text = L"STATUS: READY FOR INPUT";

			// pictureBox1
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(50, 100);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(500, 380);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew PaintEventHandler(this, &CropForm::PictureBox_Paint);

			// btnUpload
			this->btnUpload->BackColor = Color::FromArgb(30, 30, 40);
			this->btnUpload->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnUpload->FlatAppearance->BorderColor = Color::FromArgb(155, 89, 182);
			this->btnUpload->FlatAppearance->BorderSize = 2;
			this->btnUpload->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->btnUpload->ForeColor = Color::FromArgb(200, 150, 255);
			this->btnUpload->Location = System::Drawing::Point(50, 495);
			this->btnUpload->Name = L"btnUpload";
			this->btnUpload->Size = System::Drawing::Size(100, 35);
			this->btnUpload->TabIndex = 1;
			this->btnUpload->Text = L"[LOAD]";
			this->btnUpload->UseVisualStyleBackColor = false;
			this->btnUpload->Click += gcnew System::EventHandler(this, &CropForm::btnUpload_Click);
			this->btnUpload->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
			this->btnUpload->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);

			// btnDetect
			this->btnDetect->BackColor = Color::FromArgb(30, 30, 40);
			this->btnDetect->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnDetect->FlatAppearance->BorderColor = Color::FromArgb(52, 152, 219);
			this->btnDetect->FlatAppearance->BorderSize = 2;
			this->btnDetect->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->btnDetect->ForeColor = Color::FromArgb(100, 200, 255);
			this->btnDetect->Location = System::Drawing::Point(170, 495);
			this->btnDetect->Name = L"btnDetect";
			this->btnDetect->Size = System::Drawing::Size(100, 35);
			this->btnDetect->TabIndex = 2;
			this->btnDetect->Text = L"[SCAN]";
			this->btnDetect->UseVisualStyleBackColor = false;
			this->btnDetect->Click += gcnew System::EventHandler(this, &CropForm::btnDetect_Click);
			this->btnDetect->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
			this->btnDetect->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);

			// btnPrev
			this->btnPrev->BackColor = Color::FromArgb(30, 30, 40);
			this->btnPrev->Enabled = false;
			this->btnPrev->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnPrev->FlatAppearance->BorderColor = Color::FromArgb(100, 255, 100);
			this->btnPrev->FlatAppearance->BorderSize = 2;
			this->btnPrev->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Bold));
			this->btnPrev->ForeColor = Color::FromArgb(100, 255, 100);
			this->btnPrev->Location = System::Drawing::Point(290, 495);
			this->btnPrev->Name = L"btnPrev";
			this->btnPrev->Size = System::Drawing::Size(50, 35);
			this->btnPrev->TabIndex = 3;
			this->btnPrev->Text = L"◄";
			this->btnPrev->UseVisualStyleBackColor = false;
			this->btnPrev->Click += gcnew System::EventHandler(this, &CropForm::btnPrev_Click);
			this->btnPrev->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
			this->btnPrev->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);

			// btnNext
			this->btnNext->BackColor = Color::FromArgb(30, 30, 40);
			this->btnNext->Enabled = false;
			this->btnNext->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnNext->FlatAppearance->BorderColor = Color::FromArgb(100, 255, 100);
			this->btnNext->FlatAppearance->BorderSize = 2;
			this->btnNext->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Bold));
			this->btnNext->ForeColor = Color::FromArgb(100, 255, 100);
			this->btnNext->Location = System::Drawing::Point(360, 495);
			this->btnNext->Name = L"btnNext";
			this->btnNext->Size = System::Drawing::Size(50, 35);
			this->btnNext->TabIndex = 4;
			this->btnNext->Text = L"►";
			this->btnNext->UseVisualStyleBackColor = false;
			this->btnNext->Click += gcnew System::EventHandler(this, &CropForm::btnNext_Click);
			this->btnNext->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
			this->btnNext->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);

			// btnSearch
			this->btnSearch->BackColor = Color::FromArgb(30, 30, 40);
			this->btnSearch->Enabled = false;
			this->btnSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSearch->FlatAppearance->BorderColor = Color::FromArgb(255, 50, 50);
			this->btnSearch->FlatAppearance->BorderSize = 2;
			this->btnSearch->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->btnSearch->ForeColor = Color::FromArgb(255, 100, 100);
			this->btnSearch->Location = System::Drawing::Point(430, 495);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(120, 35);
			this->btnSearch->TabIndex = 5;
			this->btnSearch->Text = L"[IDENTIFY]";
			this->btnSearch->UseVisualStyleBackColor = false;
			this->btnSearch->Click += gcnew System::EventHandler(this, &CropForm::btnSearch_Click);
			this->btnSearch->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
			this->btnSearch->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);

			// lblFaceInfo
			this->lblFaceInfo->AutoSize = true;
			this->lblFaceInfo->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->lblFaceInfo->ForeColor = Color::FromArgb(255, 200, 0);
			this->lblFaceInfo->Location = System::Drawing::Point(220, 545);
			this->lblFaceInfo->Name = L"lblFaceInfo";
			this->lblFaceInfo->Size = System::Drawing::Size(160, 17);
			this->lblFaceInfo->TabIndex = 6;
			this->lblFaceInfo->Text = L"TARGET: 0 / 0";

			// openFileDialog1
			this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png;*.bmp";

			// CropForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = Color::FromArgb(15, 15, 20);
			this->ClientSize = System::Drawing::Size(600, 580);
			this->Controls->Add(this->lblTimestamp);
			this->Controls->Add(this->lblRecording);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->lblTitle);
			this->Controls->Add(this->lblFaceInfo);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->btnNext);
			this->Controls->Add(this->btnPrev);
			this->Controls->Add(this->btnDetect);
			this->Controls->Add(this->btnUpload);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"CropForm";
			this->Text = L"SURVEILLANCE - TARGET IDENTIFICATION";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private:
		// Draw corner brackets on PictureBox
		System::Void PictureBox_Paint(Object^ sender, PaintEventArgs^ e)
		{
			PictureBox^ pb = safe_cast<PictureBox^>(sender);
			Graphics^ g = e->Graphics;
			Pen^ greenPen = gcnew Pen(Color::FromArgb(0, 255, 0), 3);

			int cornerSize = 20;
			int w = pb->Width - 1;
			int h = pb->Height - 1;

			// Top-left corner
			g->DrawLine(greenPen, 0, 0, cornerSize, 0);
			g->DrawLine(greenPen, 0, 0, 0, cornerSize);

			// Top-right corner
			g->DrawLine(greenPen, w - cornerSize, 0, w, 0);
			g->DrawLine(greenPen, w, 0, w, cornerSize);

			// Bottom-left corner
			g->DrawLine(greenPen, 0, h - cornerSize, 0, h);
			g->DrawLine(greenPen, 0, h, cornerSize, h);

			// Bottom-right corner
			g->DrawLine(greenPen, w - cornerSize, h, w, h);
			g->DrawLine(greenPen, w, h - cornerSize, w, h);

			delete greenPen;
		}

		// Recording indicator blink
		System::Void RecTimer_Tick(Object^ sender, EventArgs^ e)
		{
			recBlinkState = !recBlinkState;
			lblRecording->Visible = recBlinkState;
		}

		// Update timestamp
		System::Void TimestampTimer_Tick(Object^ sender, EventArgs^ e)
		{
			UpdateTimestamp();
		}

		void UpdateTimestamp()
		{
			DateTime now = DateTime::Now;
			lblTimestamp->Text = now.ToString("yyyy-MM-dd HH:mm:ss");
		}

		// Button hover effects
		System::Void Button_MouseEnter(Object^ sender, EventArgs^ e)
		{
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(45, 45, 55);
		}

		System::Void Button_MouseLeave(Object^ sender, EventArgs^ e)
		{
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(30, 30, 40);
		}

	private:
		System::Void btnUpload_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				currentImagePath = openFileDialog1->FileName;
				pictureBox1->Image = Image::FromFile(currentImagePath);
				pictureBox1->Refresh();
				currentFaceIndex = 0;
				UpdateFaceNavigation();

				lblStatus->Text = "STATUS: IMAGE LOADED";
				lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			}
		}

	private:
		System::Void btnDetect_Click(System::Object^ sender, System::EventArgs^ e)
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
				pictureBox1->Refresh();
			}
		}

		void UpdateFaceNavigation()
		{
			int faceCount = faceDetector->GetFaceCount();
			lblFaceInfo->Text = "TARGET: " + (currentFaceIndex + 1) + " / " + faceCount;

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
				MessageBox::Show("ALERT: DATABASE EMPTY - NO RECORDS FOUND", "NO DATA",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			System::Collections::Generic::List<Tuple<String^, double>^>^ results =
				gcnew System::Collections::Generic::List<Tuple<String^, double>^>();

			msclr::interop::marshal_context context;
			std::string queryPath = context.marshal_as<std::string>(queryFacePath);

			for each (String ^ filePath in faceFiles)
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