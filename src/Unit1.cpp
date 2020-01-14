//---------------------------------------------------------------------------

#include <vcl.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Label1->Caption="Rozmiar bufora pozwoli nagraæ "
+AnsiString(TrackBar1->Position)+" sek.";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
if (SpeedButton1->Caption=="&Nagraj")
 {
Button1->Enabled=false;
Button3->Enabled=false;
SpeedButton1->Caption="&Stop";
SpeedButton2->Enabled=false;

WaveHeader.lpData = NULL;
delete[] Buffer;
Buffer = NULL;
//Zmienne opisujace jakosc dzwieku
unsigned short  Channels         = 1;       //kanaly: 1-mono, 2-stereo
unsigned long   SamplesPerSecond = 8000;   //ilosc probek na sekunde
unsigned short  BitsPerSample    = 16;       //rozmiar probki
unsigned long   RecordSeconds    = TrackBar1->Position;      //dlugosc nagrania

//Wypelnienie struktury WAVEFORMATEX
WaveFormat.wFormatTag      = WAVE_FORMAT_PCM;
WaveFormat.nChannels       = Channels;
WaveFormat.nSamplesPerSec  = SamplesPerSecond;
WaveFormat.wBitsPerSample  = BitsPerSample;
WaveFormat.nAvgBytesPerSec = SamplesPerSecond * BitsPerSample/8 *Channels;
WaveFormat.nBlockAlign     = (Channels*BitsPerSample)/8;
WaveFormat.cbSize          = 0;

//sprawdzamy, czy sprzet obsluguje taki format
int Res = waveInOpen(&WaveHandle, WAVE_MAPPER, &WaveFormat, 0, 0,
 WAVE_FORMAT_QUERY);
if (Res == WAVERR_BADFORMAT)
{ShowMessage("Sprzêt nie obs³uguje wymaganego formatu.");
 return;}
//otwieramy device  (WAVE_MAPPER = standardowe urzadzenie dzwieku
//[pierwszy przetwornik Cyfrowo->Analogowy])
Res = waveInOpen(&WaveHandle, WAVE_MAPPER, &WaveFormat, (MAKELONG(Handle,0)),
 0, CALLBACK_WINDOW);
if(Res) {ShowMessage("B³¹d otwarcia standardowego urz¹dzenia dŸwiêku."); return;}

//przygotowujemy bufor na nagranie
BufferSize = RecordSeconds * (BitsPerSample / 8) * SamplesPerSecond * Channels;
Buffer = new char [BufferSize];

//przygotowujemy klase WAVEHDR zawierajaca informacje potrzebne windowsowi...
// [m.in. rozmiar i pointer do buforu]
WaveHeader.dwBufferLength  = BufferSize;
WaveHeader.dwFlags         = 0;
WaveHeader.lpData          = Buffer;

//przygotowujemy naglowek:
Res = waveInPrepareHeader(WaveHandle, &WaveHeader, sizeof(WAVEHDR));
if(Res){ShowMessage("Niepowiod³o siê przygotowanie nag³ówka.");
 if(Buffer) delete Buffer; return;}

//Dodajemy bufor do listy buforow
Res = waveInAddBuffer(WaveHandle, &WaveHeader, sizeof(WAVEHDR));

//zaczynamy nagrywanie dzwieku
Res = waveInStart(WaveHandle);
if(Res){ShowMessage("Nagrywanie nie powiod³o siê."); if(Buffer) delete Buffer; return;}

 }
 else
 {
 waveInReset(WaveHandle); //przerywa nagrywanie
 waveInClose(WaveHandle);  //zamyka sprzet
 if (RadioGroup1->Enabled) Button3->Enabled=true;
 }
}
//---------------------------------------------------------------------------
//Funkcja wykrywaj¹ca koniec nagrywania, zapisuj¹ca i sprzatajaca
void TForm1::OnWaveMessage(TMessage& msg)
{
if(msg.Msg == MM_WIM_DATA)
 {
 //zamykamy sprzet
 waveInClose(WaveHandle);
 //zapisujemy plik
 SaveWaveFile("record");
 //Odblokowanie przyciskow po nagraniu               
        SpeedButton2->Enabled=true;
        Button1->Enabled=true;
        SpeedButton1->Caption="&Nagraj";
        if (RadioGroup1->Enabled) Button3->Enabled=true;
 }
}
//------------------------------------------------------------------------------

void TForm1::SaveWaveFile(char* FileName)
{
//i do pliku z tym
FILE *plik = fopen(FileName,"wb"); //nadpisujemy plik, jesli istnial
//zapisanie buffora o odpowiednim rozmiarze
fwrite(Buffer,WaveHeader.dwBytesRecorded,1,plik);
fclose(plik);


}
//--------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Button1->Enabled=false;
SpeedButton1->Enabled=false;
Button2->Enabled=false;



