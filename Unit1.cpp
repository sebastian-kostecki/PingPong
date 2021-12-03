//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void setItemsPosition()
{
    Ball->Top = (Form1->ClientHeight) / 2 - (Ball->Height) / 2;
    Ball->Left = (Form1->ClientWidth) / 2 - (Ball->Width) / 2;

    LeftPaddle->Top = (Form1->ClientHeight) / 2 - (LeftPaddle->Height) / 2;
    LeftPaddle->Left = 20;

    RightPaddle->Top = (Form1->ClientHeight) / 2 - (RightPaddle->Height) / 2;
    RightPaddle->Left = Form1->ClientWidth - 40;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
    setItemsPosition();
}
//---------------------------------------------------------------------------
