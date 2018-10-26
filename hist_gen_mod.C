
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"

void hist_gen_mod( Int_t nRandom, Double_t sigma)
{
	
  TH1D* hist = new TH1D("hist", "Histogram", 40, -3, 3);
  
  
  TF1* fGaus = new TF1("fGaus", "gaus", -3, 3);
  fGaus->SetParameters(1, 0, sigma); // amplitude, mean, sigma
  hist->Sumw2();
  //hist->SetMinimum(0);
  TF1* fit1 = new TF1("fit1", "pol2",-3,3);
 
  

  for(Int_t i = 0; i < nRandom; i++) {

    hist->Fill(fGaus->GetRandom());
    
  }

  hist->Draw();
  hist->Fit(fit1,"f");
  gStyle->SetOptFit();
  gStyle->SetOptStat();
}
// The Fit  is a bad fit if chi 2/ NDF  is greater than 1. In our example we consider it is 
// a bad fit if chi 2 /NDF >=2.
