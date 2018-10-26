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
#include <TH2.h> // 2d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object


void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t v2); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t v2) 
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
  
 
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; n++) {
    
    
    cout << "Event " << n << endl;
    file << "Event " << n << endl;
    cout << "nTracks " << nTracks << endl;
    file <<  "nTracks " << nTracks << endl; 

    for (Int_t nt=0; nt < nTracks; nt++){
		
	  
	  
	  phi[nt] = v2Func ->GetRandom();
	  
	  //cout << nt << " : " << phi[nt]<< endl;
	  file << nt << " : " << phi[nt]<< endl;
	}
       
    for (Int_t i=0; i<nTracks; i++) {
	  
	  hPhi->Fill(phi[i]);
    }
  }
   file.close();
  
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "v2 canvas", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
  TF1* fitFunc = new TF1("fitFunc", "[0]*(1+2*[1]*cos(2*x))", 0, 2*TMath::Pi());
  fitFunc->SetParameters(10, v2);
  fitFunc->SetParName(1, "v2");
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("v2_rootfunc.jpg");
}

// Box Method

void boxgenerate(Int_t nEvents, Double_t v2);

void boxgenerate(Int_t nEvents, Double_t v2)
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
