#include <iostream>

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TRandom3.h>

void generatebox (Int_t nEvents, Int_t nTracks, Double_t v2);

void generatebox (Int_t nEvents, Int_t nTracks, Double_t v2)
{
	
	TH1D* hPhi= new TH1D("hPhi", "Histogram;x;counts",100,0,2*TMath::Pi());
	
	TF1* v2Func = new TF1 ("v2Func", "[0]*(1+2*[1]*cos(2*x))",0,2*TMath::Pi());
	
	hPhi->Sumw2();
	hPhi->Sumw2();
	hPhi->SetMinimum(0);
	
	v2Func-> SetParameters(10,v2);
	v2Func-> SetParName(1,"v2");
	
	double x =(0,TMath::Pi());
	double y= (0, v2Func->GetMaximum());
	
	double Phi[nTracks];
	
	TRandom3* xRandom = new TRandom3();
	TRandom3* yRandom = new TRandom3();
	
	for (int i=0; i <nEvents; i++){
		
	 x = v2Func->GetRandom();
	 y = v2Func->GetRandom();
	 
	 if (y<10*(1+2*v2*cos(2*x)))
	 
	 {hPhi->Fill(x);}
	 }
   
   
   
   
   
   hPhi->Draw("esame");
   TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, TMath::Pi());
  fitFunc->SetParameters(10, v2);
  fitFunc->SetParName(1, "v2");
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
}
   

	
	
	
