
#include "TH1.h"
#include "TF1.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TCanvas.h"

Double_t hist_gen_mod( Int_t nRandom, Double_t sigma)
{
	
  TH1D* hist = new TH1D("hist", "Histogram", 40, -3, 3);
  
  
  TF1* fGaus = new TF1("fGaus", "gaus", -3, 3);
  fGaus->SetParameters(1, 0, sigma); // amplitude, mean, sigma
  hist->Sumw2();
  hist->SetMinimum(0);
  TF1* fit1 = new TF1("fit1", "pol2",-3,3);
 
  

  for(Int_t i = 0; i < nRandom; i++) {

    hist->Fill(fGaus->GetRandom());
    
  }

  hist->Fit(fit1);
  TF1 *f = hist->GetFunction("fit1");
  Double_t chi2 = f->GetChisquare();
  Double_t NDF = f->GetNDF();
  
  return chi2/NDF;
}
 
void scan_fit_quality(const Int_t nRandomMin, const Int_t nRandomMax, Double_t sigma)

{
	TCanvas* c1 = new TCanvas("c1", "Reduced  Chisquare",200,10,900,600);
	
	c1->SetFillColor(42);
	c1->SetGrid();
	
	Double_t x[10],y[10];
	Double_t incr = (nRandomMax - nRandomMin) / 9;
	
	for (Int_t i= 0; i<10; i++){
		
		x[i] = (nRandomMin + i * incr);
		y[i] = (hist_gen_mod(nRandomMin + i * incr,sigma));
	}
	
	TGraph* gr = new TGraph(10,x,y);
	gr->Draw("ACP");
	gr->SetTitle("Reduced Chisquare");
	gr->GetXaxis()->SetTitle("X");
	gr->GetYaxis()->SetTitle("Y");
	gr->GetXaxis()->CenterTitle();
	gr->GetYaxis()->CenterTitle();
	gr->SetLineColor(2);
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
}
 
