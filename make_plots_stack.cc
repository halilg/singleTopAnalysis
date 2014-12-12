void make_plots_stack(TString dpath, TString hn, TString extension){
	
	TFile tfdata("h-TreesEle_Data_2J_0T_noSyst.root");
	TFile tftch("h-TreesEle_TChannel_2J_0T_noSyst.root");
	TFile tftwch("h-TreesEle_TWChannel_2J_0T_noSyst.root");
	//TFile tfsch();
	TFile tfqcd("h-TreesEle_QCDEle_2J_0T_noSyst.root");
	TFile tfwj("h-TreesEle_WJets_2J_0T_noSyst.root");
	TFile tfzj("h-TreesEle_ZJets_2J_0T_noSyst.root");
	TFile tftt("h-TreesEle_TTBar_2J_0T_noSyst.root");
	//TFile tfdb();
	//TreesEle_ZZ_2J_0T_noSyst.root		TreesEle_WW_2J_0T_noSyst.root		TreesEle_WZ_2J_0T_noSyst.root
	
	
	cout << "accessing histograms\n";
	TH1D* hdata = (TH1D*) tfdata.Get(hn);
	TH1D* htch = (TH1D*) tftch.Get(hn); 
	TH1D* htwch = (TH1D*) tftwch.Get(hn); 
	TH1D* hqcd = (TH1D*) tfqcd.Get(hn); 
	TH1D* hwj = (TH1D*) tfwj.Get(hn); 
	TH1D* hzj = (TH1D*) tfzj.Get(hn); 
	TH1D* htt = (TH1D*) tftt.Get(hn); 

	//hdata->SetFillColor(kRed);
	htch->SetFillColor(kGreen);htch->SetLineColor(kGreen);;
	htwch->SetFillColor(kBlue);htwch->SetLineColor(kBlue);
	hqcd->SetFillColor(kOrange);hqcd->SetLineColor(kOrange);
	hwj->SetFillColor(kRed);hwj->SetLineColor(kRed);
	hzj->SetFillColor(kTeal);hzj->SetLineColor(kTeal);
	htt->SetFillColor(kAzure);htt->SetLineColor(kAzure);
	
	hdata->SetMarkerStyle(20);
	//htch->SetMarkerStyle(21);
	//htwch->SetMarkerStyle(21);
	//hqcd->SetMarkerStyle(21);
	//hwj->SetMarkerStyle(21);
	//hzj->SetMarkerStyle(21);
	//htt->SetMarkerStyle(21);

	//hdata->SetMarkerColor(kRed);	
	//htch->SetMarkerColor(kRed);	
	//htwch->SetMarkerColor(kRed);	
	//hqcd->SetMarkerColor(kRed);	
	//hwj->SetMarkerColor(kRed);	
	//hzj->SetMarkerColor(kRed);	
	//htt->SetMarkerColor(kRed);	
	
	THStack hs("hs","Stacked 1D histograms");
	
	htch->Scale(19700);
	hwj->Scale(19700);
	htt->Scale(19700);
	hzj->Scale(19700);
	hqcd->Scale(19700);
	htwch->Scale(19700);
	       
	hs.Add(htch);
	hs.Add(hwj);
	hs.Add(htt);
	hs.Add(hzj);
	hs.Add(hqcd);
	hs.Add(htwch);
	
	
	TCanvas c;
	TLegend leg(.7, .6, .9, .9);
	leg.AddEntry(hdata, "Data", "LP");
	leg.AddEntry(htch, "T-Channel", "l");
	leg.AddEntry(hwj, "W+Jets", "l");
	leg.AddEntry(htt, "TTBar", "l");
	leg.AddEntry(hzj, "Z+Jets", "l");
	leg.AddEntry(hqcd, "QCD", "l");
	leg.AddEntry(htwch, "TW-Channel", "l");
	
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(0);
	hdata->Draw("E1");
	hs.Draw("SAME");
	leg.Draw("SAME");
	//leg.Draw();
	TString pname = dpath+hn+extension;
	//cout << "wrot"pname << endl;
	c.Print(pname);
}
