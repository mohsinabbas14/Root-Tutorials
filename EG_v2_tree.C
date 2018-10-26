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
#include "MyClasses.C"
#include <TRandom.h>
#include <TTree.h>
#include <TFile.h>
#include <TClonesArray.h>


void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t sigmaTracks, Double_t v2, Double_t sigmaV2); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t sigmaTracks, Double_t v2, Double_t sigmaV2) 
{
 
  
  
  // create histogram that we will fill with random values
  TH1D* hPhi = new TH1D("hPhi", "ROOT func generated v2 distribution; x; Counts", 
			100, 0, 2*TMath::Pi());
  hPhi->Sumw2();

  // Define the function we want to generate
  TF1* v2Func = new TF1("v2Func", "[0]*(1+2*[1]*cos(2*x))", 0, 2*TMath::Pi());
  
  v2Func ->SetParameters(1,v2);
  
  // Create the outfile and data structure before the loop
	TFile* file = new TFile("phi_dist.root", "RECREATE");
	TTree* tree = new TTree("tree", "Output tree");
	MyEvent* event = new MyEvent();
	tree->Branch("event", &event);
	TClonesArray* trackArray = new TClonesArray("MyTrack", 1000);
	tree->Bronch("track", "TClonesArray", &trackArray);
	
  
 
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; n++) {
	  
	Int_t nTracksEvent = gRandom->Gaus(nTracks, sigmaTracks);
	if (nTracksEvent <0)
	nTracksEvent=0;
	   
    event->nTracks= nTracksEvent;
    
    Double_t v2Event = gRandom->Gaus(v2, sigmaV2);
    if (v2Event <0)
    v2Event=0;
    event->fV2= v2Event;

    Double_t phi[nTracksEvent];


    for (Int_t nt=0; nt < nTracksEvent; nt++){
		
	 MyTrack* track = new((*trackArray)[nt]) MyTrack();
	
	 phi[nt] = v2Func ->GetRandom();
	
	  track->fPhi = phi[nt];

	  hPhi->Fill(phi[nt]);
     }
     
     	  
	tree->Fill();
	  
	trackArray->Clear();
  }

	 file->Write();
	file->Close();
  
  
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


