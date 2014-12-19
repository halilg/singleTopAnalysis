#include <iostream>
#include <fstream>
#include <string>
#include <TError.h>
#include <TString.h>
#include <TFile.h>
#include <THStack.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TStyle.h>
#include <cfgreader.h>

using namespace std;
void make_plots_stack(TString dpath, TString category, TString hn, TString extension){
	gErrorIgnoreLevel=2000; // suppress info messages
	cfgreader cfg("analysis.cfg");
	TFile tfdata("root/h-TreesEle_Data_"+category+".root");
	TFile tftch("root/h-TreesEle_TChannel_"+category+".root");
	TFile tftwch("root/h-TreesEle_TWChannel_"+category+".root");
	//TFile tfsch();
	TFile tfqcd("root/h-TreesEle_QCDEle_"+category+".root");
	TFile tfwj("root/h-TreesEle_WJets_"+category+".root");
	TFile tfzj("root/h-TreesEle_ZJets_"+category+".root");
	TFile tftt("root/h-TreesEle_TTBar_"+category+".root");
	//TFile tfdb();
	//TreesEle_ZZ_2J_0T_noSyst.root		TreesEle_WW_2J_0T_noSyst.root		TreesEle_WZ_2J_0T_noSyst.root

	// read weights from configuration
	//cout << cfg.root["weights"]["TChannel"][category].asFloat() << endl;
	
	bool debug=false;
	if (debug) cout << "accessing histograms\n";
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
	
	htch->Scale(cfg.root["weights"]["TChannel"][category].asFloat());
	hwj->Scale(cfg.root["weights"]["WJets"][category].asFloat());
	htt->Scale(cfg.root["weights"]["TTBar"][category].asFloat());
	hzj->Scale(cfg.root["weights"]["ZJets"][category].asFloat());
	hqcd->Scale(cfg.root["weights"]["QCDEle"][category].asFloat());
	htwch->Scale(cfg.root["weights"]["TWChannel"][category].asFloat());
	hdata->Scale(cfg.root["weights"]["Data"][category].asFloat());
	
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
	TString pname = dpath+hn+"_"+category+"."+extension;
	c.Print(pname);
	cout << "wrote " << pname << endl;
}

int main(int argc, char **argv){
	if (argc < 5){
        // Tell the user how to run the program
		std::cerr << "Usage: " << argv[0] << " <dpath> <category> <histogram> <plot file extension>" << std::endl;
		return 1;
	}
	TString dpath(argv[1]);
	TString category(argv[2]);
	TString hn(argv[3]);
	TString extension(argv[4]);
	make_plots_stack(dpath, category, hn, extension);
}