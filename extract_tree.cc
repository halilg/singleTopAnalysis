// ROOT macro to copy a TTree from a ROOT file to a new ROOT file
// Arguments: <path of source ROOT file> <TDirectory> <Name of TTree> <name of the output ROOT file>

void extract_tree(TString ifname, TString tdir, TString tree, TString ofname){
    TFile *oldfile = new TFile(ifname); //("MCeos/TTBar.root");
    cout << "opened " << ifname << endl;
    TTree *oldtree = (TTree*)oldfile->Get(tdir+"/"+tree);
    cout << "tree" << tdir << "/" << tree << " has " << oldtree->GetEntries() << " entries" << endl;
    //Event *event = new Event();
    //oldtree->SetBranchAddress("event",&event);
    //oldtree->SetBranchStatus("*",0);
    //oldtree->SetBranchStatus("event",1);
    //oldtree->SetBranchStatus("fNtrack",1);
    //oldtree->SetBranchStatus("fNseg",1);
    //oldtree->SetBranchStatus("fH",1); //Create a new file + a clone of old tree in new file
    TFile *newfile = new TFile(ofname,"recreate");
    cout << "cloning tree" << endl;
    TTree *newtree = oldtree->CloneTree();
    newtree->Print();
    newfile->Write();
    delete oldfile;
    delete newfile;
    cout << "wrote " << ofname << endl; 
}
