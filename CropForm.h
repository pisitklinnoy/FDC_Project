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
				ApplyTheme();
				
				this->mainForm = mainForm;
				currentFaceIndex = 0;
				InitializeFaceDetector();

				// Initialize manual crop mode
				isManualCropMode = false;
				isDrawing = false;
				cropRectangle = System::Drawing::Rectangle(0, 0, 0, 0);
				originalImage = nullptr;

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
		private: System::Windows::Forms::Button^ btnManualCrop;
		private: System::Windows::Forms::Label^ lblFaceInfo;
		private: System::Windows::Forms::Label^ lblTitle;
		private: System::Windows::Forms::Label^ lblStatus;
		private: System::Windows::Forms::Label^ lblRecording;
		private: System::Windows::Forms::Label^ lblTimestamp;
		private: System::Windows::Forms::Label^ lblManualCropHelp;
		private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		private: System::Windows::Forms::Timer^ recTimer;
		private: System::Windows::Forms::Timer^ timestampTimer;
		private: bool recBlinkState;

		// Manual crop variables
		private: bool isManualCropMode;
		private: bool isDrawing;
		private: Point cropStartPoint;
		private: Point cropEndPoint;
		private: System::Drawing::Rectangle cropRectangle;
		private: Image^ originalImage;

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
				this->btnManualCrop = (gcnew System::Windows::Forms::Button());
				this->lblFaceInfo = (gcnew System::Windows::Forms::Label());
				this->lblTitle = (gcnew System::Windows::Forms::Label());
				this->lblStatus = (gcnew System::Windows::Forms::Label());
				this->lblRecording = (gcnew System::Windows::Forms::Label());
				this->lblTimestamp = (gcnew System::Windows::Forms::Label());
				this->lblManualCropHelp = (gcnew System::Windows::Forms::Label());
				this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				this->SuspendLayout();
				this->lblTitle->AutoSize = true;
				this->lblTitle->Font = (gcnew System::Drawing::Font(L"Consolas", 16, System::Drawing::FontStyle::Bold));
				this->lblTitle->ForeColor = Color::FromArgb(0, 255, 0);
				this->lblTitle->Location = System::Drawing::Point(150, 15);
				this->lblTitle->Name = L"lblTitle";
				this->lblTitle->Size = System::Drawing::Size(350, 26);
				this->lblTitle->TabIndex = 7;
				this->lblTitle->Text = L"╔═══ TARGET IDENTIFICATION ═══╗";
				this->lblRecording->AutoSize = true;
				this->lblRecording->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
				this->lblRecording->ForeColor = Color::FromArgb(255, 0, 0);
				this->lblRecording->Location = System::Drawing::Point(15, 50);
				this->lblRecording->Name = L"lblRecording";
				this->lblRecording->Size = System::Drawing::Size(70, 14);
				this->lblRecording->TabIndex = 8;
				this->lblRecording->Text = L"● REC";
				this->lblTimestamp->AutoSize = true;
				this->lblTimestamp->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular));
				this->lblTimestamp->ForeColor = Color::FromArgb(100, 255, 100);
				this->lblTimestamp->Location = System::Drawing::Point(410, 52);
				this->lblTimestamp->Name = L"lblTimestamp";
				this->lblTimestamp->Size = System::Drawing::Size(180, 14);
				this->lblTimestamp->TabIndex = 9;
				this->lblTimestamp->Text = L"2025-01-01 00:00:00";
				this->lblStatus->AutoSize = true;
				this->lblStatus->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
				this->lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
				this->lblStatus->Location = System::Drawing::Point(15, 75);
				this->lblStatus->Name = L"lblStatus";
				this->lblStatus->Size = System::Drawing::Size(210, 14);
				this->lblStatus->TabIndex = 10;
				this->lblStatus->Text = L"STATUS: READY FOR INPUT";
				
				// lblManualCropHelp
				this->lblManualCropHelp->AutoSize = true;
				this->lblManualCropHelp->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Italic));
				this->lblManualCropHelp->ForeColor = Color::FromArgb(255, 200, 0);
				this->lblManualCropHelp->Location = System::Drawing::Point(50, 485);
				this->lblManualCropHelp->Name = L"lblManualCropHelp";
				this->lblManualCropHelp->Size = System::Drawing::Size(400, 13);
				this->lblManualCropHelp->TabIndex = 14;
				this->lblManualCropHelp->Text = L"";
				this->lblManualCropHelp->Visible = false;
	
				this->pictureBox1->BackColor = System::Drawing::Color::Black;
				this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				this->pictureBox1->Location = System::Drawing::Point(50, 100);
				this->pictureBox1->Name = L"pictureBox1";
				this->pictureBox1->Size = System::Drawing::Size(500, 380);
				this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				this->pictureBox1->TabIndex = 0;
				this->pictureBox1->TabStop = false;
				this->pictureBox1->Paint += gcnew PaintEventHandler(this, &CropForm::PictureBox_Paint);
				this->pictureBox1->MouseDown += gcnew MouseEventHandler(this, &CropForm::PictureBox1_MouseDown);
				this->pictureBox1->MouseMove += gcnew MouseEventHandler(this, &CropForm::PictureBox1_MouseMove);
				this->pictureBox1->MouseUp += gcnew MouseEventHandler(this, &CropForm::PictureBox1_MouseUp);
	
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
				this->btnDetect->BackColor = Color::FromArgb(30, 30, 40);
				this->btnDetect->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btnDetect->FlatAppearance->BorderColor = Color::FromArgb(52, 152, 219);
				this->btnDetect->FlatAppearance->BorderSize = 2;
				this->btnDetect->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
				this->btnDetect->ForeColor = Color::FromArgb(100, 200, 255);
				this->btnDetect->Location = System::Drawing::Point(160, 495);
				this->btnDetect->Name = L"btnDetect";
				this->btnDetect->Size = System::Drawing::Size(100, 35);
				this->btnDetect->TabIndex = 2;
				this->btnDetect->Text = L"[SCAN]";
				this->btnDetect->UseVisualStyleBackColor = false;
				this->btnDetect->Click += gcnew System::EventHandler(this, &CropForm::btnDetect_Click);
				this->btnDetect->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
				this->btnDetect->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);
				
				// btnManualCrop
				this->btnManualCrop->BackColor = Color::FromArgb(30, 30, 40);
				this->btnManualCrop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btnManualCrop->FlatAppearance->BorderColor = Color::FromArgb(255, 150, 0);
				this->btnManualCrop->FlatAppearance->BorderSize = 2;
				this->btnManualCrop->Font = (gcnew System::Drawing::Font(L"Consolas", 8, System::Drawing::FontStyle::Bold));
				this->btnManualCrop->ForeColor = Color::FromArgb(255, 200, 100);
				this->btnManualCrop->Location = System::Drawing::Point(270, 495);
				this->btnManualCrop->Name = L"btnManualCrop";
				this->btnManualCrop->Size = System::Drawing::Size(100, 35);
				this->btnManualCrop->TabIndex = 11;
				this->btnManualCrop->Text = L"[M-CROP]";
				this->btnManualCrop->UseVisualStyleBackColor = false;
				this->btnManualCrop->Click += gcnew System::EventHandler(this, &CropForm::btnManualCrop_Click);
				this->btnManualCrop->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
				this->btnManualCrop->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);
				
				this->btnPrev->BackColor = Color::FromArgb(30, 30, 40);
				this->btnPrev->Enabled = false;
				this->btnPrev->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btnPrev->FlatAppearance->BorderColor = Color::FromArgb(100, 255, 100);
				this->btnPrev->FlatAppearance->BorderSize = 2;
				this->btnPrev->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Bold));
				this->btnPrev->ForeColor = Color::FromArgb(100, 255, 100);
				this->btnPrev->Location = System::Drawing::Point(380, 495);
				this->btnPrev->Name = L"btnPrev";
				this->btnPrev->Size = System::Drawing::Size(50, 35);
				this->btnPrev->TabIndex = 3;
				this->btnPrev->Text = L"◄";
				this->btnPrev->UseVisualStyleBackColor = false;
				this->btnPrev->Click += gcnew System::EventHandler(this, &CropForm::btnPrev_Click);
				this->btnPrev->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
				this->btnPrev->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);
				this->btnNext->BackColor = Color::FromArgb(30, 30, 40);
				this->btnNext->Enabled = false;
				this->btnNext->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btnNext->FlatAppearance->BorderColor = Color::FromArgb(100, 255, 100);
				this->btnNext->FlatAppearance->BorderSize = 2;
				this->btnNext->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Bold));
				this->btnNext->ForeColor = Color::FromArgb(100, 255, 100);
				this->btnNext->Location = System::Drawing::Point(440, 495);
				this->btnNext->Name = L"btnNext";
				this->btnNext->Size = System::Drawing::Size(50, 35);
				this->btnNext->TabIndex = 4;
				this->btnNext->Text = L"►";
				this->btnNext->UseVisualStyleBackColor = false;
				this->btnNext->Click += gcnew System::EventHandler(this, &CropForm::btnNext_Click);
				this->btnNext->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
				this->btnNext->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);
				this->btnSearch->BackColor = Color::FromArgb(30, 30, 40);
				this->btnSearch->Enabled = false;
				this->btnSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				this->btnSearch->FlatAppearance->BorderColor = Color::FromArgb(255, 50, 50);
				this->btnSearch->FlatAppearance->BorderSize = 2;
				this->btnSearch->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
				this->btnSearch->ForeColor = Color::FromArgb(255, 100, 100);
				this->btnSearch->Location = System::Drawing::Point(500, 495);
				this->btnSearch->Name = L"btnSearch";
				this->btnSearch->Size = System::Drawing::Size(120, 35);
				this->btnSearch->TabIndex = 5;
				this->btnSearch->Text = L"[SELECT]";
				this->btnSearch->UseVisualStyleBackColor = false;
				this->btnSearch->Click += gcnew System::EventHandler(this, &CropForm::btnSearch_Click);
				this->btnSearch->MouseEnter += gcnew System::EventHandler(this, &CropForm::Button_MouseEnter);
				this->btnSearch->MouseLeave += gcnew System::EventHandler(this, &CropForm::Button_MouseLeave);
				this->lblFaceInfo->AutoSize = true;
				this->lblFaceInfo->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
				this->lblFaceInfo->ForeColor = Color::FromArgb(255, 200, 0);
				this->lblFaceInfo->Location = System::Drawing::Point(250, 545);
				this->lblFaceInfo->Name = L"lblFaceInfo";
				this->lblFaceInfo->Size = System::Drawing::Size(160, 17);
				this->lblFaceInfo->TabIndex = 6;
				this->lblFaceInfo->Text = L"TARGET: 0 / 0";
				this->openFileDialog1->Filter = L"Image Files|*.jpg;*.jpeg;*.png;*.bmp";
				this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->BackColor = Color::FromArgb(15, 15, 20);
				this->ClientSize = System::Drawing::Size(650, 580);
				this->Controls->Add(this->lblManualCropHelp);
				this->Controls->Add(this->btnManualCrop);
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
			void ApplyTheme()
			{
				// Form theme
				this->BackColor = Color::FromArgb(15, 15, 20);

				// Labels
				lblTitle->ForeColor = Color::FromArgb(0, 255, 0);
				lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
				lblRecording->ForeColor = Color::FromArgb(255, 0, 0);
				lblTimestamp->ForeColor = Color::FromArgb(100, 255, 100);
				lblFaceInfo->ForeColor = Color::FromArgb(255, 200, 0);
				lblManualCropHelp->ForeColor = Color::FromArgb(255, 255, 255);

				// Buttons
				btnUpload->BackColor = Color::FromArgb(30, 30, 40);
				btnUpload->ForeColor = Color::FromArgb(200, 150, 255);
				btnUpload->FlatAppearance->BorderColor = Color::FromArgb(155, 89, 182);

				btnDetect->BackColor = Color::FromArgb(30, 30, 40);
				btnDetect->ForeColor = Color::FromArgb(100, 200, 255);
				btnDetect->FlatAppearance->BorderColor = Color::FromArgb(52, 152, 219);

				btnPrev->BackColor = Color::FromArgb(30, 30, 40);
				btnPrev->ForeColor = Color::FromArgb(100, 255, 100);
				btnPrev->FlatAppearance->BorderColor = Color::FromArgb(100, 255, 100);

				btnNext->BackColor = Color::FromArgb(30, 30, 40);
				btnNext->ForeColor = Color::FromArgb(100, 255, 100);
				btnNext->FlatAppearance->BorderColor = Color::FromArgb(100, 255, 100);

				btnSearch->BackColor = Color::FromArgb(30, 30, 40);
				btnSearch->ForeColor = Color::FromArgb(255, 100, 100);
			 btnSearch->FlatAppearance->BorderColor = Color::FromArgb(255, 50, 50);

				btnManualCrop->BackColor = Color::FromArgb(30, 30, 40);
				btnManualCrop->ForeColor = Color::FromArgb(255, 255, 100);
				btnManualCrop->FlatAppearance->BorderColor = Color::FromArgb(255, 255, 0);
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
					
					// Clear existing images properly
					if (pictureBox1->Image != nullptr)
					{
						delete pictureBox1->Image;
						pictureBox1->Image = nullptr;
					}
					
					if (originalImage != nullptr)
					{
						delete originalImage;
						originalImage = nullptr;
					}
					
					// Load new image
					originalImage = Image::FromFile(currentImagePath);
					pictureBox1->Image = Image::FromFile(currentImagePath);
					pictureBox1->Refresh();
					
					currentFaceIndex = 0;
					UpdateFaceNavigation();

					lblStatus->Text = "STATUS: IMAGE LOADED";
					lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
				}
			}

		// Manual crop button
		System::Void btnManualCrop_Click(Object^ sender, EventArgs^ e)
		{
			if (pictureBox1->Image == nullptr)
			{
				MessageBox::Show("ALERT: Please load an image first", "NO IMAGE",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}

			isManualCropMode = !isManualCropMode;

			if (isManualCropMode)
			{
				btnManualCrop->Text = L"[ACTIVE]";
				btnManualCrop->ForeColor = Color::FromArgb(255, 255, 0);
				lblManualCropHelp->Text = "MANUAL CROP MODE: Click and drag to select face area";
				lblManualCropHelp->Visible = true;
				lblStatus->Text = "STATUS: MANUAL CROP MODE ACTIVE";
				lblStatus->ForeColor = Color::FromArgb(255, 200, 0);
			}
			else
			{
				btnManualCrop->Text = L"[M-CROP]";
				btnManualCrop->ForeColor = Color::FromArgb(255, 200, 100);
				lblManualCropHelp->Visible = false;
				cropRectangle = System::Drawing::Rectangle(0, 0, 0, 0);
				pictureBox1->Invalidate();
				lblStatus->Text = "STATUS: MANUAL CROP CANCELLED";
				lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			}
		}

		// PictureBox Paint event - Draw corner brackets and crop rectangle
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

			// Draw crop rectangle if in manual crop mode
			if (isManualCropMode && cropRectangle.Width > 0 && cropRectangle.Height > 0)
			{
				Pen^ cropPen = gcnew Pen(Color::FromArgb(255, 255, 0), 2);
				cropPen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
				g->DrawRectangle(cropPen, cropRectangle);

				// Draw dimensions
				String^ dimText = String::Format("{0}x{1}", cropRectangle.Width, cropRectangle.Height);
				System::Drawing::Font^ dimFont = gcnew System::Drawing::Font("Consolas", 8);
				SizeF textSize = g->MeasureString(dimText, dimFont);

				int textX = cropRectangle.X + cropRectangle.Width / 2 - (int)(textSize.Width / 2);
				int textY = cropRectangle.Y - 20;
				if (textY < 0) textY = cropRectangle.Y + cropRectangle.Height + 5;

				g->FillRectangle(Brushes::Black, (float)textX - 2, (float)textY - 2, textSize.Width + 4, textSize.Height + 4);
				g->DrawString(dimText, dimFont, Brushes::Yellow, (float)textX, (float)textY);

				delete dimFont;
				delete cropPen;
			}

			delete greenPen;
		}

		// Mouse events for manual crop
		System::Void PictureBox1_MouseDown(Object^ sender, MouseEventArgs^ e)
		{
			if (!isManualCropMode) return;

			if (e->Button == System::Windows::Forms::MouseButtons::Left)
			{
				isDrawing = true;
				cropStartPoint = e->Location;
				cropEndPoint = e->Location;
				cropRectangle = System::Drawing::Rectangle(0, 0, 0, 0);
			}
		}

		System::Void PictureBox1_MouseMove(Object^ sender, MouseEventArgs^ e)
		{
			if (!isManualCropMode || !isDrawing) return;

			cropEndPoint = e->Location;

			int x = Math::Min(cropStartPoint.X, cropEndPoint.X);
			int y = Math::Min(cropStartPoint.Y, cropEndPoint.Y);
			int width = Math::Abs(cropEndPoint.X - cropStartPoint.X);
			int height = Math::Abs(cropEndPoint.Y - cropStartPoint.Y);

			cropRectangle = System::Drawing::Rectangle(x, y, width, height);
			pictureBox1->Invalidate();
		}

		System::Void PictureBox1_MouseUp(Object^ sender, MouseEventArgs^ e)
		{
			if (!isManualCropMode || !isDrawing) return;

			isDrawing = false;

			if (cropRectangle.Width > 10 && cropRectangle.Height > 10)
			{
				ProcessManualCrop();
			}
			else
			{
				MessageBox::Show("ALERT: CROP AREA TOO SMALL\nMinimum size: 10x10 pixels",
					"INVALID SELECTION", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				cropRectangle = System::Drawing::Rectangle(0, 0, 0, 0);
				pictureBox1->Invalidate();
			}
		}

		// Process manual crop selection
		void ProcessManualCrop()
		{
			try
			{
				lblStatus->Text = "STATUS: PROCESSING MANUAL CROP...";
				lblStatus->ForeColor = Color::FromArgb(255, 255, 0);
				Application::DoEvents();

				Image^ img = pictureBox1->Image;
				if (img == nullptr)
				{
					MessageBox::Show("SYSTEM ERROR: NO IMAGE LOADED", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					return;
				}

				// Convert PictureBox coordinates to image coordinates
				System::Drawing::Rectangle imgRect = ConvertPBCoordsToImageCoords(cropRectangle);

				if (imgRect.Width <= 0 || imgRect.Height <= 0)
				{
					MessageBox::Show("ALERT: INVALID CROP COORDINATES", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					lblStatus->Text = "STATUS: CROP FAILED";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
					return;
				}

				// Create a NEW bitmap from file (not from pictureBox image)
				Bitmap^ sourceBmp = gcnew Bitmap(currentImagePath);
				
				// Validate crop rectangle is within bounds
				if (imgRect.X + imgRect.Width > sourceBmp->Width || 
					imgRect.Y + imgRect.Height > sourceBmp->Height)
				{
					MessageBox::Show("ALERT: CROP AREA OUT OF BOUNDS", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					delete sourceBmp;
					lblStatus->Text = "STATUS: CROP FAILED";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
					return;
				}

				// Create cropped bitmap
				Bitmap^ croppedBmp = sourceBmp->Clone(imgRect, sourceBmp->PixelFormat);
				
				// Clean up source bitmap
				delete sourceBmp;

				// Save to temp file
				String^ tempCropPath = System::IO::Path::Combine(
					System::IO::Path::GetDirectoryName(currentImagePath),
					"temp_manual_crop_" + DateTime::Now.Ticks.ToString() + ".jpg"
				);
				
				croppedBmp->Save(tempCropPath, System::Drawing::Imaging::ImageFormat::Jpeg);
				delete croppedBmp;

				// Clear current image from pictureBox before loading new one
				pictureBox1->Image = nullptr;
				
				// Small delay to ensure GDI+ releases the image
				System::Threading::Thread::Sleep(50);
				
				// Update current image path
				currentImagePath = tempCropPath;
				
				// Load the cropped image
				Image^ newImage = Image::FromFile(tempCropPath);
				pictureBox1->Image = newImage;

				// Reset crop mode
				isManualCropMode = false;
				cropRectangle = System::Drawing::Rectangle(0, 0, 0, 0);
				pictureBox1->Invalidate();
				lblManualCropHelp->Visible = false;
				btnManualCrop->Text = L"[M-CROP]";
				btnManualCrop->ForeColor = Color::FromArgb(255, 200, 100);

				lblStatus->Text = "STATUS: DETECTING FACES IN CROPPED AREA...";
				lblStatus->ForeColor = Color::FromArgb(255, 255, 0);
				Application::DoEvents();

				// Auto detect faces in cropped image
				msclr::interop::marshal_context context;
				std::string imgPath = context.marshal_as<std::string>(tempCropPath);

				if (!faceDetector->LoadImageFile(imgPath))
				{
					MessageBox::Show("SYSTEM ERROR: CANNOT LOAD CROPPED IMAGE", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					lblStatus->Text = "STATUS: DETECTION FAILED";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
					return;
				}

				std::string cascadePath = "data\\haarcascades\\haarcascade_frontalface_default.xml";
				int faceCount = faceDetector->DetectFaces(cascadePath);

				if (faceCount == -1)
				{
					MessageBox::Show("SYSTEM ERROR: CANNOT LOAD CASCADE FILE", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					lblStatus->Text = "STATUS: CASCADE ERROR";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
					return;
				}
				else if (faceCount == 0)
				{
					MessageBox::Show("ALERT: NO FACE DETECTED IN CROPPED AREA\n" +
						"The cropped region does not contain a detectable face.\n" +
						"Try selecting a different area with a visible face.",
						"NO DETECTION", MessageBoxButtons::OK, MessageBoxIcon::Warning);
					lblStatus->Text = "STATUS: NO FACE DETECTED";
					lblStatus->ForeColor = Color::FromArgb(255, 150, 50);
					return;
				}

				// Show detected faces
				currentFaceIndex = 0;
				ShowCurrentFace();

				btnPrev->Enabled = (faceCount > 1);
				btnNext->Enabled = (faceCount > 1);
				btnSearch->Enabled = true;

				lblStatus->Text = String::Format(
					"STATUS: CROP COMPLETE - {0} FACE(S) DETECTED ({1}x{2})", 
					faceCount, imgRect.Width, imgRect.Height);
				lblStatus->ForeColor = Color::FromArgb(0, 255, 0);

				MessageBox::Show(
					String::Format("MANUAL CROP SUCCESSFUL\n\n" +
						"Area: {0}x{1} pixels\n" +
						"Faces Detected: {2}\n\n" +
						"Use ◄ ► to navigate if multiple faces found.\n" +
						"Click [SELECT] when ready.",
						imgRect.Width, imgRect.Height, faceCount),
					"SUCCESS", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("SYSTEM ERROR: " + ex->Message + "\n\nStack Trace:\n" + ex->StackTrace, 
					"ERROR", MessageBoxButtons::OK, MessageBoxIcon::Error);
				lblStatus->Text = "STATUS: PROCESSING ERROR";
				lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
				
				// Reset crop mode on error
				isManualCropMode = false;
				cropRectangle = System::Drawing::Rectangle(0, 0, 0, 0);
				pictureBox1->Invalidate();
				lblManualCropHelp->Visible = false;
				btnManualCrop->Text = L"[M-CROP]";
				btnManualCrop->ForeColor = Color::FromArgb(255, 200, 100);
			}
		}

		// Helper function to get actual image display bounds in Zoom mode
		System::Drawing::Rectangle GetImageDisplayBounds()
		{
			if (pictureBox1->Image == nullptr)
				return System::Drawing::Rectangle(0, 0, 0, 0);

			Image^ img = pictureBox1->Image;
			int pbWidth = pictureBox1->Width;
			int pbHeight = pictureBox1->Height;

			float imgAspect = (float)img->Width / img->Height;
			float pbAspect = (float)pbWidth / pbHeight;

			int displayWidth, displayHeight, offsetX, offsetY;

			if (imgAspect > pbAspect)
			{
				// Image is wider - fit to width
				displayWidth = pbWidth;
				displayHeight = (int)(pbWidth / imgAspect);
				offsetX = 0;
				offsetY = (pbHeight - displayHeight) / 2;
			}
			else
			{
				// Image is taller - fit to height
				displayHeight = pbHeight;
				displayWidth = (int)(pbHeight * imgAspect);
				offsetX = (pbWidth - displayWidth) / 2;
				offsetY = 0;
			}

			return System::Drawing::Rectangle(offsetX, offsetY, displayWidth, displayHeight);
		}

		// Convert PictureBox coordinates to image coordinates
		System::Drawing::Rectangle ConvertPBCoordsToImageCoords(System::Drawing::Rectangle pbRect)
		{
			if (pictureBox1->Image == nullptr)
				return System::Drawing::Rectangle(0, 0, 0, 0);

			Image^ img = pictureBox1->Image;
			System::Drawing::Rectangle displayBounds = GetImageDisplayBounds();

			if (displayBounds.Width == 0 || displayBounds.Height == 0)
				return System::Drawing::Rectangle(0, 0, 0, 0);

			// Calculate scale factor
			float scaleX = (float)img->Width / displayBounds.Width;
			float scaleY = (float)img->Height / displayBounds.Height;

			// Convert coordinates
			int imgX = (int)((pbRect.X - displayBounds.X) * scaleX);
			int imgY = (int)((pbRect.Y - displayBounds.Y) * scaleY);
			int imgWidth = (int)(pbRect.Width * scaleX);
			int imgHeight = (int)(pbRect.Height * scaleY);

			// Clamp to image bounds
			imgX = Math::Max(0, Math::Min(imgX, img->Width - 1));
			imgY = Math::Max(0, Math::Min(imgY, img->Height - 1));
			imgWidth = Math::Max(1, Math::Min(imgWidth, img->Width - imgX));
			imgHeight = Math::Max(1, Math::Min(imgHeight, img->Height - imgY));

			return System::Drawing::Rectangle(imgX, imgY, imgWidth, imgHeight);
		}

		// Initialize Face Detector
		void InitializeFaceDetector()
		{
			faceDetector = new FaceDetectionWrapper();
		}

		// Detect faces button
		System::Void btnDetect_Click(Object^ sender, EventArgs^ e)
		{
			if (currentImagePath == nullptr) return;

			try
			{
				lblStatus->Text = "STATUS: SCANNING FOR TARGETS...";
				lblStatus->ForeColor = Color::FromArgb(255, 255, 0);
				Application::DoEvents();

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

		// Previous face button
		System::Void btnPrev_Click(Object^ sender, EventArgs^ e)
		{
			if (currentFaceIndex > 0)
			{
				currentFaceIndex--;
				ShowCurrentFace();
				UpdateFaceNavigation();
			}
		}

		// Next face button
		System::Void btnNext_Click(Object^ sender, EventArgs^ e)
		{
			if (currentFaceIndex < faceDetector->GetFaceCount() - 1)
			{
				currentFaceIndex++;
				ShowCurrentFace();
				UpdateFaceNavigation();
			}
		}

		// Select button (ปุ่มเลือกใบหน้าส่งกลับไปหน้าหลัก)
		System::Void btnSearch_Click(Object^ sender, EventArgs^ e)
		{
			if (faceDetector->GetFaceCount() == 0) return;

			try
			{
				lblStatus->Text = "STATUS: SAVING TARGET...";
				lblStatus->ForeColor = Color::FromArgb(255, 255, 0);
				Application::DoEvents();

				String^ tempFacePath = "temp_selected_target.jpg";
				msclr::interop::marshal_context context;
				std::string tempPath = context.marshal_as<std::string>(tempFacePath);

				if (!faceDetector->SaveCurrentFace(currentFaceIndex, tempPath))
				{
					MessageBox::Show("SYSTEM ERROR: CANNOT SAVE TARGET", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					lblStatus->Text = "STATUS: SAVE FAILED";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
					return;
				}

				// Send selected target to main form
				if (mainForm != nullptr)
				{
					mainForm->SetSelectedTarget(tempFacePath);
					
					lblStatus->Text = "STATUS: TARGET TRANSFERRED TO MAIN SYSTEM";
					lblStatus->ForeColor = Color::FromArgb(0, 255, 0);
					
					// Ask if user wants to search immediately
					auto result = MessageBox::Show(
						"TARGET LOCKED SUCCESSFULLY\n\nDo you want to search the database now?",
						"SEARCH CONFIRMATION",
						MessageBoxButtons::YesNo,
						MessageBoxIcon::Question);

					this->Close();

					// If user wants to search immediately, trigger search
					if (result == System::Windows::Forms::DialogResult::Yes)
					{
						// Trigger search button click on main form
						// Note: This requires btnSearchPerson to be accessible
						// For now, just show message
						MessageBox::Show("Click [SEARCH] button on main screen to identify target.",
							"READY FOR IDENTIFICATION",
							MessageBoxButtons::OK,
							MessageBoxIcon::Information);
					}
				}
				else
				{
					MessageBox::Show("SYSTEM ERROR: MAIN FORM NOT FOUND", "ERROR",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
					lblStatus->Text = "STATUS: TRANSFER FAILED";
					lblStatus->ForeColor = Color::FromArgb(255, 0, 0);
					return;
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

		// Show current face with rectangle
		void ShowCurrentFace()
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

		// Update face navigation controls
		void UpdateFaceNavigation()
		{
			int faceCount = faceDetector->GetFaceCount();
			lblFaceInfo->Text = "TARGET: " + (currentFaceIndex + 1) + " / " + faceCount;

			btnPrev->Enabled = (currentFaceIndex > 0);
			btnNext->Enabled = (currentFaceIndex < faceCount - 1);
			btnSearch->Enabled = (faceCount > 0);
		}
	};
}