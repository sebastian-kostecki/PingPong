//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int translationUp = -5;
int translationLeft = -8;
int baseTranslationLeft = -8;

int scoreLeftPaddle = 0;
int scoreRightPaddle = 0;
int numberOfBounces = 0;

bool firstGame = true;

void setItemsPosition(TImage *Ball, TImage *RightPaddle, TImage *LeftPaddle)
{
    Ball->Top = (Form1->ClientHeight) / 2 - (Ball->Height) / 2;
    Ball->Left = (Form1->ClientWidth) / 2 - (Ball->Width) / 2;

    LeftPaddle->Top = (Form1->ClientHeight) / 2 - (LeftPaddle->Height) / 2;
    LeftPaddle->Left = 20;

    RightPaddle->Top = (Form1->ClientHeight) / 2 - (RightPaddle->Height) / 2;
    RightPaddle->Left = Form1->ClientWidth - 40;
}

bool isBounceInMiddleOfPaddle(TImage *Ball, TImage *Paddle)
{
    if ((Ball->Top + (Ball->Height / 2) > Paddle->Top + 40) &&
        (Ball->Top + (Ball->Height / 2) < Paddle->Top + 60))
        {
            return true;
        }
    return false;
}

bool isTranslationOverNormal()
{
    if (translationUp > abs(baseTranslationLeft) ||
        translationUp < -(abs(baseTranslationLeft)))
    {
        return true;
    }
    return false;
}

void speedBallUpIfBounceMiddlePaddle(TImage *Ball, TImage *Paddle)
{
    if (isBounceInMiddleOfPaddle(Ball, Paddle) && isTranslationOverNormal())
    {
        translationUp = translationUp;
        translationLeft = translationLeft;
    }
    else if (isBounceInMiddleOfPaddle(Ball, Paddle) && !(isTranslationOverNormal()))
    {
        translationUp *= 2;
        translationLeft *= 2;
    }
    else if (!(isBounceInMiddleOfPaddle(Ball, Paddle)) && isTranslationOverNormal())
    {
        translationUp /= 2;
        translationLeft /= 2;
    }
}

void speedUpBallWithTime()
{
    const int NUMBER_OF_BOUNCES_TO_SPEED_UP_BALL = 6;
    if (numberOfBounces % NUMBER_OF_BOUNCES_TO_SPEED_UP_BALL == 5)
    {
        if (translationUp > 0) translationUp++;
        else translationUp = translationUp--;

        if (translationLeft > 0) translationLeft++;
        else translationLeft = translationLeft--;

        if (baseTranslationLeft > 0) baseTranslationLeft++;
        else baseTranslationLeft--;
    }
}

void bounceBallByRightPaddle(TImage *Ball, TImage *RightPaddle)
{
    if ((Ball->Top + (Ball->Height / 2) > RightPaddle->Top) &&
        (Ball->Top + (Ball->Height / 2) < RightPaddle->Top + RightPaddle->Height) &&
        (Ball->Left + Ball->Height > RightPaddle->Left))
        {
            if (translationLeft > 0) translationLeft = -translationLeft;
            speedBallUpIfBounceMiddlePaddle(Ball, RightPaddle);
            numberOfBounces++;
            speedUpBallWithTime();
        }
}

void bounceBallByLeftPaddle(TImage *Ball, TImage *LeftPaddle)
{
    if ((Ball->Top + (Ball->Height / 2) > LeftPaddle->Top) &&
        (Ball->Left < LeftPaddle->Left + LeftPaddle->Width) &&
        (Ball->Top + (Ball->Height / 2) < LeftPaddle->Top + LeftPaddle->Height))
        {
            if (translationLeft < 0) translationLeft = -translationLeft;
            speedBallUpIfBounceMiddlePaddle(Ball, LeftPaddle);
            numberOfBounces++;
            speedUpBallWithTime();
        }
}

bool isRightPlayerWinner(TImage *Ball, TImage *LeftPaddle)
{
    if (Ball->Left + Ball->Width < LeftPaddle->Left) return true;
    else return false;
}

bool isLeftPlayerWinner(TImage *Ball, TImage *RightPaddle)
{
    if (Ball->Left > RightPaddle->Left + RightPaddle->Width) return true;
    else return false;
}

void bounceBallByWalls(TImage *Ball)
{
    const int DISTANCE_FROM_WALL = 5;
    if (Ball->Top <= DISTANCE_FROM_WALL) translationUp = -translationUp;
    if (Ball->Top + Ball->Height >= Form1->ClientHeight - DISTANCE_FROM_WALL) translationUp = -translationUp;
}

void displayInformationsAfterWin(TLabel *WinnerInformation, TLabel *Score, TLabel *CounterBounces, TButton *NextRound, TButton *ButtonNewGame)
{
    WinnerInformation->Visible = true;
    Score->Visible = true;
    AnsiString scoreLeftPlayer = IntToStr(scoreLeftPaddle);
    AnsiString scoreRightPlayer = IntToStr(scoreRightPaddle);
    Score->Caption = scoreLeftPlayer + " : " + scoreRightPlayer;

    CounterBounces->Visible = true;
    AnsiString bounces = IntToStr(numberOfBounces);
    CounterBounces->Caption = "Ilo?? odbi?: " + bounces;

    NextRound->Visible = true;
    ButtonNewGame->Visible = true;
}

