//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TChart *Chart1;
	TFastLineSeries *Кривая;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button1;
	TFastLineSeries *Лагранж;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TFastLineSeries *Ньютон;
	TButton *Button5;
	TButton *Button6;
	TFastLineSeries *МНК_1;
	TFastLineSeries *МНК_2;
	TFastLineSeries *МНК_3;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
private:
	vector<double> X;
	vector<double> Y;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	size_t get_size(){

	return X.size();
	}
	vector<double> get_vectorX(){
		return X;
	}

	vector<double> get_vectorY(){
		return Y;
	}
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
