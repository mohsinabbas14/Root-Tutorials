{
	
	Exp = new TF1("Exp" , "exp([0] + [1]*x)",0.,5);
	Exp.SetParameter(0,1);
	Exp.SetParameter(1,-1);
	
	h1= new TH1D("h1", "Histogram",100,0.,5.);
	for(int i=0;i<1000;i++) {h1.Fill(Exp.GetRandom());}
	h1.Draw();
}
