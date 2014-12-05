{
    TFile *oldfile = new TFile("~/eos/cms/store/group/phys_top/SingleTop/Trees/MC/TChannel.root");
    oldfile->cd("TreesEle");
    TTree *oldtree = TChannel_2J_1T_noSyst; //(TTree*)oldfile->Get("TChannel_2J_1T_noSyst");
    //Event *event = new Event();
    //oldtree->SetBranchAddress("event",&event);
    //oldtree->SetBranchStatus("*",0);
    //oldtree->SetBranchStatus("event",1);
    //oldtree->SetBranchStatus("fNtrack",1);
    //oldtree->SetBranchStatus("fNseg",1);
    //oldtree->SetBranchStatus("fH",1); //Create a new file + a clone of old tree in new file
    TFile *newfile = new TFile("small.root","recreate");
    TTree *newtree = oldtree->CloneTree();
    newtree->Print();
    newfile->Write();
    delete oldfile;
    delete newfile;
}
