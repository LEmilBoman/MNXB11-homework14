/* 
   In this ROOT function we generate a distribution according to sin(x)
   between 0 and pi

   To run do:
   root 
   .L rootgenerate_v2.C 
   rootfuncgenerate(10000)
*/

// include C++ STL headers 
#include <iostream>

using namespace std;

// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object

void rootfuncgenerate(Int_t nEvents, Double_t v2); // ROOT method (a bit dangerous since we don't know exactly what happens!)


//________________________________________________________________________
void rootfuncgenerate(Int_t nEvents, Double_t v2) 
{
  cout << "Generating " << nEvents << " events" << endl << endl;

  // create histogram that we will fill with random values
  TH1D* hPhi = new TH1D("hPhi", "ROOT func generated phi distribution; x; Counts", 
			100, 0, 6);

  // Define the function we want to generate
  TF1* phiFunc = new TF1("phiFunc", "1+2*[0]*cos(2*x)", 0, 6);
  phiFunc->SetParameter(0,v2);
  
  // make a loop for the number of events
  for(Int_t n = 0; n < nEvents; n++) {
    
    if((n+1)%1000==0)
      cout << "event " << n+1 << endl;
    
    // fill our phi dist histogram
    hPhi->Fill(phiFunc->GetRandom()); 
  }
  
  // Set ROOT drawing styles
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(1111);

  // create canvas for hPhi
  TCanvas* c1 = new TCanvas("c1", "phi canvas", 900, 600);
  hPhi->SetMinimum(0);
  hPhi->Draw();
  
  // create 1d function that we will use to fit our generated data to ensure
  // that the generation works
  TF1* fitFunc = new TF1("fitFunc", "[0]*sin(x)", 0, TMath::Pi());
  fitFunc->SetParameter(0, 10);
  fitFunc->SetLineColor(kRed);
  hPhi->Fit(fitFunc);
  
  // Save the canvas as a picture
  c1->SaveAs("v2_rootfunc.jpg");
}