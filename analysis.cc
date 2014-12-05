#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TTree.h"
#include "TDirectoryFile.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH1I.h"
#include "analysis.h"
#include <algorithm>
#include <json/json.h>

using namespace std;
int main(int argc, char **argv){
    Event myevent;
    
    if (argc < 7){
        // Tell the user how to run the program
        std::cerr << "Usage: " << argv[0] << " <events> <iroot file> <oroot file> <TDirectory> <TTree> <output json file>" << std::endl;
        return 1;
    }
    Long64_t nevents = std::atoll(argv[1]);
    TString rfile(argv[2]);
    TString orfile(argv[3]);
    TString tdir(argv[4]);
    TString ttree(argv[5]);
    TString fnjson(argv[6]);

    cout << "Opening root file: " << rfile << endl;
    TFile T(rfile);
    
    if (! T.IsOpen() ){
        cout << "Cannot open root file: " << rfile << endl;
        return 1;
    }else{
        cout << "Done." << endl;
    }
    
    cout << "Starting analysis\n";
    TString treeName;
    treeName=tdir+"/"+ttree;
    cout << "Accessing tree: " << treeName << endl;
    TTree* myTree = (TTree*)T.Get(treeName);
    
    Long64_t nentries = myTree->GetEntries();
    cout << "Entries in ROOT tree: " << nentries << endl;
    
    // Create the output ROOT file and book the histograms
    TFile E(orfile,"recreate");
    TH1D h_metPt("h_metPt","MET; MET (GeV); Events", 50, 0, 250);
    TH1D h_topMass("h_topMass","Top Mass; Mass(GeV); Events", 50, 100, 250);
    TH1D h_leptonPt("h_leptonPt","; PT(GeV); Events", 50, 0, 250);
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
    
    Long64_t i;
    //cout << nevents << "-" << nentries << "-" << std::min(nevents,nentries) << endl;
    nevents= (nevents < nentries) ? nevents : nentries; // std::min(nevents,nentries);
    if (nevents == -1) nevents = nentries;
    cout << "Will analyze " << nevents << " events\n 1000X:";
    for (i=1; i<nevents+1;i++) {
        if (i % 1000 == 0) cout << "+" << std::flush;
        myTree->GetEntry(i);
        nVertices.Fill(myevent.nVertices);
        nGoodVertices.Fill(myevent.nGoodVertices);
        h_topMass.Fill(myevent.topMass);
        h_leptonPt.Fill(myevent.leptonPt);
        h_leptonEta.Fill(myevent.leptonEta);
        h_leptonPhi.Fill(myevent.leptonPhi);
        h_fJetEta.Fill(myevent.fJetEta);
        h_bJetEta.Fill(myevent.bJetEta);
        h_mtwMass.Fill(myevent.mtwMass);
        h_metPt.Fill(myevent.metPt);
        h_Mlb1.Fill(myevent.Mlb1);
        h_Mlb2.Fill(myevent.Mlb2);
        h_b1b2Mass.Fill(myevent.b1b2Mass);
        h_leptonRhoCorrectedRelIso.Fill(myevent.leptonRhoCorrectedRelIso);
        h_leptonDeltaCorrectedRelIso.Fill(myevent.leptonDeltaCorrectedRelIso);
        
   }
    cout << "\nAnalyzed " << i-1<< " entries\n";
    cout << "histograms written to: " << orfile << endl;
    T.Close();
    E.Write();
    E.Close();
    
    // write report to JSON file
    Json::Value root;   // will contains the root value after parsing
    root["root_file"]=rfile.Data();
    root["root_tree_path"]=tdir.Data();
    root["root_tree_name"] = ttree.Data();
    root["events_total"] = nentries;
    root["events_analyzed"] = nevents;
    root["Selection"]["Cut 1"] = 0;
    root["Selection"]["Cut 2"] = 0;
    root["Selection"]["Cut 3"] = 0;
    root["Selection"]["Cut 4"] = 0;
    
    Json::StyledWriter writer;
    std::string outputConfig = writer.write( root );
    std::ofstream out(fnjson.Data());
    out << outputConfig << std::endl;
    out.close();
    std::cout << "wrote " << fnjson.Data() << "\n";
    
    return 0;
}

/*
 *store number in root file:
 *http://root.cern.ch/phpBB3/viewtopic.php?f=3&t=11341
 *
 */