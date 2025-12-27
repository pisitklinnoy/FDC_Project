#pragma once

namespace FDCProject {
	ref class CropForm;
	ref class GalleryForm;
}

namespace FDCProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			// Initialize theme colors
			this->BackColor = Color::FromArgb(15, 15, 20);

			// Start recording blink timer
			recTimer = gcnew System::Windows::Forms::Timer();
			recTimer->Interval = 500;
			recTimer->Tick += gcnew EventHandler(this, &MyForm::RecTimer_Tick);
			recTimer->Start();

			// Update timestamp timer
			timestampTimer = gcnew System::Windows::Forms::Timer();
			timestampTimer->Interval = 1000;
			timestampTimer->Tick += gcnew EventHandler(this, &MyForm::TimestampTimer_Tick);
			timestampTimer->Start();
			UpdateTimestamp();

			// Initialize selected target path
			selectedTargetPath = nullptr;
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
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

	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::Label^ lblRecording;
	private: System::Windows::Forms::Label^ lblTimestamp;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Label^ lblScore1;
	private: System::Windows::Forms::Label^ lblScore2;
	private: System::Windows::Forms::Label^ lblScore3;
	private: System::Windows::Forms::Button^ btnSelectTarget;
	private: System::Windows::Forms::Button^ btnSearchPerson;
	private: System::Windows::Forms::Button^ btnManageGallery;
	private: System::Windows::Forms::Timer^ recTimer;
	private: System::Windows::Forms::Timer^ timestampTimer;
	private: bool recBlinkState;

	public:
		String^ selectedTargetPath;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->lblRecording = (gcnew System::Windows::Forms::Label());
			this->lblTimestamp = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lblScore1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lblScore2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->lblScore3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->btnSelectTarget = (gcnew System::Windows::Forms::Button());
			this->btnSearchPerson = (gcnew System::Windows::Forms::Button());
			this->btnManageGallery = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();

			// lblTitle
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Consolas", 18, System::Drawing::FontStyle::Bold));
			this->lblTitle->ForeColor = Color::FromArgb(0, 255, 0);
			this->lblTitle->Location = System::Drawing::Point(140, 15);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(450, 28);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"???? SURVEILLANCE SYSTEM ????";

			// lblRecording
			this->lblRecording->AutoSize = true;
			this->lblRecording->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->lblRecording->ForeColor = Color::FromArgb(255, 0, 0);
			this->lblRecording->Location = System::Drawing::Point(20, 50);
			this->lblRecording->Name = L"lblRecording";
			this->lblRecording->Size = System::Drawing::Size(80, 17);
			this->lblRecording->TabIndex = 7;
			this->lblRecording->Text = L"? REC";

			// lblTimestamp
			this->lblTimestamp->AutoSize = true;
			this->lblTimestamp->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Regular));
			this->lblTimestamp->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblTimestamp->Location = System::Drawing::Point(520, 52);
			this->lblTimestamp->Name = L"lblTimestamp";
			this->lblTimestamp->Size = System::Drawing::Size(180, 14);
			this->lblTimestamp->TabIndex = 8;
			this->lblTimestamp->Text = L"2025-01-01 00:00:00";

			// lblStatus
			this->lblStatus->AutoSize = true;
			this->lblStatus->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblStatus->Location = System::Drawing::Point(20, 75);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(280, 17);
			this->lblStatus->TabIndex = 1;
			this->lblStatus->Text = L"STATUS: STANDBY - READY";

			// groupBox1
			this->groupBox1->Controls->Add(this->lblScore1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->groupBox1->ForeColor = Color::FromArgb(0, 255, 0);
			this->groupBox1->Location = System::Drawing::Point(30, 110);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 280);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"[TARGET #1]";

			// lblScore1
			this->lblScore1->AutoSize = true;
			this->lblScore1->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblScore1->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblScore1->Location = System::Drawing::Point(30, 250);
			this->lblScore1->Name = L"lblScore1";
			this->lblScore1->Size = System::Drawing::Size(140, 14);
			this->lblScore1->TabIndex = 1;
			this->lblScore1->Text = L"CONFIDENCE: ---";

			// pictureBox1
			this->pictureBox1->BackColor = System::Drawing::Color::Black;
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(25, 30);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(150, 200);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew PaintEventHandler(this, &MyForm::PictureBox_Paint);

			// groupBox2
			this->groupBox2->Controls->Add(this->lblScore2);
			this->groupBox2->Controls->Add(this->pictureBox2);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->groupBox2->ForeColor = Color::FromArgb(0, 255, 0);
			this->groupBox2->Location = System::Drawing::Point(260, 110);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 280);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"[TARGET #2]";

			// lblScore2
			this->lblScore2->AutoSize = true;
			this->lblScore2->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblScore2->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblScore2->Location = System::Drawing::Point(30, 250);
			this->lblScore2->Name = L"lblScore2";
			this->lblScore2->Size = System::Drawing::Size(140, 14);
			this->lblScore2->TabIndex = 1;
			this->lblScore2->Text = L"CONFIDENCE: ---";

			// pictureBox2
			this->pictureBox2->BackColor = System::Drawing::Color::Black;
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Location = System::Drawing::Point(25, 30);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(150, 200);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 0;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Paint += gcnew PaintEventHandler(this, &MyForm::PictureBox_Paint);

			// groupBox3
			this->groupBox3->Controls->Add(this->lblScore3);
			this->groupBox3->Controls->Add(this->pictureBox3);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Consolas", 10, System::Drawing::FontStyle::Bold));
			this->groupBox3->ForeColor = Color::FromArgb(0, 255, 0);
			this->groupBox3->Location = System::Drawing::Point(490, 110);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(200, 280);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"[TARGET #3]";

			// lblScore3
			this->lblScore3->AutoSize = true;
			this->lblScore3->Font = (gcnew System::Drawing::Font(L"Consolas", 9, System::Drawing::FontStyle::Bold));
			this->lblScore3->ForeColor = Color::FromArgb(100, 255, 100);
			this->lblScore3->Location = System::Drawing::Point(30, 250);
			this->lblScore3->Name = L"lblScore3";
			this->lblScore3->Size = System::Drawing::Size(140, 14);
			this->lblScore3->TabIndex = 1;
			this->lblScore3->Text = L"CONFIDENCE: ---";

			// pictureBox3
			this->pictureBox3->BackColor = System::Drawing::Color::Black;
			this->pictureBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox3->Location = System::Drawing::Point(25, 30);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(150, 200);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox3->TabIndex = 0;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Paint += gcnew PaintEventHandler(this, &MyForm::PictureBox_Paint);

			// btnSelectTarget
			this->btnSelectTarget->BackColor = Color::FromArgb(30, 30, 40);
			this->btnSelectTarget->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSelectTarget->FlatAppearance->BorderColor = Color::FromArgb(155, 89, 182);
			this->btnSelectTarget->FlatAppearance->BorderSize = 2;
			this->btnSelectTarget->Font = (gcnew System::Drawing::Font(L"Consolas", 11, System::Drawing::FontStyle::Bold));
			this->btnSelectTarget->ForeColor = Color::FromArgb(200, 150, 255);
			this->btnSelectTarget->Location = System::Drawing::Point(70, 420);
			this->btnSelectTarget->Name = L"btnSelectTarget";
			this->btnSelectTarget->Size = System::Drawing::Size(180, 45);
			this->btnSelectTarget->TabIndex = 5;
			this->btnSelectTarget->Text = L"[SELECT TARGET]";
			this->btnSelectTarget->UseVisualStyleBackColor = false;
			this->btnSelectTarget->Click += gcnew System::EventHandler(this, &MyForm::btnSelectTarget_Click);
			this->btnSelectTarget->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->btnSelectTarget->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);

			// btnSearchPerson
			this->btnSearchPerson->BackColor = Color::FromArgb(30, 30, 40);
			this->btnSearchPerson->Enabled = false;
			this->btnSearchPerson->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSearchPerson->FlatAppearance->BorderColor = Color::FromArgb(52, 152, 219);
			this->btnSearchPerson->FlatAppearance->BorderSize = 2;
			this->btnSearchPerson->Font = (gcnew System::Drawing::Font(L"Consolas", 11, System::Drawing::FontStyle::Bold));
			this->btnSearchPerson->ForeColor = Color::FromArgb(100, 200, 255);
			this->btnSearchPerson->Location = System::Drawing::Point(270, 420);
			this->btnSearchPerson->Name = L"btnSearchPerson";
			this->btnSearchPerson->Size = System::Drawing::Size(180, 45);
			this->btnSearchPerson->TabIndex = 6;
			this->btnSearchPerson->Text = L"[IDENTIFY TARGET]";
			this->btnSearchPerson->UseVisualStyleBackColor = false;
			this->btnSearchPerson->Click += gcnew System::EventHandler(this, &MyForm::btnSearchPerson_Click);
			this->btnSearchPerson->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->btnSearchPerson->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);

			// btnManageGallery
			this->btnManageGallery->BackColor = Color::FromArgb(30, 30, 40);
			this->btnManageGallery->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnManageGallery->FlatAppearance->BorderColor = Color::FromArgb(39, 174, 96);
			this->btnManageGallery->FlatAppearance->BorderSize = 2;
			this->btnManageGallery->Font = (gcnew System::Drawing::Font(L"Consolas", 11, System::Drawing::FontStyle::Bold));
			this->btnManageGallery->ForeColor = Color::FromArgb(100, 255, 150);
			this->btnManageGallery->Location = System::Drawing::Point(470, 420);
			this->btnManageGallery->Name = L"btnManageGallery";
			this->btnManageGallery->Size = System::Drawing::Size(180, 45);
			this->btnManageGallery->TabIndex = 7;
			this->btnManageGallery->Text = L"[DATABASE]";
			this->btnManageGallery->UseVisualStyleBackColor = false;
			this->btnManageGallery->Click += gcnew System::EventHandler(this, &MyForm::btnManageGallery_Click);
			this->btnManageGallery->MouseEnter += gcnew System::EventHandler(this, &MyForm::Button_MouseEnter);
			this->btnManageGallery->MouseLeave += gcnew System::EventHandler(this, &MyForm::Button_MouseLeave);

			// MyForm
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = Color::FromArgb(15, 15, 20);
			this->ClientSize = System::Drawing::Size(720, 490);
			this->Controls->Add(this->lblTimestamp);
			this->Controls->Add(this->lblRecording);
			this->Controls->Add(this->btnManageGallery);
			this->Controls->Add(this->btnSearchPerson);
			this->Controls->Add(this->btnSelectTarget);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->lblTitle);
			this->Name = L"MyForm";
			this->Text = L"SURVEILLANCE SYSTEM - FACIAL RECOGNITION";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
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
			Pen^ greenPen = gcnew Pen(Color::FromArgb(0, 255, 0), 2);

			int cornerSize = 15;
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

	public:
		void SetSelectedTarget(String^ targetPath)
		{
			selectedTargetPath = targetPath;
			btnSearchPerson->Enabled = (targetPath != nullptr);
			
			if (targetPath != nullptr)
			{
				lblStatus->Text = "STATUS: TARGET SELECTED - READY TO IDENTIFY";
				lblStatus->ForeColor = Color::FromArgb(100, 255, 100);
			}
		}

		void UpdateSearchResults(array<String^>^ imagePaths, array<double>^ scores)
		{
			lblStatus->Text = "STATUS: SCANNING...";
			lblStatus->ForeColor = Color::FromArgb(255, 255, 0);

			if (imagePaths->Length >= 1 && imagePaths[0] != nullptr)
			{
				try
				{
					FileStream^ fs = gcnew FileStream(imagePaths[0], FileMode::Open, FileAccess::Read);
					if (pictureBox1->Image != nullptr) delete pictureBox1->Image;
					pictureBox1->Image = Image::FromStream(fs);
					fs->Close();
					delete fs;
				}
				catch (Exception^) {}

				double similarity = 100.0 / (1.0 + scores[0] / 1000.0);
				String^ confidenceLevel = similarity > 80 ? "HIGH" : (similarity > 60 ? "MEDIUM" : "LOW");
				lblScore1->Text = "MATCH: " + similarity.ToString("F1") + "% [" + confidenceLevel + "]";
				pictureBox1->Refresh();
			}

			if (imagePaths->Length >= 2 && imagePaths[1] != nullptr)
			{
				try
				{
					FileStream^ fs = gcnew FileStream(imagePaths[1], FileMode::Open, FileAccess::Read);
					if (pictureBox2->Image != nullptr) delete pictureBox2->Image;
					pictureBox2->Image = Image::FromStream(fs);
					fs->Close();
					delete fs;
				}
				catch (Exception^) {}

				double similarity = 100.0 / (1.0 + scores[1] / 1000.0);
				String^ confidenceLevel = similarity > 80 ? "HIGH" : (similarity > 60 ? "MEDIUM" : "LOW");
				lblScore2->Text = "MATCH: " + similarity.ToString("F1") + "% [" + confidenceLevel + "]";
				pictureBox2->Refresh();
			}

			if (imagePaths->Length >= 3 && imagePaths[2] != nullptr)
			{
				try
				{
					FileStream^ fs = gcnew FileStream(imagePaths[2], FileMode::Open, FileAccess::Read);
					if (pictureBox3->Image != nullptr) delete pictureBox3->Image;
					pictureBox3->Image = Image::FromStream(fs);
					fs->Close();
					delete fs;
				}
				catch (Exception^) {}

				double similarity = 100.0 / (1.0 + scores[2] / 1000.0);
				String^ confidenceLevel = similarity > 80 ? "HIGH" : (similarity > 60 ? "MEDIUM" : "LOW");
				lblScore3->Text = "MATCH: " + similarity.ToString("F1") + "% [" + confidenceLevel + "]";
				pictureBox3->Refresh();
			}

			lblStatus->Text = "STATUS: SCAN COMPLETE - " + imagePaths->Length + " TARGET(S) IDENTIFIED";
			lblStatus->ForeColor = Color::FromArgb(0, 255, 0);
		}

	private:
		System::Void btnSelectTarget_Click(System::Object^ sender, System::EventArgs^ e);

	private:
		System::Void btnSearchPerson_Click(System::Object^ sender, System::EventArgs^ e);

	private:
		System::Void btnManageGallery_Click(System::Object^ sender, System::EventArgs^ e);
	};
}