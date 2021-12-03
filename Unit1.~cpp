//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

void setItemsPosition(TImage *Ball, TImage *RightPaddle, TImage *LeftPaddle)
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
    setItemsPosition(Ball,RightPaddle, LeftPaddle);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LeftPaddleUpTimer(TObject *Sender)
{
    LeftPaddle->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftPaddleDownTimer(TObject *Sender)
{
    LeftPaddle->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightPaddleUpTimer(TObject *Sender)
{
    RightPaddle->Top -= 10;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightPaddleDownTimer(TObject *Sender)
{
    RightPaddle->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) RightPaddleUp->Enabled = true;
    if (Key == VK_DOWN) RightPaddleDown->Enabled = true;
    if (Key == 87) LeftPaddleUp->Enabled = true;
    if (Key == 83) LeftPaddleDown->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if (Key == VK_UP) RightPaddleUp->Enabled = false;
    if (Key == VK_DOWN) RightPaddleDown->Enabled = false;
    if (Key == 87) LeftPaddleUp->Enabled = false;
    if (Key == 83) LeftPaddleDown->Enabled = false;
}
//---------------------------------------------------------------------------

