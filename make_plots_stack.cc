void make_plots_shapecomparison(TString dpath, TString rfn0, TString rfn1, TString hn, TString extension){
	
	TFile tf0(rfn0);
	TFile tf1(rfn1);
	if (! tf0.IsOpen() ){
		cout << "Couldn't open file: " << rfn0 << endl;
		return;
	}
	if (! tf1.IsOpen() ){
		cout << "Couldn't open file: " << rfn1 << endl;
		return;
	}
	cout << "accessing histograms\n";
	TH1D* h0 = (TH1D*) tf0.Get(hn);
	TH1D* h1 = (TH1D*) tf1.Get(hn);

	// normalize histograms
	Double_t norm = h0->GetEntries();
	h0->Scale(1/norm);
	norm = h1->GetEntries();
	h1->Scale(1/norm);
	
	TCanvas c;
	TLegend leg(.7, .8, .9, .9);
	leg.AddEntry(h0, "T Channel", "l");
	leg.AddEntry(h1, "TTBar", "l");
	h1->SetLineColor(8);
	h1->SetLineStyle(2);
	
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	h1->Draw();
	h0->Draw("SAME");
	leg.Draw();
	TString pname = dpath+hn+extension;
	//cout << "wrot"pname << endl;
	
	c.Print(pname);
}
