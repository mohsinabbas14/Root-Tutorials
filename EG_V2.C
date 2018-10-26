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
#include <fstream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
#include <TRandom3.h>

void boxgenerate(Int_t nEvents,Int_t nTracks, Double_t v2); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void boxgenerate(Int_t nEvents,Int_t nTracks, Double_t v2) 
{
  cout << "Generating " << nEvents << " events" << endl << endl;
  
  
  Double_t phi[nTracks];
  
  ofstream file("phi_dist.dat");
  
 

  // create histogram that we will fill with random values
  TH1D* hPhi = new TH1D("hPhi", "ROOT func generated v2 distribution; x; Counts", 
			100, 0, 2*TMath::Pi());
  hPhi->Sumw2();

  // Define the function we want to generate
  TF1* v2Func = new TF1("v2Func", "[0]*(1+2*[1]*cos(2*x))", 0, 2*TMath::Pi());
  
  v2Func ->SetParameters(1,v2);
  
 double_t y=  (0, v2Func->GetMaximumX());
 double_t x=  (0, TMath::Pi());
  
 
	  xRandom = new TRandom3();
	  yRandom = new TRandom3()'
	  
 
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; n++) {
    
    
    cout << "Event " << n << endl;
    file << "Event " << n << endl;
    cout << "nTracks " << nTracks << endl;
    file <<  "nTracks " << nTracks << endl; 

    for (Int_t nt=0; nt < nTracks; nt++){
		
		do 
		{x= v2Func ->GetRandom();
		  y= v2Func ->GetRandom();
		   
	   }
		while (y<v2Func->GetMaximumX());
		
	  
	  phi[nt] = v2Func ->GetRandom();
	  
	  cout << nt << ":" << phi[nt]<< endl;
	  file << nt << ":" << phi[nt]<< endl;
	}
       
    for (Int_t i=0; i<nTracks; i++) {
	  
	  hPhi->Fill(phi[i]);
    }
  }
   file.close();
  
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hSin
  TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
  TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, TMath::Pi());
  fitFunc->SetParameters(10, v2);
  fitFunc->SetParName(1, "v2");
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("v2_rootfunc.jpg");
}
