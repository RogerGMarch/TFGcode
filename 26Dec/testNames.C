R__LOAD_LIBRARY(/home/roger/Desktop/24Dec/3He_DSP_routines.C+);



void testraw(string FileName = ""){



    cout<<"it's fine"<<endl;


    // problema con libreria????
    
    vector<basic_string<char> > Nam = RawNames(FileName);


    cout<< Nam.at(1) << endl;


    for(int i=0; i<Nam.size(); i++){
        cout<<i<<endl;
    }



}
