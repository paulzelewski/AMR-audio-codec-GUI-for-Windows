//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TOkienko1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
        __fastcall TOkienko1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOkienko1 *Okienko1;
//---------------------------------------------------------------------------
#endif
