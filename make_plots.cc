{
	TFile T("TChannel-ele-histo.root");
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
	/*
	TH1D* h_topMass = T.Get("h_topMass");
	
	h_topMass->Draw();
	c.Print("h_topMass.pdf");
	*/
}
