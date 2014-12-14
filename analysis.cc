#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TDirectoryFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH1I.h"
#include "analysis.h"
#include <algorithm>
#include <json/json.h>
#include <json2tchain.h>
#include <git_ref.h>

using namespace std;
int main(int argc, char **argv){
    Event myevent;
    Json::Value root;   // will contains the root value after parsing
    bool debug;
    debug=true;
    
    if (argc < 6){
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <events> <iroot file> <oroot file> <TDirectory> <TTree>" << std::endl;
        return 1;
    }
    Long64_t nevents = std::atoll(argv[1]);
    Long64_t wevents = 0;
    TString rjfile(argv[2]);
    TString orfile(argv[3]);
    TString tdir(argv[4]);
    TString ttree(argv[5]);

    TString treeName;
    TString stemp;
    treeName=tdir+"/"+ttree;
    TChain * T;
    bool use_weights=false;
    
    // is the input file a json file?
    if (debug) cout << "will analyze " << rjfile << endl;
    if (rjfile.Contains(".json")){
        T = json2tchain(treeName, rjfile);
        if (debug) cout << "received chain contains " <<  T->GetEntries() << " events" << endl;
    } else {
        T = new TChain(treeName);
        cout << "Opening root file: " << rjfile << endl;
        T->Add(rjfile);
    }
    
    cout << "Starting analysis\n";
    //cout << "Accessing tree: " << treeName << endl;
    //TTree* myTree = (TTree*)T.Get(treeName);
    TTree* myTree = T; //->GetTree();
    
    Long64_t nentries = myTree->GetEntries();
    if (nentries == 0){
        cerr << "ROOT tree had no events\n";
        return 1;
    }else{
        cout << "Entries in ROOT tree: " << nentries << endl;
    }
    
    // Create the output ROOT file and book the histograms
    TFile E(orfile,"recreate");
    TH1D h_metPt("h_metPt","MET; MET (GeV); Events", 50, 0, 150);
    TH1D h_topMass("h_topMass","Top Mass; Mass(GeV); Events", 50, 100, 250);
    TH1D h_leptonPt("h_leptonPt","; PT(GeV); Events", 50, 0, 250);
    TH1D h_fJetPt("h_fJetPt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_bJetPt("h_bJetPt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_firstJetPt("h_firstJetPt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_secondJetPt("h_secondJetPt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_looseJetPt("h_looseJetPt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_bJet1Pt("h_bJet1Pt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_bJet2Pt("h_bJet2Pt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_topPt("h_topPt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_top1Pt("h_top1Pt","; PT(GeV); Events", 50, 0, 250); //
    TH1D h_top2Pt("h_top2Pt","; PT(GeV); Events", 50, 0, 250); //
    
    //TH1D h_("h_","; PT(GeV); Events", 50, 0, 250); //
    //TH1D h_("h_","; PT(GeV); Events", 50, 0, 250); //
    //TH1D h_("h_","; PT(GeV); Events", 50, 0, 250); //
    //TH1D h_("h_","; PT(GeV); Events", 50, 0, 250); //
    
    TH1D h_leptonEta("h_leptonEta","; eta; Events", 50, 0, 6);
    TH1D h_leptonPhi("h_leptonPhi","; phi; Events", 50, -3.14, 3.14);
    //TH1D h_("h_","; (GeV); Events", 50, 100, 250);
    TH1D h_fJetEta("h_fJetEta","f Jet eta; eta; Events", 50, 0, 6);
    TH1D h_bJetEta("h_bJetEta","title;x;y",50,0,6);
    TH1D h_mtwMass("h_mtwMass","mtw; W Transverse Mass (GeV); Events", 40, 0, 200);
    TH1D h_Mlb1("h_Mlb1","b1b2Mass; (GeV); Events", 50, 100, 250);
    TH1D h_Mlb2("h_Mlb2","b1b2Mass; (GeV); Events", 50, 100, 250);
    TH1D h_b1b2Mass("h_b1b2Mass","b1b2Mass; (GeV); Events", 50, 100, 250);
    TH1D h_leptonDeltaCorrectedRelIso("h_leptonDeltaCorrectedRelIso","leptonRhoCorrectedRelIso; I; Events", 50, 0, 1);
    TH1D h_leptonRhoCorrectedRelIso("h_leptonRhoCorrectedRelIso","leptonRhoCorrectedRelIso; I; Events", 50, 0, 1);
    TH1I nVertices("h_nVertices"," nVertices ; Vertices ; Events", 51, 0, 50);//("h_","; ; Events", 50, 100, 250);
    TH1I nGoodVertices("h_nGoodVertices"," nGoodVertices ; Vertices ; Events", 51, 0, 50);//("h_","; ; Events", 50, 100, 250);
    
    cout << "Histograms created\n";
    
    // Set branch addresses.   
    myevent.register_branches(myTree);
    cout << "Branches set\n";
    
    // determine if electron or muon dataset
    myTree->GetEntry(0);
    bool isElectronDST = false;
    if (rjfile.Contains("TreesEle")) isElectronDST = true;
    if (isElectronDST) {cout << "electron dataset detected\n";} else {cout << "muon dataset detected\n";} 
    
    // determine the number of events to analyze
    Long64_t i;
    nevents= (nevents < nentries) ? nevents : nentries; // std::min(nevents,nentries);
    if (nevents == -1) nevents = nentries;
    
    Long64_t c0=0;
    Long64_t c1=0;
    Long64_t y=0;
    cout << "Will analyze " << nevents << " events\n 1000X:";
    for (i=1; i<nevents+1;i++) {
        if (i % 1000 == 0) cout << "+" << std::flush;
        myTree->GetEntry(i);
        if (!use_weights) myevent.weight=1;
        
        // selection
        bool selected=true;
        if (isElectronDST) { // electron dataset cuts
            if(selected){
                selected = (myevent.leptonPt > 30) &&
                           (fabs(myevent.leptonEta) < 2.5) &&
                           (fabs(myevent.leptonEta) < 1.44 || fabs(myevent.leptonEta) > 1.57) &&
                           (myevent.leptonRhoCorrectedRelIso < 0.1);
            }
            //cout << selected << "eta " << fabs(myevent.leptonEta) << ", pt " <<myevent.leptonPt << " iso: " << myevent.leptonRhoCorrectedRelIso << endl;
            //exit(0);
            if (selected){
                ++c0;
                selected = myevent.metPt > 45; // GeV
            }
            if (selected) ++c1;
        } else { // muon dataset cuts
            if(selected){
                selected = (myevent.leptonPt > 26) &&
                           (fabs(myevent.leptonEta) < 2.1) &&
                           (myevent.leptonDeltaCorrectedRelIso < 0.12);
                
            }
            if(selected){
                ++c0;
                selected = (myevent.mtwMass > 50); // GeV
            }
            if(selected) ++c1;
        }
        
        if (selected){
            ++y; // event yield
            wevents += myevent.weight;
            // fill histograms
            nVertices.Fill(myevent.nVertices, myevent.weight);
            nGoodVertices.Fill(myevent.nGoodVertices, myevent.weight);
            h_topMass.Fill(myevent.topMass, myevent.weight);
            h_leptonPt.Fill(myevent.leptonPt, myevent.weight);
            h_leptonEta.Fill(myevent.leptonEta, myevent.weight);
            h_leptonPhi.Fill(myevent.leptonPhi, myevent.weight);
            h_fJetEta.Fill(myevent.fJetEta, myevent.weight);
            h_bJetEta.Fill(myevent.bJetEta, myevent.weight);
            h_mtwMass.Fill(myevent.mtwMass, myevent.weight);
            h_metPt.Fill(myevent.metPt, myevent.weight);
            h_Mlb1.Fill(myevent.Mlb1, myevent.weight);
            h_Mlb2.Fill(myevent.Mlb2, myevent.weight);
            h_b1b2Mass.Fill(myevent.b1b2Mass, myevent.weight);
            h_leptonRhoCorrectedRelIso.Fill(myevent.leptonRhoCorrectedRelIso, myevent.weight);
            h_leptonDeltaCorrectedRelIso.Fill(myevent.leptonDeltaCorrectedRelIso, myevent.weight);
            h_fJetPt.Fill(myevent.fJetPt, myevent.weight);
            h_bJetPt.Fill(myevent.bJetPt, myevent.weight);
            h_firstJetPt.Fill(myevent.firstJetPt, myevent.weight);
            h_secondJetPt.Fill(myevent.secondJetPt, myevent.weight);
            h_looseJetPt.Fill(myevent.looseJetPt, myevent.weight);
            h_bJet1Pt.Fill(myevent.bJet1Pt, myevent.weight);
            h_bJet2Pt.Fill(myevent.bJet2Pt, myevent.weight);
            h_topPt.Fill(myevent.topPt, myevent.weight);
            h_top1Pt.Fill(myevent.top1Pt, myevent.weight);
            h_top2Pt.Fill(myevent.top2Pt, myevent.weight);
            
        }
        
   }
    cout << "\nAnalyzed " << i-1<< " entries\n";
    cout << "histograms written to: " << orfile << endl;
    //T.Close();
    E.Write();
    E.Close();
    
    // write report to JSON file
    root["git_ref"]=GIT_REF;
    root["root_file"]=rjfile.Data();
    root["root_tree_path"]=tdir.Data();
    root["root_tree_name"] = ttree.Data();
    root["events_total"] = nentries;
    root["events_analyzed"] = nevents;
    root["events_yield_w"] = wevents;
    root["events_yield"] = y;
    root["Selection"]["Cut_0"]["Description"] = "Kinematic cuts";
    root["Selection"]["Cut_0"]["Passed"] = c0;
    root["Selection"]["Cut_1"]["Description"] = (isElectronDST) ? "MET Cut" : "MTW Cut";
    root["Selection"]["Cut_1"]["Passed"] = c1;
    
    Json::StyledWriter writer;
    std::string outputConfig = writer.write( root );
    stemp=(rjfile.Remove(0,rjfile.Last('/')+1)).Data();
    stemp.ReplaceAll(".json","");
    stemp.ReplaceAll(".root","");
    stemp = "results/"+stemp + "-analysis.json";
    std::ofstream out(stemp);
    out << outputConfig << std::endl;
    out.close();
    std::cout << "analysis report written to: " << stemp << "\n";
    delete T; 
    return 0;
}

/*
 *store number in root file:
 *http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=11341
 *
 */