void disableBall(TImage *Ball, TTimer *MovingBall)
{
    MovingBall->Enabled = false;
    Ball->Visible = false;
}

void resetTranslations()
{
    const int BASE_TRANSLATION_UP = 5;
    const int BASE_TRANSLATION_LEFT = 8;

    if (translationUp > 0) translationUp = BASE_TRANSLATION_UP;
    else translationUp = translationUp = -BASE_TRANSLATION_UP;

    if (translationLeft > 0) translationLeft = BASE_TRANSLATION_LEFT;
    else translationLeft = translationLeft = -BASE_TRANSLATION_LEFT;

    if (baseTranslationLeft > 0) baseTranslationLeft = BASE_TRANSLATION_LEFT;
    else baseTranslationLeft = -BASE_TRANSLATION_LEFT;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    ShowMessage("Witaj w grze PingPong.\n\nLewy gracz steruje wciskaj?c klawisze W oraz S.\nPrawy gracz steruje wciskaj?c strza?ki w g?r? i w d??.\n\nInformacje dla graczy:\nOdbicie w srodku paletki przy?pieszy pi?k?.\nPi?ka przy?piesza w trakcie gry.\nMo?esz dowolnie zmienia? pole gry.\n\nDobrej zabawy!");
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
    setItemsPosition(Ball,RightPaddle, LeftPaddle);
    Title->Top = 50;
    Title->Left = Form1->ClientWidth / 2 - Title->Width / 2;
    WinnerInformation->Top = 50;
    WinnerInformation->Left = Form1->ClientWidth / 2 - WinnerInformation->Width / 2;
    Score->Top = WinnerInformation->Top + WinnerInformation->Height + 20;
    Score->Left = Form1->ClientWidth / 2 - Score->Width / 2;
    CounterBounces->Top = Score->Top + Score->Height + 20;
    CounterBounces->Left = Form1->ClientWidth / 2 - CounterBounces->Width / 2;
    NextRound->Top = CounterBounces->Top + CounterBounces->Height + 20;
    NextRound->Left = Form1->ClientWidth / 2 - NextRound->Width /2;
    ButtonNewGame->Top = NextRound->Top + NextRound->Height + 20;
    ButtonNewGame->Left = Form1->ClientWidth / 2 - ButtonNewGame->Width / 2;
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
    const int VK_W = 87;
    const int VK_S = 83;

    if (Key == VK_UP) RightPaddleUp->Enabled = true;
    if (Key == VK_DOWN) RightPaddleDown->Enabled = true;
    if (Key == VK_W) LeftPaddleUp->Enabled = true;
    if (Key == VK_S) LeftPaddleDown->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    const int VK_W = 87;
    const int VK_S = 83;

    if (Key == VK_UP) RightPaddleUp->Enabled = false;
    if (Key == VK_DOWN) RightPaddleDown->Enabled = false;
    if (Key == VK_W) LeftPaddleUp->Enabled = false;
    if (Key == VK_S) LeftPaddleDown->Enabled = false;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MovingBallTimer(TObject *Sender)
{
    Ball->Top += translationUp;
    Ball->Left += translationLeft;

    bounceBallByWalls(Ball);
    bounceBallByLeftPaddle(Ball, LeftPaddle);
    bounceBallByRightPaddle(Ball, RightPaddle);

    if (isRightPlayerWinner(Ball, LeftPaddle))
    {
        WinnerInformation->Caption = "Punkt dla gracza prawego >";
        scoreRightPaddle++;

        disableBall(Ball, MovingBall);
        displayInformationsAfterWin(WinnerInformation, Score, CounterBounces, NextRound, ButtonNewGame);
    }
    else if (isLeftPlayerWinner(Ball, RightPaddle))
    {
        WinnerInformation->Caption = "< Punkt dla gracza lewego";
        scoreLeftPaddle++;

        disableBall(Ball, MovingBall);
        displayInformationsAfterWin(WinnerInformation, Score, CounterBounces, NextRound, ButtonNewGame);
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ButtonNewGameClick(TObject *Sender)
{
    if (firstGame == true) firstGame = false;
    else if (firstGame == false && (Application->MessageBox("Czy na pewno chcesz zacza? od nowa?", "Potwierd?", MB_YESNO | MB_ICONQUESTION) == IDNO)) return;

    NextRoundClick(NextRound);
    scoreLeftPaddle = 0;
    scoreRightPaddle = 0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::NextRoundClick(TObject *Sender)
{
    FormCreate(Form1);
    WinnerInformation->Visible = false;
    Score->Visible = false;
    CounterBounces->Visible = false;
    NextRound->Visible = false;
    ButtonNewGame->Visible = false;
    Title->Visible = false;
    Ball->Visible = true;
    numberOfBounces = 0;
    MovingBall->Enabled = true;
    resetTranslations();
}
//---------------------------------------------------------------------------



