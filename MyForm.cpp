#include "MyForm.h"
#include "CropForm.h"
#include "GalleryForm.h"

using namespace FDCProject;

System::Void MyForm::btnSearchPerson_Click(System::Object^ sender, System::EventArgs^ e)
{
	CropForm^ searchForm = gcnew CropForm(this);
	searchForm->ShowDialog();
}

System::Void MyForm::btnManageGallery_Click(System::Object^ sender, System::EventArgs^ e)
{
	GalleryForm^ galleryForm = gcnew GalleryForm();
	galleryForm->ShowDialog();
}