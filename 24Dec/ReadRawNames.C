// Test to see if we get the raw names right
// remember to check the library path

// There  is a problem, we have duplicated RawNames, we introduce a modification to only get the second one string.


R__LOAD_LIBRARY(/media/roger/28721BB8721B8A28/root/TFGcode-main/24Dec/3He_DSP_routines.C+);

#include <typeinfo>
void RawNames(string FileName=""){


    

    TFile *f = new TFile(FileName.c_str());

    std:: vector<const char*> Names;


    for (auto&& keyAsObj : *f->GetListOfKeys()){

        auto key = (TKey*) keyAsObj;

        Names.push_back(key->GetName());

        cout << key->GetName() << " " << key->GetClassName() << endl;
        cout << typeid(key->GetName()).name() << endl;

    }


// remove info TTre name
    Names.pop_back();
// Remove duplicate names (root files have a duplicate name tree for the metadata)
// primera iteració borra raw_0 0 per cada iteració es van reduint en 1 la posicio del index

    for(int i=0; i<Names.size();i++){

            Names.erase(Names.begin()+i);

        }


    for (const char* i: Names)

        std::cout << i << ' ';
    






}
