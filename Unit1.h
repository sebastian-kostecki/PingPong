//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *Ball;
    TImage *LeftPaddle;
    TImage *RightPaddle;
    TTimer *LeftPaddleUp;
    TTimer *LeftPaddleDown;
    TTimer *RightPaddleUp;
    TTimer *RightPaddleDown;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall LeftPaddleUpTimer(TObject *Sender);
    void __fastcall LeftPaddleDownTimer(TObject *Sender);
    void __fastcall RightPaddleUpTimer(TObject *Sender);
    void __fastcall RightPaddleDownTimer(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
