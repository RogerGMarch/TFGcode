// Test to see if we get the raw names right
// remember to check the library path


R__LOAD_LIBRARY(/home/roger/Desktop/23Dec/3He_DSP_routines.C+);


void RawNames(string FileName=""){

    for (auto&& keyAsObj : file->GetListOfKeys()){


        auto key = (TKey*) keyAsObj;
        cout << key->GetName() << " " << key->GetClassName() << endl;


}




}