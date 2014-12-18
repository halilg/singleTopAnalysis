#include <TError.h>
void make_plots(TString ifname, TString opath){
	gErrorIgnoreLevel=2000;
	TFile T(ifname);
	if (! T.IsOpen() ){
		cerr << "Couldn't open file: " << ifname << endl;
		exit(1);
	}
	
	TIter nextkey(T.GetListOfKeys());
	TKey *key;
	TObject *obj;
	TCanvas c;
	int cnt=0;
	while ((key=(TKey*)nextkey())) {
		obj = key->ReadObj();
		//printf("at key:%s, object class:%s\n",key->GetName(),obj->ClassName());
		if (obj->InheritsFrom("TH1")){
			//cout << "is histogram\n";
			obj->Draw();
			TString extension(".pdf");
			TString fname = opath + "/" + key->GetName()+extension;
			c.Print(fname);
			++cnt;
		}
		delete obj;
	}
	cout << "Wrote " << cnt << " plots to " << opath << "/" << endl;
}

