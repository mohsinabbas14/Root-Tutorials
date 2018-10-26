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
   gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("a simple graph");
   gr->GetXaxis()->SetTitle("X title");
   gr->GetYaxis()->SetTitle("Y title");
   gr->Draw("ACP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
   
   fit1 =new TF1("fit1","pol2",0,2);
   fit2 =new TF1("fit2","pol3",0,2);
   fit3 =new TF1("fit3","pol4",0,2);
   fit4 =new TF1("fit4","pol5",0,2);
   fit5 =new TF1("fit5","pol6",0,2);
   fit6 =new TF1("fit6","pol7",0,2);
   
   gr->Fit("fit1");
   gr->Fit("fit2","+","Q");
   gr->Fit("fit3","+","Q");
   gr->Fit("fit4","+","Q");
   gr->Fit("fit5","+","Q");
   gr->Fit("fit6","+","Q");

   gr->GetFunction("fit1")->SetLineColor(kBlue);
   gr->GetFunction("fit2")->SetLineColor(kGreen);
   gr->GetFunction("fit3")->SetLineColor(kYellow);
   gr->GetFunction("fit4")->SetLineColor(kBlack);
   gr->GetFunction("fit5")->SetLineColor(kOrange);
   gr->GetFunction("fit6")->SetLineColor(kSpring);
}
