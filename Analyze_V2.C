#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <TMath.h>
#include <TH1F.h>
#include <TRandom.h>



using namespace std;


void analyze_v2_2particle(){
	
	
	int nEvents = 0; // event counter
	
	string helpString; // help variable

	ifstream inFile("phi_dist.dat");
	
	int eventNo = 0;
	
	if ("!=inFile"){
	
	cout<< "Error: No file Found"<< endl;}
	
	Double_t sum_const_2=0;
	Double_t Qvector2=0;
	
	
	// create histogram that we will fill with random values
	
  TH1D* hPhi = new TH1D("hPhi", "ROOT func generated v2 distribution; x; Counts", 
			100, 0, 2*TMath::Pi());
	
	while (inFile >> helpString >> eventNo) {
		
	// cout <<" Reading event : " << eventNo << endl;
		
		nEvents++;
		
	    int nTracks =-1;
		
		inFile >> helpString >> nTracks;
		
	
	// cout <<  "Event contains "<< nTracks << "tracks " <<endl;
		
		double phi[nTracks];
		int trackNo;
		
	// Read back the phi values
		
		for (int nt =0 ; nt<nTracks; nt++) {
			
			inFile >> trackNo >> helpString >> phi[nt];
			
	// cout << nt << ":" << phi[nt] << endl;
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
		
	// Compute Q vector
		
		for (Int_t i = 0 ; i < nTracks; i++) 
		
		{
			sum_cos2 += TMath :: Cos(2*phi[i]);
			sum_sin2 += TMath :: Sin(2*phi[i]);
		}
		
		Double_t Qvector = pow(sum_cos2,2) + pow(sum_sin2,2);
		
		Qvector2 += (Qvector-nTracks)/(nTracks*(nTracks-1));
		
		
		
	}		
	
	
	//  2 Paricle Method
	
		Double_t Mean = sum_const_2/(nEvents);
		
		Double_t V2 = sqrt(Mean);
		
		cout << "<2> = " << Mean << endl;
		
		cout << "V2{2} =  " << V2 << endl;
		
	// Output QVector Method

		cout << "Q-vector Method : {2} = " << Qvector2/nEvents << endl;
		
		cout << "Q-vector Method : V2{2} = " << sqrt(Qvector2/nEvents) << endl;	
				
}	
	
	
	
		
		
		
		
		
		
