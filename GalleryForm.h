#pragma once

// Forward declare instead of including FaceDetectionWrapper.h
class FaceDetectionWrapper;

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
			ApplyTheme();

			InitializeFaceDetector();

			// Start timers
			recTimer = gcnew System::Windows::Forms::Timer();
			recTimer->Interval = 500;
			recTimer->Tick += gcnew EventHandler(this, &GalleryForm::RecTimer_Tick);
			recTimer->Start();

			timestampTimer = gcnew System::Windows::Forms::Timer();
			timestampTimer->Interval = 1000;
			timestampTimer->Tick += gcnew EventHandler(this, &GalleryForm::TimestampTimer_Tick);
			timestampTimer->Start();
			UpdateTimestamp();

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

	private: System::Windows::Forms::Button^ btnUploadFullImage;
	private: System::Windows::Forms::Label^ lblTotalFaces;
	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::Label^ lblRecording;
	private: System::Windows::Forms::Label^ lblTimestamp;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Timer^ recTimer;
	private: System::Windows::Forms::Timer^ timestampTimer;
	private: bool recBlinkState;

	private:
		System::ComponentModel::Container^ components;
		FaceDetectionWrapper* faceDetector;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->btnUploadFullImage = (gcnew System::Windows::Forms::Button());
			this->lblTotalFaces = (gcnew System::Windows::Forms::Label());
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->lblRecording = (gcnew System::Windows::Forms::Label());
			this->lblTimestamp = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();

			// lblTitle
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Consolas", 16, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = Color::FromArgb(0, 255, 0);
			this->lblTitle->Location = System::Drawing::Point(180, 15);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(350, 26);
			this->lblTitle->TabIndex = 4;
			this->lblTitle->Text = L"???? DATABASE ARCHIVE ????";

			// lblRecording
			this->lblRecording->AutoSize = true;
			this->lblRecording->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblRecording->ForeColor = Color::FromArgb(255, 0, 0);
			this->lblRecording->Location = System::Drawing::Point(15, 50);
			this->lblRecording->Name = L"lblRecording";
			this->lblRecording->Size = System::Drawing::Size(70, 14);
			this->lblRecording->TabIndex = 5;
			this->lblRecording->Text = L"? REC";

			// lblTimestamp
			this->lblTimestamp->AutoSize = true;
			this->lblTimestamp->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular));
			this->lblTimestamp->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblTimestamp->Location = System::Drawing::Point(505, 52);
			this->lblTimestamp->Name = L"lblTimestamp";
			this->lblTimestamp->Size = System::Drawing::Size(180, 14);
			this->lblTimestamp->TabIndex = 6;
			this->lblTimestamp->Text = L"2025-01-01 00:00:00";

			// lblStatus
			this->lblStatus->AutoSize = true;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblStatus->Location = System::Drawing::Point(15, 75);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(200, 14);
			this->lblStatus->TabIndex = 7;
			this->lblStatus->Text = L"STATUS: DATABASE READY";

			// btnUploadFullImage
			this->btnUploadFullImage->BackColor = Color::FromArgb(30, 30, 40);
			this->btnUploadFullImage->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnUploadFullImage->FlatAppearance->BorderColor = Color::FromArgb(39, 174, 96);
			this->btnUploadFullImage->FlatAppearance->BorderSize = 2;
			this->btnUploadFullImage->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->btnUploadFullImage->ForeColor = Color::FromArgb(100, 255, 150);
			this->btnUploadFullImage->Location = System::Drawing::Point(20, 100);
			this->btnUploadFullImage->Name = L"btnUploadFullImage";
			this->btnUploadFullImage->Size = System::Drawing::Size(180, 40);
			this->btnUploadFullImage->TabIndex = 0;
			this->btnUploadFullImage->Text = L"[ADD TO DATABASE]";
			this->btnUploadFullImage->UseVisualStyleBackColor = false;
			this->btnUploadFullImage->Click += gcnew System::EventHandler(this, &GalleryForm::btnUploadFullImage_Click);
			this->btnUploadFullImage->MouseEnter += gcnew System::EventHandler(this, &GalleryForm::Button_MouseEnter);
			this->btnUploadFullImage->MouseLeave += gcnew System::EventHandler(this, &GalleryForm::Button_MouseLeave);

			// lblTotalFaces
			this->lblTotalFaces->AutoSize = true;
			this->lblTotalFaces->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->lblTotalFaces->ForeColor = Color::FromArgb(255, 200, 0);
			this->lblTotalFaces->Location = System::Drawing::Point(230, 113);
			this->lblTotalFaces->Name = L"lblTotalFaces";
			this->lblTotalFaces->Size = System::Drawing::Size(200, 17);
			this->lblTotalFaces->TabIndex = 1;
			this->lblTotalFaces->Text = L"RECORDS: 0";

			// flowLayoutPanel1
			this->flowLayoutPanel1->AutoScroll = true;
			this->flowLayoutPanel1->BackColor = Color::FromArgb(20, 20, 25);
			this->flowLayoutPanel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->flowLayoutPanel1->Location = System::Drawing::Point(20, 160);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(660, 400);
			this->flowLayoutPanel1->TabIndex = 2;

			// openFileDialog1
			this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png;*.bmp";

			// GalleryForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = Color::FromArgb(15, 15, 20);
			this->ClientSize = System::Drawing::Size(700, 580);
			this->Controls->Add(this->lblTimestamp);
			this->Controls->Add(this->lblRecording);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->lblTitle);
			this->Controls->Add(this->btnUploadFullImage);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->lblTotalFaces);
			this->Name = L"GalleryForm";
			this->Text = L"SURVEILLANCE - DATABASE ARCHIVE";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private:
		void ApplyTheme()
		{
			// Form theme
			this->BackColor = Color::FromArgb(15, 15, 20);

			// Labels
			lblTitle->ForeColor = Color::FromArgb(0, 255, 0);
			lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			lblRecording->ForeColor = Color::FromArgb(255, 0, 0);
			lblTimestamp->ForeColor = Color::FromArgb(100, 255, 100);
			lblTotalFaces->ForeColor = Color::FromArgb(255, 200, 0);

			// Button
			btnUploadFullImage->BackColor = Color::FromArgb(30, 30, 40);
			btnUploadFullImage->ForeColor = Color::FromArgb(100, 255, 150);
			btnUploadFullImage->FlatAppearance->BorderColor = Color::FromArgb(39, 174, 96);

			// FlowLayoutPanel
			flowLayoutPanel1->BackColor = Color::FromArgb(20, 20, 25);
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

		// Delete button hover effects
		System::Void DeleteButton_MouseEnter(Object^ sender, EventArgs^ e)
		{
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(60, 20, 20);
		}

		System::Void DeleteButton_MouseLeave(Object^ sender, EventArgs^ e)
		{
			Button^ btn = safe_cast<Button^>(sender);
			btn->BackColor = Color::FromArgb(30, 30, 40);
		}

		void DeleteFace_Click(Object^ sender, EventArgs^ e)
		{
			Button^ btn = safe_cast<Button^>(sender);
			String^ filePath = safe_cast<String^>(btn->Tag);

			auto result = MessageBox::Show(
				"CONFIRM: DELETE THIS RECORD FROM DATABASE?",
				"SECURITY CONFIRMATION",
				MessageBoxButtons::YesNo,
				MessageBoxIcon::Warning);

			if (result == System::Windows::Forms::DialogResult::Yes)
			{
				try
				{
					Panel^ parentPanel = safe_cast<Panel^>(btn->Parent);
					for each(Control ^ ctrl in parentPanel->Controls)
					{
						PictureBox^ picBox = dynamic_cast<PictureBox^>(ctrl);
						if (picBox != nullptr && picBox->Image != nullptr)
						{
							delete picBox->Image;
							picBox->Image = nullptr;
						}
					}

					System::GC::Collect();
					System::GC::WaitForPendingFinalizers();

					File::Delete(filePath);
					lblStatus->Text = "STATUS: RECORD DELETED";
					lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
					LoadGalleryFaces();
				}
				catch (Exception^ ex)
				{
					MessageBox::Show("SYSTEM ERROR: CANNOT DELETE FILE - " + ex->Message,
						"ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
					lblStatus->Text = "STATUS: DELETE FAILED";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
				}
			}
		}

	private:
		System::Void btnUploadFullImage_Click(System::Object^ sender, System::EventArgs^ e);

	private:
		void InitializeFaceDetector();
		void LoadGalleryFaces();
	};
}