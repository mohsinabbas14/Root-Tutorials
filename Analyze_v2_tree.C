#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <TMath.h>
#include <TH1F.h>
#include <TRandom.h>
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

void Analyze_v2_tree(){

	// Open the file and get the tree
	
	TFile* file = TFile::Open("phi_dist.root");
	
	TTree* tree = (TTree*)file->Get("tree");
	
	MyEvent* event = 0;
	
	TClonesArray* trackArray = 0;
	
	tree->SetBranchAddress("event", &event);
	
	tree->SetBranchAddress("track", &trackArray);
	
	Int_t nEvents = tree->GetEntries();
	
	Double_t Qvector2 = 0;
	
	for(Int_t n = 0; n < nEvents; n++) {
		
// Read in event n (fills event and trackArray)
	tree->GetEntry(n);
	
	Double_t sum_cos2 = 0;
	Double_t sum_sin2 = 0;
	
	const Int_t nTracks = trackArray->GetEntries();

	for(Int_t i = 0; i < nTracks; i++) {
	
	MyTrack* track = (MyTrack*)trackArray->At(i);
	
	// Q vector
		
			sum_cos2 += TMath :: Cos(2*track->fPhi);
			sum_sin2 += TMath :: Sin(2*track->fPhi);
		}
		

	Double_t Qvector = pow(sum_cos2,2) + pow(sum_sin2,2);
		
	 Qvector2 += (Qvector-nTracks)/(nTracks*(nTracks-1));
		
}

		cout << "Q-vector Method : {2} = " << Qvector2/nEvents << endl;
		
		cout << "Q-vector Method : V2{2} = " << sqrt(Qvector2/nEvents) << endl;
}







	
		
		
		
		
		
