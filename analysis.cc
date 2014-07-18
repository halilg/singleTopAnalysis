# include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectoryFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH1I.h"
#include "analysis.h"

using namespace std;
int main(int argc, char **argv){
    Event myevent;
    if (argc < 2){
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <root file> <TDirectory> <TTree>" << std::endl;
        /* "Usage messages" are a conventional way of telling the user
         * how to run a program if they enter the command incorrectly.
         */
        return 1;
    }
   
/*  QCD_Ele.root
    SChannel.root
    SbarChannel.root
    TChannel.root
    TTBar.root
    TTBarFullLep.root
    TTBarSemiLep.root
    TWChannel.root
    TbarChannel.root
    TbarWChannel.root
    W1Jet.root
    W2Jets.root
    W3Jets.root
    W4Jets.root
    WJets.root
    WW.root
    WZ.root
    ZJets.root
    ZZ.root  */
   
   // TFile T("TChannel.root");
    TString fpath("~/eos/cms/store/group/phys_top/SingleTop/Trees/MC/");
    //TString fname("TChannel.root");
    TString fname("~/eos/cms/store/group/phys_top/SingleTop/Trees/MC/TTBarFullLep.root");
    cout << "Opening root file: " << fname << endl;
    TFile T(fname);
    
    if (! T.IsOpen() ){
        cout << "Cannot open root file: " << fname << endl;
        return 1;
    }else{
        cout << "Done." << endl;
    }
    
    cout << "Starting analysis\n";
    TString treeName("TreesEle/TTBar_2J_1T_noSyst");
    TTree* TChannel_2J_1T_noSyst = (TTree*)T.Get(treeName);
    
    Long64_t nentries = TChannel_2J_1T_noSyst->GetEntries();
    cout << "Entries: " << nentries << endl;

    
    
    
    TFile E("TChannel-ele-histo.root","recreate");
    TH1D h_topMass("h_topMass","Top Mass; Mass (GeV); Events", 50, 100, 250);
    TH1D h_leptonPt("h_leptonPt","; PT(GeV); Events", 50, 0, 250);
    TH1D h_leptonEta("h_leptonEta","; eta; Events", 50, 0, 6);
    TH1D h_leptonPhi("h_leptonPhi","; phi; Events", 50, -3.14, 3.14);
    //TH1D h_("h_","; (GeV); Events", 50, 100, 250);
    TH1D h_fJetEta("h_fJetEta","f Jet eta; eta; Events", 50, 0, 6);
    TH1D h_bJetEta("h_bJetEta","title;x;y",50,0,6);
    cout << "histos created\n";
    // Set branch addresses.   
   {
        TChannel_2J_1T_noSyst->SetBranchAddress("eta",&myevent.eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("costhetalj",&myevent.costhetalj);
        TChannel_2J_1T_noSyst->SetBranchAddress("costhetalbl",&myevent.costhetalbl);
        TChannel_2J_1T_noSyst->SetBranchAddress("costhetalj1",&myevent.costhetalj1);
        TChannel_2J_1T_noSyst->SetBranchAddress("costhetalbl1",&myevent.costhetalbl1);
        TChannel_2J_1T_noSyst->SetBranchAddress("costhetalj2",&myevent.costhetalj2);
        TChannel_2J_1T_noSyst->SetBranchAddress("costhetalbl2",&myevent.costhetalbl2);
        TChannel_2J_1T_noSyst->SetBranchAddress("Mlb1",&myevent.Mlb1);
        TChannel_2J_1T_noSyst->SetBranchAddress("Mlb2",&myevent.Mlb2);
        TChannel_2J_1T_noSyst->SetBranchAddress("b1b2Mass",&myevent.b1b2Mass);
        TChannel_2J_1T_noSyst->SetBranchAddress("b1b2Pt",&myevent.b1b2Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("mtwMass",&myevent.mtwMass);
        TChannel_2J_1T_noSyst->SetBranchAddress("charge",&myevent.charge);
        TChannel_2J_1T_noSyst->SetBranchAddress("runid",&myevent.runid);
        TChannel_2J_1T_noSyst->SetBranchAddress("lumiid",&myevent.lumiid);
        TChannel_2J_1T_noSyst->SetBranchAddress("eventid",&myevent.eventid);
        TChannel_2J_1T_noSyst->SetBranchAddress("weight",&myevent.weight);
        TChannel_2J_1T_noSyst->SetBranchAddress("totalWeight",&myevent.totalWeight);
        TChannel_2J_1T_noSyst->SetBranchAddress("bWeight",&myevent.bWeight);
        TChannel_2J_1T_noSyst->SetBranchAddress("bWeightBTagUp",&myevent.bWeightBTagUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("bWeightBTagDown",&myevent.bWeightBTagDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("bWeightMisTagUp",&myevent.bWeightMisTagUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("bWeightMisTagDown",&myevent.bWeightMisTagDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("PUWeight",&myevent.PUWeight);
        TChannel_2J_1T_noSyst->SetBranchAddress("PUWeightPUUp",&myevent.PUWeightPUUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("PUWeightPUDown",&myevent.PUWeightPUDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightMCTruth",&myevent.topPtReweightMCTruth);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweight",&myevent.topPtReweight);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonPt",&myevent.leptonPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonEta",&myevent.leptonEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonPhi",&myevent.leptonPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonDeltaCorrectedRelIso",&myevent.leptonDeltaCorrectedRelIso);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonRhoCorrectedRelIso",&myevent.leptonRhoCorrectedRelIso);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSF",&myevent.leptonSF);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFB",&myevent.leptonSFB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFC",&myevent.leptonSFC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFD",&myevent.leptonSFD);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDUp",&myevent.leptonSFIDUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDUpB",&myevent.leptonSFIDUpB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDUpC",&myevent.leptonSFIDUpC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDUpD",&myevent.leptonSFIDUpD);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDDown",&myevent.leptonSFIDDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDDownB",&myevent.leptonSFIDDownB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDDownC",&myevent.leptonSFIDDownC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIDDownD",&myevent.leptonSFIDDownD);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoUp",&myevent.leptonSFIsoUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoUpB",&myevent.leptonSFIsoUpB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoUpC",&myevent.leptonSFIsoUpC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoUpD",&myevent.leptonSFIsoUpD);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoDown",&myevent.leptonSFIsoDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoDownB",&myevent.leptonSFIsoDownB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoDownC",&myevent.leptonSFIsoDownC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFIsoDownD",&myevent.leptonSFIsoDownD);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigUp",&myevent.leptonSFTrigUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigUpB",&myevent.leptonSFTrigUpB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigUpC",&myevent.leptonSFTrigUpC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigUpD",&myevent.leptonSFTrigUpD);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigDown",&myevent.leptonSFTrigDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigDownB",&myevent.leptonSFTrigDownB);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigDownC",&myevent.leptonSFTrigDownC);
        TChannel_2J_1T_noSyst->SetBranchAddress("leptonSFTrigDownD",&myevent.leptonSFTrigDownD);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetPt",&myevent.fJetPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetE",&myevent.fJetE);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetEta",&myevent.fJetEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetPhi",&myevent.fJetPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetBtag",&myevent.fJetBtag);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetFlavour",&myevent.fJetFlavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetPUID",&myevent.fJetPUID);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetPUWP",&myevent.fJetPUWP);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetBeta",&myevent.fJetBeta);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetDZ",&myevent.fJetDZ);
        TChannel_2J_1T_noSyst->SetBranchAddress("fJetRMS",&myevent.fJetRMS);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetBeta",&myevent.bJetBeta);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetDZ",&myevent.bJetDZ);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetRMS",&myevent.bJetRMS);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetPt",&myevent.bJetPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetE",&myevent.bJetE);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetEta",&myevent.bJetEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetPhi",&myevent.bJetPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetBtag",&myevent.bJetBtag);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetFlavour",&myevent.bJetFlavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetPUID",&myevent.bJetPUID);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJetPUWP",&myevent.bJetPUWP);
        TChannel_2J_1T_noSyst->SetBranchAddress("firstJetPt",&myevent.firstJetPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("firstJetEta",&myevent.firstJetEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("firstJetPhi",&myevent.firstJetPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("firstJetE",&myevent.firstJetE);
        TChannel_2J_1T_noSyst->SetBranchAddress("firstJetBtag",&myevent.firstJetBtag);
        TChannel_2J_1T_noSyst->SetBranchAddress("firstJetFlavour",&myevent.firstJetFlavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("secondJetPt",&myevent.secondJetPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("secondJetEta",&myevent.secondJetEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("secondJetPhi",&myevent.secondJetPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("secondJetE",&myevent.secondJetE);
        TChannel_2J_1T_noSyst->SetBranchAddress("secondJetBtag",&myevent.secondJetBtag);
        TChannel_2J_1T_noSyst->SetBranchAddress("secondJetFlavour",&myevent.secondJetFlavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("looseJetPt",&myevent.looseJetPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("looseJetEta",&myevent.looseJetEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("looseJetPhi",&myevent.looseJetPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("looseJetE",&myevent.looseJetE);
        TChannel_2J_1T_noSyst->SetBranchAddress("looseJetBtag",&myevent.looseJetBtag);
        TChannel_2J_1T_noSyst->SetBranchAddress("looseJetFlavour",&myevent.looseJetFlavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet1Pt",&myevent.bJet1Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet1E",&myevent.bJet1E);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet1Eta",&myevent.bJet1Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet1Phi",&myevent.bJet1Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet1Btag",&myevent.bJet1Btag);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet1Flavour",&myevent.bJet1Flavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet2Pt",&myevent.bJet2Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet2E",&myevent.bJet2E);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet2Eta",&myevent.bJet2Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet2Phi",&myevent.bJet2Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet2Btag",&myevent.bJet2Btag);
        TChannel_2J_1T_noSyst->SetBranchAddress("bJet2Flavour",&myevent.bJet2Flavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("nJLoose",&myevent.nJLoose);
        TChannel_2J_1T_noSyst->SetBranchAddress("nJLooseCentral",&myevent.nJLooseCentral);
        TChannel_2J_1T_noSyst->SetBranchAddress("nJLooseForward",&myevent.nJLooseForward);
        TChannel_2J_1T_noSyst->SetBranchAddress("nJLooseMBTag",&myevent.nJLooseMBTag);
        TChannel_2J_1T_noSyst->SetBranchAddress("eventFlavour",&myevent.eventFlavour);
        TChannel_2J_1T_noSyst->SetBranchAddress("metPt",&myevent.metPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("metPhi",&myevent.metPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("HT",&myevent.HT);
        TChannel_2J_1T_noSyst->SetBranchAddress("H",&myevent.H);
        TChannel_2J_1T_noSyst->SetBranchAddress("topMass",&myevent.topMass);
        TChannel_2J_1T_noSyst->SetBranchAddress("top1Mass",&myevent.top1Mass);
        TChannel_2J_1T_noSyst->SetBranchAddress("top2Mass",&myevent.top2Mass);
        TChannel_2J_1T_noSyst->SetBranchAddress("topMtw",&myevent.topMtw);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPt",&myevent.topPt);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPhi",&myevent.topPhi);
        TChannel_2J_1T_noSyst->SetBranchAddress("topEta",&myevent.topEta);
        TChannel_2J_1T_noSyst->SetBranchAddress("topE",&myevent.topE);
        TChannel_2J_1T_noSyst->SetBranchAddress("top1Pt",&myevent.top1Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("top1Phi",&myevent.top1Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("top1Eta",&myevent.top1Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("top1E",&myevent.top1E);
        TChannel_2J_1T_noSyst->SetBranchAddress("top2Pt",&myevent.top2Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("top2Phi",&myevent.top2Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("top2Eta",&myevent.top2Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("top2E",&myevent.top2E);
        TChannel_2J_1T_noSyst->SetBranchAddress("ID",&myevent.ID);
        TChannel_2J_1T_noSyst->SetBranchAddress("MVAID",&myevent.MVAID);
        TChannel_2J_1T_noSyst->SetBranchAddress("nVertices",&myevent.nVertices);
        TChannel_2J_1T_noSyst->SetBranchAddress("nGoodVertices",&myevent.nGoodVertices);
        TChannel_2J_1T_noSyst->SetBranchAddress("totalEnergy",&myevent.totalEnergy);
        TChannel_2J_1T_noSyst->SetBranchAddress("totalMomentum",&myevent.totalMomentum);
        TChannel_2J_1T_noSyst->SetBranchAddress("lowBTag",&myevent.lowBTag);
        TChannel_2J_1T_noSyst->SetBranchAddress("highBTag",&myevent.highBTag);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_1_Pt",&myevent.MCTop_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_1_Phi",&myevent.MCTop_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_1_Eta",&myevent.MCTop_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_1_E",&myevent.MCTop_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_1_PdgId",&myevent.MCTop_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_1_MotherId",&myevent.MCTop_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_1_Pt",&myevent.MCTopLepton_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_1_Phi",&myevent.MCTopLepton_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_1_Eta",&myevent.MCTopLepton_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_1_E",&myevent.MCTopLepton_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_1_PdgId",&myevent.MCTopLepton_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_1_MotherId",&myevent.MCTopLepton_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_1_Pt",&myevent.MCTopNeutrino_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_1_Phi",&myevent.MCTopNeutrino_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_1_Eta",&myevent.MCTopNeutrino_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_1_E",&myevent.MCTopNeutrino_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_1_PdgId",&myevent.MCTopNeutrino_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_1_MotherId",&myevent.MCTopNeutrino_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_1_Pt",&myevent.MCTopQuark_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_1_Phi",&myevent.MCTopQuark_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_1_Eta",&myevent.MCTopQuark_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_1_E",&myevent.MCTopQuark_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_1_PdgId",&myevent.MCTopQuark_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_1_MotherId",&myevent.MCTopQuark_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_1_Pt",&myevent.MCTopQuarkBar_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_1_Phi",&myevent.MCTopQuarkBar_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_1_Eta",&myevent.MCTopQuarkBar_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_1_E",&myevent.MCTopQuarkBar_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_1_PdgId",&myevent.MCTopQuarkBar_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_1_MotherId",&myevent.MCTopQuarkBar_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_1_Pt",&myevent.MCTopBQuark_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_1_Phi",&myevent.MCTopBQuark_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_1_Eta",&myevent.MCTopBQuark_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_1_E",&myevent.MCTopBQuark_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_1_PdgId",&myevent.MCTopBQuark_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_1_MotherId",&myevent.MCTopBQuark_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_1_Pt",&myevent.MCTopW_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_1_Phi",&myevent.MCTopW_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_1_Eta",&myevent.MCTopW_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_1_E",&myevent.MCTopW_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_1_PdgId",&myevent.MCTopW_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_1_DauOneId",&myevent.MCTopW_1_DauOneId);
        TChannel_2J_1T_noSyst->SetBranchAddress("nMCTruthLeptons",&myevent.nMCTruthLeptons);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_2_Pt",&myevent.MCTop_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_2_Phi",&myevent.MCTop_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_2_Eta",&myevent.MCTop_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_2_E",&myevent.MCTop_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_2_PdgId",&myevent.MCTop_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTop_2_MotherId",&myevent.MCTop_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_2_Pt",&myevent.MCTopLepton_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_2_Phi",&myevent.MCTopLepton_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_2_Eta",&myevent.MCTopLepton_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_2_E",&myevent.MCTopLepton_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_2_PdgId",&myevent.MCTopLepton_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopLepton_2_MotherId",&myevent.MCTopLepton_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_2_Pt",&myevent.MCTopNeutrino_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_2_Phi",&myevent.MCTopNeutrino_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_2_Eta",&myevent.MCTopNeutrino_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_2_E",&myevent.MCTopNeutrino_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_2_PdgId",&myevent.MCTopNeutrino_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopNeutrino_2_MotherId",&myevent.MCTopNeutrino_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_2_Pt",&myevent.MCTopQuark_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_2_Phi",&myevent.MCTopQuark_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_2_Eta",&myevent.MCTopQuark_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_2_E",&myevent.MCTopQuark_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_2_PdgId",&myevent.MCTopQuark_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuark_2_MotherId",&myevent.MCTopQuark_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_2_Pt",&myevent.MCTopQuarkBar_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_2_Phi",&myevent.MCTopQuarkBar_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_2_Eta",&myevent.MCTopQuarkBar_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_2_E",&myevent.MCTopQuarkBar_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_2_PdgId",&myevent.MCTopQuarkBar_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopQuarkBar_2_MotherId",&myevent.MCTopQuarkBar_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_2_Pt",&myevent.MCTopBQuark_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_2_Phi",&myevent.MCTopBQuark_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_2_Eta",&myevent.MCTopBQuark_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_2_E",&myevent.MCTopBQuark_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_2_PdgId",&myevent.MCTopBQuark_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopBQuark_2_MotherId",&myevent.MCTopBQuark_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_2_Pt",&myevent.MCTopW_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_2_Phi",&myevent.MCTopW_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_2_Eta",&myevent.MCTopW_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_2_E",&myevent.MCTopW_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_2_PdgId",&myevent.MCTopW_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCTopW_2_DauOneId",&myevent.MCTopW_2_DauOneId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_1_Pt",&myevent.MCQuark_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_1_Phi",&myevent.MCQuark_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_1_Eta",&myevent.MCQuark_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_1_E",&myevent.MCQuark_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_1_PdgId",&myevent.MCQuark_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_1_MotherId",&myevent.MCQuark_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_2_Pt",&myevent.MCQuark_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_2_Phi",&myevent.MCQuark_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_2_Eta",&myevent.MCQuark_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_2_E",&myevent.MCQuark_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_2_PdgId",&myevent.MCQuark_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_2_MotherId",&myevent.MCQuark_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_3_Pt",&myevent.MCQuark_3_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_3_Phi",&myevent.MCQuark_3_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_3_Eta",&myevent.MCQuark_3_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_3_E",&myevent.MCQuark_3_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_3_PdgId",&myevent.MCQuark_3_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_3_MotherId",&myevent.MCQuark_3_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_4_Pt",&myevent.MCQuark_4_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_4_Phi",&myevent.MCQuark_4_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_4_Eta",&myevent.MCQuark_4_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_4_E",&myevent.MCQuark_4_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_4_PdgId",&myevent.MCQuark_4_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_4_MotherId",&myevent.MCQuark_4_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_5_Pt",&myevent.MCQuark_5_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_5_Phi",&myevent.MCQuark_5_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_5_Eta",&myevent.MCQuark_5_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_5_E",&myevent.MCQuark_5_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_5_PdgId",&myevent.MCQuark_5_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_5_MotherId",&myevent.MCQuark_5_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_6_Pt",&myevent.MCQuark_6_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_6_Phi",&myevent.MCQuark_6_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_6_Eta",&myevent.MCQuark_6_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_6_E",&myevent.MCQuark_6_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_6_PdgId",&myevent.MCQuark_6_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_6_MotherId",&myevent.MCQuark_6_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_7_Pt",&myevent.MCQuark_7_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_7_Phi",&myevent.MCQuark_7_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_7_Eta",&myevent.MCQuark_7_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_7_E",&myevent.MCQuark_7_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_7_PdgId",&myevent.MCQuark_7_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_7_MotherId",&myevent.MCQuark_7_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_8_Pt",&myevent.MCQuark_8_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_8_Phi",&myevent.MCQuark_8_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_8_Eta",&myevent.MCQuark_8_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_8_E",&myevent.MCQuark_8_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_8_PdgId",&myevent.MCQuark_8_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_8_MotherId",&myevent.MCQuark_8_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_9_Pt",&myevent.MCQuark_9_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_9_Phi",&myevent.MCQuark_9_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_9_Eta",&myevent.MCQuark_9_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_9_E",&myevent.MCQuark_9_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_9_PdgId",&myevent.MCQuark_9_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_9_MotherId",&myevent.MCQuark_9_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_10_Pt",&myevent.MCQuark_10_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_10_Phi",&myevent.MCQuark_10_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_10_Eta",&myevent.MCQuark_10_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_10_E",&myevent.MCQuark_10_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_10_PdgId",&myevent.MCQuark_10_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_10_MotherId",&myevent.MCQuark_10_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_11_Pt",&myevent.MCQuark_11_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_11_Phi",&myevent.MCQuark_11_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_11_Eta",&myevent.MCQuark_11_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_11_E",&myevent.MCQuark_11_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_11_PdgId",&myevent.MCQuark_11_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_11_MotherId",&myevent.MCQuark_11_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_12_Pt",&myevent.MCQuark_12_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_12_Phi",&myevent.MCQuark_12_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_12_Eta",&myevent.MCQuark_12_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_12_E",&myevent.MCQuark_12_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_12_PdgId",&myevent.MCQuark_12_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCQuark_12_MotherId",&myevent.MCQuark_12_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_1_Pt",&myevent.MCBQuark_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_1_Phi",&myevent.MCBQuark_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_1_Eta",&myevent.MCBQuark_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_1_E",&myevent.MCBQuark_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_1_PdgId",&myevent.MCBQuark_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_1_MotherId",&myevent.MCBQuark_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_1_Pt",&myevent.MCLepton_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_1_Phi",&myevent.MCLepton_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_1_Eta",&myevent.MCLepton_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_1_E",&myevent.MCLepton_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_1_PdgId",&myevent.MCLepton_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_1_MotherId",&myevent.MCLepton_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_1_Pt",&myevent.MCNeutrino_1_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_1_Phi",&myevent.MCNeutrino_1_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_1_Eta",&myevent.MCNeutrino_1_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_1_E",&myevent.MCNeutrino_1_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_1_PdgId",&myevent.MCNeutrino_1_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_1_MotherId",&myevent.MCNeutrino_1_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_2_Pt",&myevent.MCBQuark_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_2_Phi",&myevent.MCBQuark_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_2_Eta",&myevent.MCBQuark_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_2_E",&myevent.MCBQuark_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_2_PdgId",&myevent.MCBQuark_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_2_MotherId",&myevent.MCBQuark_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_2_Pt",&myevent.MCLepton_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_2_Phi",&myevent.MCLepton_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_2_Eta",&myevent.MCLepton_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_2_E",&myevent.MCLepton_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_2_PdgId",&myevent.MCLepton_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_2_MotherId",&myevent.MCLepton_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_2_Pt",&myevent.MCNeutrino_2_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_2_Phi",&myevent.MCNeutrino_2_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_2_Eta",&myevent.MCNeutrino_2_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_2_E",&myevent.MCNeutrino_2_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_2_PdgId",&myevent.MCNeutrino_2_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_2_MotherId",&myevent.MCNeutrino_2_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_3_Pt",&myevent.MCBQuark_3_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_3_Phi",&myevent.MCBQuark_3_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_3_Eta",&myevent.MCBQuark_3_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_3_E",&myevent.MCBQuark_3_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_3_PdgId",&myevent.MCBQuark_3_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_3_MotherId",&myevent.MCBQuark_3_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_3_Pt",&myevent.MCLepton_3_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_3_Phi",&myevent.MCLepton_3_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_3_Eta",&myevent.MCLepton_3_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_3_E",&myevent.MCLepton_3_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_3_PdgId",&myevent.MCLepton_3_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_3_MotherId",&myevent.MCLepton_3_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_3_Pt",&myevent.MCNeutrino_3_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_3_Phi",&myevent.MCNeutrino_3_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_3_Eta",&myevent.MCNeutrino_3_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_3_E",&myevent.MCNeutrino_3_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_3_PdgId",&myevent.MCNeutrino_3_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_3_MotherId",&myevent.MCNeutrino_3_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_4_Pt",&myevent.MCBQuark_4_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_4_Phi",&myevent.MCBQuark_4_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_4_Eta",&myevent.MCBQuark_4_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_4_E",&myevent.MCBQuark_4_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_4_PdgId",&myevent.MCBQuark_4_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCBQuark_4_MotherId",&myevent.MCBQuark_4_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_4_Pt",&myevent.MCLepton_4_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_4_Phi",&myevent.MCLepton_4_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_4_Eta",&myevent.MCLepton_4_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_4_E",&myevent.MCLepton_4_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_4_PdgId",&myevent.MCLepton_4_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCLepton_4_MotherId",&myevent.MCLepton_4_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_4_Pt",&myevent.MCNeutrino_4_Pt);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_4_Phi",&myevent.MCNeutrino_4_Phi);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_4_Eta",&myevent.MCNeutrino_4_Eta);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_4_E",&myevent.MCNeutrino_4_E);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_4_PdgId",&myevent.MCNeutrino_4_PdgId);
        TChannel_2J_1T_noSyst->SetBranchAddress("MCNeutrino_4_MotherId",&myevent.MCNeutrino_4_MotherId);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight1",&myevent.PDFWeight1);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight2",&myevent.PDFWeight2);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight3",&myevent.PDFWeight3);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight4",&myevent.PDFWeight4);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight5",&myevent.PDFWeight5);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight6",&myevent.PDFWeight6);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight7",&myevent.PDFWeight7);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight8",&myevent.PDFWeight8);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight9",&myevent.PDFWeight9);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight10",&myevent.PDFWeight10);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight11",&myevent.PDFWeight11);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight12",&myevent.PDFWeight12);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight13",&myevent.PDFWeight13);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight14",&myevent.PDFWeight14);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight15",&myevent.PDFWeight15);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight16",&myevent.PDFWeight16);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight17",&myevent.PDFWeight17);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight18",&myevent.PDFWeight18);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight19",&myevent.PDFWeight19);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight20",&myevent.PDFWeight20);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight21",&myevent.PDFWeight21);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight22",&myevent.PDFWeight22);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight23",&myevent.PDFWeight23);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight24",&myevent.PDFWeight24);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight25",&myevent.PDFWeight25);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight26",&myevent.PDFWeight26);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight27",&myevent.PDFWeight27);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight28",&myevent.PDFWeight28);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight29",&myevent.PDFWeight29);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight30",&myevent.PDFWeight30);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight31",&myevent.PDFWeight31);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight32",&myevent.PDFWeight32);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight33",&myevent.PDFWeight33);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight34",&myevent.PDFWeight34);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight35",&myevent.PDFWeight35);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight36",&myevent.PDFWeight36);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight37",&myevent.PDFWeight37);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight38",&myevent.PDFWeight38);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight39",&myevent.PDFWeight39);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight40",&myevent.PDFWeight40);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight41",&myevent.PDFWeight41);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight42",&myevent.PDFWeight42);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight43",&myevent.PDFWeight43);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight44",&myevent.PDFWeight44);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight45",&myevent.PDFWeight45);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight46",&myevent.PDFWeight46);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight47",&myevent.PDFWeight47);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight48",&myevent.PDFWeight48);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight49",&myevent.PDFWeight49);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight50",&myevent.PDFWeight50);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight51",&myevent.PDFWeight51);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight52",&myevent.PDFWeight52);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight_MSTW",&myevent.PDFWeight_MSTW);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight_NNPDF21",&myevent.PDFWeight_NNPDF21);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight_GJR_FV",&myevent.PDFWeight_GJR_FV);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight_GJR_FF",&myevent.PDFWeight_GJR_FF);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight_GJR_FDIS",&myevent.PDFWeight_GJR_FDIS);
        TChannel_2J_1T_noSyst->SetBranchAddress("PDFWeight_HERAPDF",&myevent.PDFWeight_HERAPDF);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightMCTruthNorm",&myevent.topPtReweightMCTruthNorm);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightNorm",&myevent.topPtReweightNorm);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightMCTruthNormUp",&myevent.topPtReweightMCTruthNormUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightNormUp",&myevent.topPtReweightNormUp);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightMCTruthNormDown",&myevent.topPtReweightMCTruthNormDown);
        TChannel_2J_1T_noSyst->SetBranchAddress("topPtReweightNormDown",&myevent.topPtReweightNormDown);
   }
    cout << "Branches set\n";
   for (Long64_t i=0; i<nentries;i++) {
        TChannel_2J_1T_noSyst->GetEntry(i);
        h_topMass.Fill(myevent.topMass);
        h_leptonPt.Fill(myevent.leptonPt);
        h_leptonEta.Fill(myevent.leptonEta);
        h_leptonPhi.Fill(myevent.leptonPhi);
        h_fJetEta.Fill(myevent.fJetEta);
        h_bJetEta.Fill(myevent.bJetEta);
   }
    cout << "Analyzed " << nentries << " entries\n";
    T.Close();
    E.Write();
    E.Close();
    return 0;
}