CheckBox12->Enabled=false;
CheckBox13->Enabled=false;
CheckBox14->Enabled=false;
CheckBox15->Enabled=false;
CheckBox16->Enabled=false;
BytesEncoded=WaveHeader.dwBytesRecorded;
//sprawdzenie wybraniej przeplywnosci
if (CheckBox1->Checked==true)
        {
        FKoder(475);
        CheckBox9->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox9->Enabled=false;
if (CheckBox2->Checked==true)
        {
        FKoder(515);
        CheckBox10->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox10->Enabled=false;
if (CheckBox3->Checked==true)
        {
        FKoder(59);
        CheckBox11->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox11->Enabled=false;
if (CheckBox4->Checked==true)
        {
        FKoder(67);
        CheckBox12->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox12->Enabled=false;
if (CheckBox5->Checked==true)
        {
        FKoder(74);
        CheckBox13->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox13->Enabled=false;
if (CheckBox6->Checked==true)
        {
        FKoder(795);
        CheckBox14->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox14->Enabled=false;
if (CheckBox7->Checked==true)
        {
        FKoder(102);
        CheckBox15->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox15->Enabled=false;
if (CheckBox8->Checked==true)
        {
        FKoder(122);
        CheckBox16->Enabled=true;
        Button2->Enabled=true;
        }
        else CheckBox16->Enabled=false;
//Wyswietla informacje o niewybraniu predkosci kodowania
if (Button2->Enabled==false)
        //Okienko1->ShowModal();
         ShowMessage("Nie wybrano prêdkoœci kodowania!");
SpeedButton1->Enabled=true;
Button1->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
Button1->Enabled=false;
Button2->Enabled=false;
Button3->Enabled=false;
BytesDecoded=BytesEncoded;
RadioButton1->Enabled=false;
RadioButton2->Enabled=false;
RadioButton3->Enabled=false;
RadioButton4->Enabled=false;
RadioButton5->Enabled=false;
RadioButton6->Enabled=false;
RadioButton7->Enabled=false;
RadioButton8->Enabled=false;
RadioGroup1->Enabled=true;
if (CheckBox9->Checked==true&&CheckBox9->Enabled==true)
        {
        FDekoder("decoded475","encoded475");
        RadioButton1->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox10->Checked==true&&CheckBox10->Enabled==true)
        {
        FDekoder("decoded515","encoded515");
        RadioButton2->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox11->Checked==true&&CheckBox11->Enabled==true)
        {
        FDekoder("decoded59","encoded59");
        RadioButton3->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox12->Checked==true&&CheckBox12->Enabled==true)
        {
        FDekoder("decoded67","encoded67");
        RadioButton4->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox13->Checked==true&&CheckBox13->Enabled==true)
        {
        FDekoder("decoded74","encoded74");
        RadioButton5->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox14->Checked==true&&CheckBox14->Enabled==true)
        {
        FDekoder("decoded795","encoded795");
        RadioButton6->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox15->Checked==true&&CheckBox15->Enabled==true)
        {
        FDekoder("decoded102","encoded102");
        RadioButton7->Enabled=true;
        Button3->Enabled=true;
        };
if (CheckBox16->Checked==true&&CheckBox16->Enabled==true)
        {
        FDekoder("decoded122","encoded122");
        RadioButton8->Enabled=true;
        Button3->Enabled=true;
        };
if (Button3->Enabled==false) ShowMessage("Nie wybrano danych do dekodowania!");
Button1->Enabled=true;
Button2->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
//Posprzatanie plików tymczasowych
DeleteFile("record");
DeleteFile("encoded475");
DeleteFile("encoded515");
DeleteFile("encoded59");
DeleteFile("encoded67");
DeleteFile("encoded74");
DeleteFile("encoded795");
DeleteFile("encoded102");
DeleteFile("encoded122");
DeleteFile("decoded475");
DeleteFile("decoded515");
DeleteFile("decoded59");
DeleteFile("decoded67");
DeleteFile("decoded74");
DeleteFile("decoded795");
DeleteFile("decoded102");
DeleteFile("decoded122");
//Zwolnienie pamieci

 WaveHeader.lpData = NULL;
 delete[] Buffer;
 Buffer = NULL;
 delete[] Buffer2;
 Buffer2 = NULL;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button3Click(TObject *Sender)
{
if (Button3->Caption=="&Odtwórz")
{
Button2->Enabled=false;
Button3->Caption="&Stop";
SpeedButton1->Enabled=false;
SpeedButton2->Enabled=false;
RadioGroup1->Enabled=false;
if (RadioButton1->Checked==true && RadioButton1->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded475","rb");
        Wczytaj(plik);
        };
if (RadioButton2->Checked==true && RadioButton2->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded515","rb");
        Wczytaj(plik);
        };
if (RadioButton3->Checked==true&&RadioButton3->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded59","rb");
        Wczytaj(plik);
        };
if (RadioButton4->Checked==true&&RadioButton4->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded67","rb");
        Wczytaj(plik);
        };
if (RadioButton5->Checked==true&&RadioButton5->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded74","rb");
        Wczytaj(plik);
        };
if (RadioButton6->Checked==true&&RadioButton6->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded795","rb");
        Wczytaj(plik);
        };
if (RadioButton7->Checked==true&&RadioButton7->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded102","rb");
        Wczytaj(plik);
        };
if (RadioButton8->Checked==true&&RadioButton8->Enabled==true)
        {
        //Wczytanie pliku do bufora
        FILE *plik= fopen("decoded122","rb");
        Wczytaj(plik);
        };
//Zwolnienie pamieci buffora  */
 delete[] Buffer2;
 Buffer2 = NULL;
if (!RadioGroup1->Enabled)
{
ShowMessage("Brak danych do odtworzenia!");
SpeedButton1->Enabled=true;
SpeedButton2->Enabled=true;
Button2->Enabled=true;
Button3->Enabled=true;
Button3->Caption="&Odtwórz";
}
}
else
{
waveOutReset(WaveHandle);
waveOutUnprepareHeader(WaveHandle, &WaveHeader, sizeof(WAVEHDR));
waveOutClose(WaveHandle);
Button3->Caption="&Odtwórz";
SpeedButton1->Enabled=true;
SpeedButton2->Enabled=true;
Button3->Enabled=true;
Button2->Enabled=true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
if (SpeedButton2->Caption=="Ode&graj")
{
SpeedButton2->Caption="&Stop";
SpeedButton1->Enabled=false;
Button3->Enabled=false;
WaveHeader.lpData = Buffer;
//przypisanie buforowi dlugosci nagrania
WaveHeader.dwBufferLength  = WaveHeader.dwBytesRecorded;
Odtwarzanie();
}
else
{
waveOutReset(WaveHandle);
waveOutUnprepareHeader(WaveHandle, &WaveHeader, sizeof(WAVEHDR));
waveOutClose(WaveHandle);
SpeedButton2->Caption="Ode&graj";
SpeedButton1->Enabled=true;
if (RadioGroup1->Enabled) Button3->Enabled=true;
}
}
//---------------------------------------------------------------------------
void TForm1::Odtwarzanie()
{
//sprawdzanie czy sprzet obsluguje taki format dzwieku
int Res = waveOutOpen(&WaveHandle, WAVE_MAPPER, &WaveFormat, 0,0,
 WAVE_FORMAT_QUERY);
//incjalizacja urz¹dzenia
Res = waveOutOpen(&WaveHandle, WAVE_MAPPER, &WaveFormat, MAKELONG(Handle, 0),
 0, CALLBACK_WINDOW);
//przygotowanie nag³ówka
Res = waveOutPrepareHeader(WaveHandle, &WaveHeader, sizeof(WAVEHDR));
//odtworzenie dzwieku
Res = waveOutWrite(WaveHandle, &WaveHeader, sizeof(WAVEHDR));

}
//---------------------------------------------------------------------------


void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
Label1->Caption="Rozmiar bufora pozwoli nagraæ "+AnsiString(TrackBar1->Position)+" sek.";
}
//---------------------------------------------------------------------------
void TForm1::Wczytaj(FILE *plik)
{
Buffer2 = new char[BytesDecoded];
fread(Buffer2,BytesDecoded,1,plik);
fclose(plik);
//Wpisanie bufora do stuktury waveheader
WaveHeader.lpData = Buffer2;
WaveHeader.dwBufferLength  = BytesDecoded;
Odtwarzanie();
WaveHeader.lpData = NULL;
delete[] Buffer2;
Buffer2 = NULL;
RadioGroup1->Enabled=true;
}
//---------------------------------------------------------------------------
void TForm1::OnWaveDone (TMessage& msg)
{
if (msg.Msg == MM_WOM_DONE)
 {
 waveOutUnprepareHeader(WaveHandle, &WaveHeader, sizeof(WAVEHDR));
 waveOutClose(WaveHandle);
 SpeedButton1->Enabled=true;
 if (RadioGroup1->Enabled)
 {
 Button3->Enabled=true;
 Button2->Enabled=true;
 }
 SpeedButton2->Caption="Ode&graj";
 SpeedButton2->Enabled=true;
 Button3->Caption="&Odtwórz";
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
delete[] Buffer;
Buffer = NULL;
WAVEHEAD head;
if(!OpenDialog1->Execute()) return;  //fragment z VCL borlandowskim
char *FileName = OpenDialog1->FileName.c_str();

FILE *plik = fopen(FileName,"rb");

fread(&head, sizeof(WAVEHEAD), 1, plik);

BufferSize = head.RIFF.Size-36;
Buffer = new char[BufferSize];
fread(Buffer,BufferSize,1,plik);

fclose(plik);
if(head.fmt.Format.AudioFormat==1&&head.fmt.Format.NumChannels==1
&&head.fmt.Format.SampleRate==8000&&head.fmt.Format.BitsPerSample==16)
{
SpeedButton2->Enabled=true;
Button1->Enabled=true;
memcpy(&WaveFormat,&(head.fmt.Format),sizeof(WAVEFORMATEX));
WaveHeader.dwBytesRecorded=BufferSize;
SaveWaveFile("record");
}
else
{
ShowMessage("Niepoprawny format pliku! Czy to 16 bit, mono, PCM, 8 kHz?");
delete[] Buffer;
Buffer = NULL;
};

}
//---------------------------------------------------------------------------

