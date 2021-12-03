//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int translationUp = -8;
int translationLeft = -8;

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
    if (LeftPaddle->Top >= 5) LeftPaddle->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LeftPaddleDownTimer(TObject *Sender)
{
    if (LeftPaddle->Top <= Form1->ClientHeight - 105) LeftPaddle->Top += 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightPaddleUpTimer(TObject *Sender)
{
    if (RightPaddle->Top >= 5) RightPaddle->Top -= 10;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RightPaddleDownTimer(TObject *Sender)
{
    if (RightPaddle->Top <= Form1->ClientHeight - 105) RightPaddle->Top += 10;
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


void __fastcall TForm1::MovingBallTimer(TObject *Sender)
{
    Ball->Top += translationUp;
    Ball->Left += translationLeft;

    if (Ball->Top <= 5) translationUp = -translationUp;
    if (Ball->Top + 32 >= Form1->ClientHeight - 5) translationUp = -translationUp;

    //odbicie od prawej paletki
    if ((Ball->Top + 16 >= LeftPaddle->Top) &&
        (Ball->Left == LeftPaddle->Left + 20) &&
        (Ball->Top +16 <= LeftPaddle->Top + 100))
        {
            translationLeft = -translationLeft;
        }

    //odbicie od lewej paletki
    if ((Ball->Top + 16 >= RightPaddle->Top) &&
        (Ball->Top + 16 <= RightPaddle->Top + 100) &&
        (Ball->Left + 32 == RightPaddle->Left))
        {
            translationLeft = -translationLeft;
        }
}
//---------------------------------------------------------------------------

