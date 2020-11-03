//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------


const double dx=0.25;


__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
Form1->Button1->Caption="Внести точку на график";
Form1->Button2->Caption="Лагранж";
Form1->Button3->Caption="Ньютон";
Form1->Button4->Caption="МНК 1 степени";
Form1->Button5->Caption="МНК 2 степени";
Form1->Button6->Caption="МНК 3 степени";
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
if(Edit1->Text == "")
{
	ShowMessage("Вы не ввели значение X !");
	return ;
}
if(Edit2->Text == "")
{
	ShowMessage("Вы не ввели значение  Y !");
	return ;
}
double y;
double x;
x = Edit1->Text.ToDouble();
X.push_back(x);
y = Edit2->Text.ToDouble();
Y.push_back(y);
Кривая->AddXY(x,y);
Edit1->Text = "";
Edit2->Text = "";
}


double interpolateLagrange(double x_current) {
size_t N = Form1->get_size();
vector<double> X = Form1->get_vectorX();
vector<double> Y = Form1->get_vectorY();
	double result = 0;
	for (int i = 0; i < N; i++) {
		double term = Y[i];
		for (int j = 0; j < N; j++) {
			if (j != i)
				term *= (x_current - X[j]) / (X[i] - X[j]);
        }
    result += term;
    }
     return result;
}


void __fastcall TForm1::Button2Click(TObject *Sender)
{
vector<double>x_lagr;
vector<double>y_lagr;
double x1= *min_element(begin(X),end(X));
double x2= *max_element(begin(X),end(X));

 for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
		x_lagr.push_back(x_current);
		y_lagr.push_back(interpolateLagrange(x_current));
	}

	for(size_t i=0;i<x_lagr.size(); ++i){
	Лагранж->AddXY(x_lagr[i],y_lagr[i]);
	}
}

int fact(int a)
{
    if (a==1) return 1;
    return fact(a-1)*a;
}

double u_cal1 (double u, int n) {
     double temp = u;
     for (int i = 1; i < n; i++) temp *= (u - i);
     return temp;
}

double u_cal2 (double u, int n) {
     double temp = u;
     for (int i = 1; i < n; i++) temp *= (u + i);
     return temp;
}

double interpolateNewton(vector<vector<double>> differences,double x_current, float left_half) {
size_t N = Form1->get_size();
vector<double> X = Form1->get_vectorX();
vector<double> Y = Form1->get_vectorY();
    double sum;
    if (left_half)
	{
        sum = differences[0][0];
		double u = (x_current - X[0]) / (X[1] - X[0]);
		for (int i = 1; i < N; i++)
			sum += (u_cal1(u, i) * differences[0][i]) / fact(i);
	}
	else
    {
		sum = differences[N-1][0];
		double u = (x_current - X[N-1]) / (X[1] - X[0]);
		for (int i = 1; i < N; i++)
			sum += (u_cal2(u, i) * differences[N-1][i]) / fact(i);
    }
    return sum;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
size_t N= X.size();
vector <double> x_newt;
vector <double> y_newt;
double x1= *min_element(begin(X),end(X));
double x2= *max_element(begin(X),end(X));
 vector<vector<double>> differences1; //таблица конечных разностей вперед
    vector<vector<double>> differences2; //таблица конечных разностей назад
    differences1.assign(N, vector<double>(N));
    differences2.assign(N, vector<double>(N));
	for (int i = 0; i < N; i++)
    {
		differences1[i][0]=Y[i];
		differences2[i][0]=Y[i];
    }
	for (int i = 1; i < N; i++)
    {
		for (int j = 0; j < N - i; j++)
        {
            differences1[j][i]=differences1[j + 1][i - 1] - differences1[j][i - 1];
        }
		for (int j = N-1; j >= i; j--)
        {
            differences2[j][i]=differences2[j][i - 1] - differences2[j-1][i - 1];
        }
    }
	for (double x_current = x1;x_current<(x1+x2)/2;x_current+=dx)
    {
		x_newt.push_back(x_current);
		y_newt.push_back(interpolateNewton(differences1,x_current,true));
    }

    for (double x_current = (x1+x2)/2;x_current<=x2;x_current+=dx)
       {
           x_newt.push_back(x_current);
		   y_newt.push_back(interpolateNewton(differences2,x_current,false));
	   }

	   for(size_t i=0;i<x_newt.size(); ++i){
	Ньютон->AddXY(x_newt[i],y_newt[i]);
	}
}

