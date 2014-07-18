void make_plots(char * ifname){
	TFile T(ifname);
	if (! T.IsOpen() ){
		cout << "Couldn't open file: " << ifname << endl;
		return;
	}
	
	TIter nextkey(T.GetListOfKeys());
	TKey *key;
	TObject *obj;
	TCanvas c;
	while ((key=(TKey*)nextkey())) {
		obj = key->ReadObj();
		printf("at key:%s, object class:%s\n",key->GetName(),obj->ClassName());
		if (obj->InheritsFrom("TH1")){
			cout << "is histogram\n";
			obj->Draw();
			TString extension(".pdf");
			TString fname = key->GetName()+extension;
			c.Print(fname);
		}
		delete obj;
	}

}
