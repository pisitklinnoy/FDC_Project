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

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ lblTitle;
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Label^ lblScore1;
	private: System::Windows::Forms::Label^ lblScore2;
	private: System::Windows::Forms::Label^ lblScore3;
	private: System::Windows::Forms::Button^ btnSearchPerson;
	private: System::Windows::Forms::Button^ btnManageGallery;

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->lblTitle = (gcnew System::Windows::Forms::Label());
			this->lblStatus = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->lblScore1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->lblScore2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->lblScore3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->btnSearchPerson = (gcnew System::Windows::Forms::Button());
			this->btnManageGallery = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			this->lblTitle->AutoSize = true;
			this->lblTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Bold));
			this->lblTitle->Location = System::Drawing::Point(230, 20);
			this->lblTitle->Name = L"lblTitle";
			this->lblTitle->Size = System::Drawing::Size(286, 31);
			this->lblTitle->TabIndex = 0;
			this->lblTitle->Text = L"Face Search Results";
			this->lblStatus->AutoSize = true;
			this->lblStatus->Location = System::Drawing::Point(20, 70);
			this->lblStatus->Name = L"lblStatus";
			this->lblStatus->Size = System::Drawing::Size(133, 16);
			this->lblStatus->TabIndex = 1;
			this->lblStatus->Text = L"Status: No search yet";
			this->groupBox1->Controls->Add(this->lblScore1);
			this->groupBox1->Controls->Add(this->pictureBox1);
			this->groupBox1->Location = System::Drawing::Point(30, 110);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 280);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"#1";
			this->lblScore1->AutoSize = true;
			this->lblScore1->Location = System::Drawing::Point(60, 250);
			this->lblScore1->Name = L"lblScore1";
			this->lblScore1->Size = System::Drawing::Size(53, 16);
			this->lblScore1->TabIndex = 1;
			this->lblScore1->Text = L"Score: -";
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(25, 30);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(150, 200);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->groupBox2->Controls->Add(this->lblScore2);
			this->groupBox2->Controls->Add(this->pictureBox2);
			this->groupBox2->Location = System::Drawing::Point(260, 110);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 280);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"#2";
			this->lblScore2->AutoSize = true;
			this->lblScore2->Location = System::Drawing::Point(60, 250);
			this->lblScore2->Name = L"lblScore2";
			this->lblScore2->Size = System::Drawing::Size(53, 16);
			this->lblScore2->TabIndex = 1;
			this->lblScore2->Text = L"Score: -";
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Location = System::Drawing::Point(25, 30);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(150, 200);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 0;
			this->pictureBox2->TabStop = false;
			this->groupBox3->Controls->Add(this->lblScore3);
			this->groupBox3->Controls->Add(this->pictureBox3);
			this->groupBox3->Location = System::Drawing::Point(490, 110);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(200, 280);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"#3";
			this->lblScore3->AutoSize = true;
			this->lblScore3->Location = System::Drawing::Point(60, 250);
			this->lblScore3->Name = L"lblScore3";
			this->lblScore3->Size = System::Drawing::Size(53, 16);
			this->lblScore3->TabIndex = 1;
			this->lblScore3->Text = L"Score: -";
			this->pictureBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox3->Location = System::Drawing::Point(25, 30);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(150, 200);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox3->TabIndex = 0;
			this->pictureBox3->TabStop = false;
			this->btnSearchPerson->Location = System::Drawing::Point(181, 420);
			this->btnSearchPerson->Name = L"btnSearchPerson";
			this->btnSearchPerson->Size = System::Drawing::Size(150, 40);
			this->btnSearchPerson->TabIndex = 5;
			this->btnSearchPerson->Text = L"Search Person";
			this->btnSearchPerson->UseVisualStyleBackColor = true;
			this->btnSearchPerson->Click += gcnew System::EventHandler(this, &MyForm::btnSearchPerson_Click);
			this->btnManageGallery->Location = System::Drawing::Point(420, 420);
			this->btnManageGallery->Name = L"btnManageGallery";
			this->btnManageGallery->Size = System::Drawing::Size(150, 40);
			this->btnManageGallery->TabIndex = 6;
			this->btnManageGallery->Text = L"Manage Gallery";
			this->btnManageGallery->UseVisualStyleBackColor = true;
			this->btnManageGallery->Click += gcnew System::EventHandler(this, &MyForm::btnManageGallery_Click);
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(720, 490);
			this->Controls->Add(this->btnManageGallery);
			this->Controls->Add(this->btnSearchPerson);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lblStatus);
			this->Controls->Add(this->lblTitle);
			this->Name = L"MyForm";
			this->Text = L"Face Search System";
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

	public:
		void UpdateSearchResults(array<String^>^ imagePaths, array<double>^ scores)
		{
			if (imagePaths->Length >= 1 && imagePaths[0] != nullptr)
			{
				pictureBox1->Image = Image::FromFile(imagePaths[0]);
				double similarity = 100.0 / (1.0 + scores[0] / 1000.0);
				lblScore1->Text = "Score: " + similarity.ToString("F1") + "%";
			}
			if (imagePaths->Length >= 2 && imagePaths[1] != nullptr)
			{
				pictureBox2->Image = Image::FromFile(imagePaths[1]);
				double similarity = 100.0 / (1.0 + scores[1] / 1000.0);
				lblScore2->Text = "Score: " + similarity.ToString("F1") + "%";
			}
			if (imagePaths->Length >= 3 && imagePaths[2] != nullptr)
			{
				pictureBox3->Image = Image::FromFile(imagePaths[2]);
				double similarity = 100.0 / (1.0 + scores[2] / 1000.0);
				lblScore3->Text = "Score: " + similarity.ToString("F1") + "%";
			}
			lblStatus->Text = "Status: Search completed - Found " + imagePaths->Length + " matches";
		}

	private: 
		System::Void btnSearchPerson_Click(System::Object^ sender, System::EventArgs^ e);

	private: 
		System::Void btnManageGallery_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
