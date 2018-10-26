#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <TMath.h>
#include <TH1D.h>
#include <TRandom.h>
#include <TCanvas.h>
#include <TF1.h> 
#include <TStyle.h> 
#include <TLatex.h>

void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t v2);
void rootfuncgenerate(Int_t nEvents,Int_t nTracks, Double_t v2) 
{
  //cout << "Generating " << nEvents << " events" << endl << endl;
  
  
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
    
    
   // cout << "Event " << n << endl;
    file << "Event " << n << endl;
    //cout << "nTracks " << nTracks << endl;
    file <<  "nTracks " << nTracks << endl; 

    for (Int_t nt=0; nt < nTracks; nt++){
		
	  
	  
	  phi[nt] = v2Func ->GetRandom();
	  
	 // cout << nt << " : " << phi[nt]<< endl;
	  
	}
       
    for (Int_t i=0; i<nTracks; i++) {
	  
	  hPhi->Fill(phi[i]);
	  file << i << " : " << phi[i]<< endl;
    }
  }
   file.close();
}

Double_t analyze_v2_2particle(){
	
	
	int nEvents = 0; // event counter
	
	string helpString; // help variable

	ifstream inFile("phi_dist.dat");
	
	int eventNo = 0;
	
	if ("!=inFile"){
	
	cout<< "Error: No file Found"<< endl;}
	
	Double_t sum_const_2=0;
	Double_t Qvector2=0;
	
	while (inFile >> helpString >> eventNo) {
		
		//cout <<" Reading event : " << eventNo << endl;
		
		nEvents++;
		
	    int nTracks =-1;
		
		inFile >> helpString >> nTracks;
		
	
//		cout <<  "Event contains "<< nTracks << "tracks " <<endl;
		
		double phi[nTracks];
		int trackNo;
		
		// Read back the phi values
		
		for (int nt =0 ; nt<nTracks; nt++) {
			
			inFile >> trackNo >> helpString >> phi[nt];
			
//			cout << nt << ":" << phi[nt] << endl;
		}
		
		// Here we want to analyze the phi values 
		
		Double_t sum_cos2_diff = 0;
		for(Int_t i = 0; i < nTracks; i++){
			
		for(Int_t j = 0; j < nTracks && j!=i; j++) {
		sum_cos2_diff += 2*TMath::Cos(2*(phi[i]-phi[j]));
		}
	  }
		sum_const_2 += sum_cos2_diff/(nTracks*(nTracks-1));
		
		
		
	// Extracting V2{2} using Q vector	
	
	// Q vector 
	
		Double_t sum_cos2 = 0;
		Double_t sum_sin2 = 0;
		
		// // Compute Q vector
		
		for (Int_t i = 0 ; i < nTracks; i++) 
		
		{
			sum_cos2 += TMath :: Cos(2*phi[i]);
			sum_sin2 += TMath :: Sin(2*phi[i]);
		}
		
		Double_t Qvector = pow(sum_cos2,2) + pow(sum_sin2,2);
		
		Qvector2 += (Qvector-nTracks)/(nTracks*(nTracks-1));
		
		
		
	}		
	
		Double_t Mean = sum_const_2/(nEvents);
		
		Double_t V2 = sqrt(Mean);
		
		/*cout << "<2> = " << Mean << endl;
		
		cout << "V2{2} =  " << V2 << endl;

		cout << "Q-vector Method : {2} = " << Qvector2/nEvents << endl;
		
		cout << "Q-vector Method : V2{2} = " << sqrt(Qvector2/nEvents) << endl;	*/
		
		return V2;
				
}	
	
	void analyze_v2_2particle_for_Nexperiments(Int_t NExp, Int_t nEvents,Int_t nTracks, Double_t v2)  {
		// create histogram that we will fill with random values
  TH1D* hV2 = new TH1D("hV2", " V2 distribution; x; Counts", 
			100, 0,0.1);
  hV2->Sumw2();
	
	for (Int_t i =0; i< NExp ; i++) {
		
	rootfuncgenerate(nEvents,  nTracks, v2);
	
	hV2->Fill(analyze_v2_2particle());}
	
	TCanvas* c1 = new TCanvas("c1", "v2 canvas", 200,10,900, 600);
	c1->SetFillColor(42);
	c1->SetGrid();
  hV2->SetMinimum(0);
  hV2->Draw();
  gStyle->SetOptStat();
  TLatex* t = new TLatex (0.01,11,"Ngen = 100, v2=0.05");
	t->SetTextSize(0.03);
	t->Draw();
  
 
  
}
	
	
		
		
		
		
		
		
