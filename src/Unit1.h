//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TSpeedButton *SpeedButton1;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TCheckBox *CheckBox15;
        TCheckBox *CheckBox16;
        TButton *Button1;
        TButton *Button2;
        TSpeedButton *SpeedButton2;
        TLabel *Label1;
        TTrackBar *TrackBar1;
        TRadioGroup *RadioGroup1;
        TButton *Button3;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
        TRadioButton *RadioButton7;
        TRadioButton *RadioButton8;
        TSpeedButton *SpeedButton3;
        TOpenDialog *OpenDialog1;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        void TForm1::OnWaveDone (TMessage& msg);
        void TForm1::OnWaveMessage(TMessage& msg);
                BEGIN_MESSAGE_MAP
                 MESSAGE_HANDLER(MM_WIM_DATA, TMessage, OnWaveMessage)
                 MESSAGE_HANDLER( MM_WOM_DONE, TMessage, OnWaveDone)
                END_MESSAGE_MAP(TForm)
        void TForm1::SaveWaveFile(char* FileName);
        void TForm1::Odtwarzanie();
        void TForm1::Wczytaj(FILE *plik);

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern "C" { FDekoder(char nazwa[13],char nazwa1[13]); }
extern "C" { FKoder(short tryb); }

//Deklaracja zmiennych globalnych i klas
WAVEFORMATEX    WaveFormat;
HWAVEIN         WaveHandle;
WAVEHDR         WaveHeader;
char*           Buffer = NULL;
char*           Buffer2= NULL;
unsigned int    BufferSize = 0;
unsigned int    BytesEncoded=0;
unsigned int    BytesDecoded=0;
typedef struct _WAVEHEAD {
 struct {
        char            RIFF[4];
        unsigned long   Size;
        char            WAVE[4]; //okresla format pliku
 } RIFF;
 struct {
        char            fmt[4] ;
        unsigned long   BlockSize;
        struct {
          unsigned short  AudioFormat;
          unsigned short  NumChannels;
          unsigned long SampleRate;
          unsigned long ByteRate;
          unsigned short  BlockAlign;
          unsigned short  BitsPerSample;
          } Format;
 } fmt;
 struct {
        char            data[4];
        unsigned long   DataSize;
 } data;
} WAVEHEAD;
//---------------------------------------------------------------------------
#endif
 