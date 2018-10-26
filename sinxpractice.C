/* 
   In this ROOT function we generate a distribution according to sin(x)
   between 0 and pi

   To run do:
   root 
   .L rootgenerate_sinx.C+ 
   rootfuncgenerate(10000)
*/

// include C++ STL headers 
#include <iostream>

using namespace std;

// ROOT library obejcts
#include "TF1.h"     // 1d function clas 
#include "TH2.h"     // 1d histogram classes
#include "TStyle.h"  // style object
#include "TMath.h"   // math functions
#include "TCanvas.h" // canvas object
#include "TRandom3.h"

void boxfuncgenerate(Int_t nEvents); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void boxfuncgenerate(Int_t nEvents) 
{
  cout << "Generating " << nEvents << " events" << endl << endl;
  
  // Define the function we want to generate
  TF1* sinFunc = new TF1("sinFunc", "[0]*sin(x)", 0, TMath::Pi());
  sinFunc->SetParameter(0,1);

  // create histogram that we will fill with random values
  TH2D* hsinaccept = new TH2D("hsinaccept", "Sin", 100, 0, TMath::Pi(), 0, sinFunc->GetMaximum());
 
  
  
  TH2D* hsinreject = new TH2D("hsinreject", "Sin", 100, 0, TMath::Pi(), 0, sinFunc->GetMaximum());
  
 
  
  

   double x;
   double y;
  
  // make a loop for the number of events
  for (int i=0; i < nEvents; i++) {
	  
    // fill our sin dist histogram
    
  x=sinFunc->GetRandom(0, TMath::Pi());
  y=sinFunc->GetRandom(0, sinFunc->GetMaximum());
    
   if (y < sin(x))
    
   { hsinaccept->Fill(x,y);}
    
    else  {hsinreject->Fill(x,y);}
  }
  
   
   hsinaccept->SetMarkerStyle(20);
   hsinaccept->SetMarkerColor(kBlue);
   hsinreject->SetMarkerStyle(21);
   hsinreject->SetMarkerColor(kRed);
  
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hSin
 TCanvas* c1 = new TCanvas ("c1", "hSin", 900, 600);
 hsinaccept->SetMinimum(0);
 hsinreject->SetMinimum(0);
 hsinaccept->Draw();
 hsinreject->Draw("same");
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
 /* TF1* fitFunc= new TF1("fitFunc", "[0]*sin(x)", 0, TMath::Pi());
  fitFunc->SetParameter(0,1);
  fitFunc->SetLineColor(kBlue);
  hsinaccept->Fit(fitFunc);
*/  
  
  // Save the canvas as a picture
  c1->SaveAs("sinx_rootfunc.jpg");
}