vector <double> interpolateLeastSquare(int K)
{
size_t N = Form1->get_size();
vector<double> X = Form1->get_vectorX();
vector<double> Y = Form1->get_vectorY();
vector<vector<double>> sums;
    sums.assign(K+1, vector<double>(K+1));

    vector<double> a(K+1,0);
    vector<double> b(K+1,0);


    for(int i=0; i<K+1; i++)
    {
        for(int j=0; j<K+1; j++)
        {
            sums[i][j] = 0;
            for(int k=0; k<N; k++)
            {
				sums[i][j] += pow(X[k], i+j);
            }
        }
    }
    for(int i=0; i<K+1; i++)
    {
        for(int k=0; k<N; k++)
        {
		b[i] += pow(X[k], i) * Y[k];
        }
    }

    double temp=0;
	for(int i=0; i<K+1; i++) //приведение к диагональному виду
    {
        if(sums[i][i]==0)
        {
            for(int j=0; j<K+1; j++)
            {
                if(j==i) continue;
                if(sums[j][i] !=0 && sums[i][j]!=0)
                {
                for(int k=0; k<K+1; k++){
                    temp = sums[j][k];
                    sums[j][k] = sums[i][k];
                    sums[i][k] = temp;
                }
                temp = b[j];
                b[j] = b[i];
                b[i] = temp;
                break;
                }
            }
        }
    }

    for(int k=0; k<K+1; k++) //расчет решения
    {
        for(int i=k+1; i<K+1; i++)
        {
        if(sums[k][k]==0)
        {
            printf("\nРешения не существует\n");
            exit(1);
        }
        double M = sums[i][k] / sums[k][k];
        for(int j=k; j<K+1; j++)
        {
            sums[i][j] -= M * sums[k][j];
        }
        b[i] -= M*b[k];
        }
    }

    for(int i=(K+1)-1; i>=0; i--)
    {
        float s = 0;
        for(int j = i; j<K+1; j++)
        {
        s = s + sums[i][j]*a[j];
        }
        a[i] = (b[i] - s) / sums[i][i];
    }
    return a;
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
vector <double> x_squ1;
vector <double> y_squ1;
vector<double> a;
double x1= *min_element(begin(X),end(X));
double x2= *max_element(begin(X),end(X));
int K=1;
	a=interpolateLeastSquare(K);
	for (double x_current = x1;x_current<=x2;x_current+=dx)
	{
		double sum=0;
		for(int i=0;i<K+1;i++)
        {
            sum+=a[i]*pow(x_current,i);
        }
        x_squ1.push_back(x_current);
        y_squ1.push_back(sum);
	}
	for(size_t i=0;i<x_squ1.size(); ++i){
	МНК_1->AddXY(x_squ1[i],y_squ1[i]);
	}
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
vector <double> x_squ2;
vector <double> y_squ2;
vector<double> a;
double x1= *min_element(begin(X),end(X));
double x2= *max_element(begin(X),end(X));
int K=2;
	a=interpolateLeastSquare(K);
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        double sum=0;
        for(int i=0;i<K+1;i++)
        {
            sum+=a[i]*pow(x_current,i);
        }
        x_squ2.push_back(x_current);
        y_squ2.push_back(sum);
	}
	for(size_t i=0;i<x_squ2.size(); ++i){
	МНК_2->AddXY(x_squ2[i],y_squ2[i]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
vector <double> x_squ3;
vector <double> y_squ3;
vector<double> a;
double x1= *min_element(begin(X),end(X));
double x2= *max_element(begin(X),end(X));
int K=3;
    a=interpolateLeastSquare(K);
    for (double x_current = x1;x_current<=x2;x_current+=dx)
    {
        double sum=0;
        for(int i=0;i<K+1;i++)
        {
            sum+=a[i]*pow(x_current,i);
        }
        x_squ3.push_back(x_current);
        y_squ3.push_back(sum);
	}
	for(size_t i=0;i<x_squ3.size(); ++i){
	МНК_3->AddXY(x_squ3[i],y_squ3[i]);
   }
}
//---------------------------------------------------------------------------

