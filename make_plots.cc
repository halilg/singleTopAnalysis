{
	TFile T("TChannel-ele-histo.root");
	TH1D* h_topMass = T.Get("h_topMass");
	TCanvas c;
	h_topMass->Draw();
	c.Print("h_topMass.pdf");
}
