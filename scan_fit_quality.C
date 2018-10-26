
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"


void scan_fit_quality(int nRandommin,int nRandommax, double sigma)
{
	
 	
  TH1D* hist = new TH1D("hist", "Histogram", 40, -3, 3);
  
  for(Int_t i = 0; i < 10; i++) {
  TF1* fGaus = new TF1("fGaus", "gaus", -3, 3);
  fGaus->SetParameters(1, 0, 1);
   hist->Fill(fGaus->GetRandom());} // amplitude, mean, sigma
  hist->Sumw2();
  //hist->SetMinimum(0);
  TF1* fit1 = new TF1("fit1", "pol2",-3,3);
 
  

  for(Int_t i = 0; i < 10000; i++) {

    hist->Fill(fGaus->GetRandom());
    
  }

  hist->Draw();
  hist->Fit(fit1);
  gStyle->SetOptFit();
  gStyle->SetOptStat();
}
