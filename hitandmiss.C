#include <iostream>
using namespace std;
#include <TF1.h> // 1d function class
#include <TH2.h> // 2d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TRandom3.h>

void generatebox (Int_t nEvents, Double_t v2);

void generatebox (Int_t nEvents, Double_t v2)
{
	TF1* v2Func = new TF1 ("v2Func", "[0]*(1+2*[1]*cos(2*x))",0,2*TMath::Pi());
	
	v2Func-> SetParameters(1,v2);
	v2Func-> SetParName(1,"v2");
	
	TH2D* hit= new TH2D("hit", "Histogram;x;counts",100,0,2*TMath::Pi(),100,0,v2Func->GetMaximum());
	hit->Sumw2();
	hit->SetMinimum(0);
	
	TH2D* hmiss= new TH2D("miss", "Histogram;x;counts",100,0,2*TMath::Pi(),100,0,v2Func->GetMaximum());
	hmiss->Sumw2();
	hmiss->SetMinimum(0);
	

	double x;
	double y;
	
	
	
	
	
	for (int i=0; i <nEvents; i++){
		
	 x = v2Func->GetRandom(0, 2*TMath::Pi());
	 y = v2Func->GetRandom(0, v2Func->GetMaximum());
	 
	 cout << "x" << "= " << x << " y " << "= " << y   << endl;
	 
	 if (y <1*(1+2*v2*cos(2*x)))
	 
	 {hit->Fill(x,y);}
	 else hmiss->Fill(x,y);
	 
	 
	 
	 }
    
   
   hit->SetMarkerStyle(20);
   hit->SetMarkerColor(kRed);
   hmiss->SetMarkerStyle(21);
   hmiss->SetMarkerColor(kBlue);
   
   
   
 /*
  TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, 2*TMath::Pi());
  fitFunc->SetParameters(10, v2);
  fitFunc->SetParName(1, "v2");
  fitFunc->SetLineColor(kGreen);
  hit->Fit(fitFunc);
  hmiss->Fit(fitFunc,"R+");
 
 */
 
 TCanvas* c1 = new TCanvas ("c1", "BoxMethod", 900, 600);
   hit->Draw();
   
   hmiss->Draw("same");
   
 
 
 c1->SaveAs("BoxMethod.jpg");  

   
}
   

	
	
	
