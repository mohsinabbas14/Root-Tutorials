
{
   //Draw a simple graph
   // To see the output of this macro, click begin_html <a href="gif/graph.gif">here</a>. end_html
   //Author: Rene Brun
   
   TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,700,500);

   c1->SetFillColor(42);
   c1->SetGrid();

   const Int_t n = 20;
   Double_t x[n], y[n];
   for (Int_t i=0;i<n;i++) {
     x[i] = i*0.1;
     y[i] = 10*sin(x[i]+0.2);
     printf(" i %i %f %f \n",i,x[i],y[i]);
   }
   gr = new TGraphErrors(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("a simple graph");
   
   gr->SetPoint(20,2.4,6);
   gr->SetPoint(21,3,4);
   gr->GetXaxis()->SetTitle("X title");
   gr->GetXaxis()->CenterTitle();
   gr->GetYaxis()->SetTitle("Y title");
   
   gr->Draw("ACP");
   
   AR1 = new TArrow(1,5,x[6],y[6]);
   AR2 = new TArrow(1,5,3,4);
   AR1->Draw();
   AR2->Draw();
   AR1->SetLineColor(kRed);
   

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   
f1= new TF1("f1", "pol4",0,1.5);
f2= new TF1("f2", "pol5",1.5,3);
f3= new TF1("f3", "pol6",0,3);
gr->Fit(f1);
gr->Fit(f2, "+");
gr->Fit(f3, "+");
gr->GetFunction("f1")->SetLineColor(kGreen);
gr->GetFunction("f2")->SetLineColor(kBlue);
gr->GetFunction("f3")->SetLineColor(kYellow);
 
}
