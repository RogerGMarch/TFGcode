// example to calculate amplitudes in a test run

// Ejecutate $Time in linux

R__LOAD_LIBRARY(/home/roger/Desktop/22Dec/3He_DSP_routines.C+);


Double_t fline(Double_t *x, Double_t *par)
	{
		Bool_t reject;
		int pini, pfin;

		if (reject && x[0] > pini && x[0] < pfin) {
			TF1::RejectPoint();
			return 0;
		}
		return par[0] + par[1]*x[0];
	}



// Read signal and apply basic smoothing
void testRoger1(string FileName="",
          string treeName=""){
//Signal preprocessing: double smoothing on signal
        TH1D * signal=GetMovieRaw2root(FileName, treeName);

	TH1D * Splitted_signal=SplitMovie(signal, 20e6, 20.400e6);

        TCanvas *C1 = new TCanvas("C1","",1000,900);
        C1->cd();
        C1->SetFrameFillColor(1);

        Splitted_signal->Draw("HIST SAME");
}
// function

void amplitud(string FileName="",
          string treeName=""){
// Variables definition

		TH1D * signal=GetMovieRaw2root(FileName,treeName);

		TH1D * signalmovie=SplitMovie(signal,20e6,21e6);	
		
        	TCanvas *C1 = new TCanvas("C1","",1000,900);
        	C1->cd();
        	C1->SetFrameFillColor(1);

        	signalmovie->Draw("HIST SAME");



// Looking for amplitudes in the movie
		int trigger;
		int PreSamples;
		int IntegrationLength;
		int p1, p2, p3, p4;
		Bool_t reject;
		int pini, pfin;
		double constant, slope;
		


		trigger = 300e3;
		PreSamples = 0;
		IntegrationLength = 500e3;

		

		TH1D* hEM = AmplitudeWFM(signalmovie,trigger,PreSamples,IntegrationLength+PreSamples);
// Fit
		p2 = PreSamples;
		p1 = 0;
		p3 = IntegrationLength;
		p4 = IntegrationLength + PreSamples;



		TF1 *fl = new TF1("fl",fline,p1,p4,2);

		pini = p2;
		pfin = p3;

		reject = kTRUE;
		hEM->Fit(fl,"0");
	
		reject = kFALSE;

		TF1 *fleft = new TF1("fleft",fline,p1,p2,2);
		fleft->SetParameters(fl->GetParameters());

		hEM->GetListOfFunctions()->Add(fleft);
		gROOT->GetListOfFunctions()->Remove(fleft);

		TF1 *fright = new TF1("fright",fline,p2,p4,2);
		fright->SetParameters(fl->GetParameters());

		hEM->GetListOfFunctions()->Add(fright);
		gROOT->GetListOfFunctions()->Remove(fright);


		constant = fl->GetParameter(0);
		slope = fl->GetParameter(1);

	// Variables of the Fit

		std::cout << "constant: " << constant << endl;
		std::cout << "slope: " << slope << endl;

//varaibles amplitudes

		double Amp,Area,content_BaseLine,content_hEMC;

		TH1D* hEMC = new TH1D("hEMC","hEMC",PreSamples+IntegrationLength,0,PreSamples+IntegrationLength);	

// Fills hEMC
		for (int j=1;j<=(IntegrationLength+PreSamples); j++){

			content_hEMC = hEM->GetBinContent(j);
			content_BaseLine = slope*j+constant;

			hEMC->SetBinContent(j, content_hEMC - content_BaseLine);
		}

// Amplitude
		Amp = hEMC->GetMaximum();
		std::cout << "Amplitude: " << Amp << endl;
// Area
		Area = hEMC->Integral(p2,p3);
		std::cout << "Area: " << Area << endl;
		// Fills the histograms

}

void AmplitudMovie(string FileName="",
          string treeName=""){

/// Files

	ofstream DataFile
	DataFile.open("dataAmp.txt",ofstream::app);


/// Declaració de Variables

	std:: vector<double> Events;
	std:: int NumberEvents

	int trigger, PreSamples, IntegrationLength;
	int p1, p2, p3, p4;
	Bool_t reject;
	int pini, pfin;
	double constant, slope;


	TH1D* AreaHisto = new TH1D("AreaHisto","AreaHisto",500,0.);
	TH1D* AmplitudeHisto = new TH1D("AmplitudeHisto","AmplitudeHisto", 500,0.);

/// Iniciem clock per tenir un idea del que tardara

     struct timeval begin, end;
    gettimeofday(&begin, 0)

/// Lectura de Fitxers i filtres

	TH1D * signal=GetMovieRaw2root(FileName,treeName);
	TH1D * signalmovie=SplitMovie(signal,20e6,21e6);
	TH1D* dersignal = DerivativeWFM(signalmovie,250);


/// Codi

	double Threshold = getProjectionThreshold(dersignal);

 	std::cout << "Threshold: " << Threshold << endl;
// number Events


	Events = TimeStamp(dersignal,Threshold);
	NumberEvents = Events.Size()

// Calculem amplitud i restem linea de base per cada timestamp


	PreSamples = 0;
	IntegrationLength = 500e3;

	for(int i = 0; i<NumberEvents; i++){

		// Looking for amplitudes in the movie

		trigger = Events.at(i);


		TH1D* hEM = AmplitudeWFM(signalmovie,trigger,PreSamples,IntegrationLength+PreSamples);
// Fit
		p2 = PreSamples;
		p1 = 0;
		p3 = IntegrationLength;
		p4 = IntegrationLength + PreSamples;



		TF1 *fl = new TF1("fl",fline,p1,p4,2);

		pini = p2;
		pfin = p3;

		reject = kTRUE;
		hEM->Fit(fl,"0");
	
		reject = kFALSE;

		TF1 *fleft = new TF1("fleft",fline,p1,p2,2);
		fleft->SetParameters(fl->GetParameters());

		hEM->GetListOfFunctions()->Add(fleft);
		gROOT->GetListOfFunctions()->Remove(fleft);

		TF1 *fright = new TF1("fright",fline,p2,p4,2);
		fright->SetParameters(fl->GetParameters());

		hEM->GetListOfFunctions()->Add(fright);
		gROOT->GetListOfFunctions()->Remove(fright);


		constant = fl->GetParameter(0);
		slope = fl->GetParameter(1);

	// Variables of the Fit

		std::cout << "constant: " << constant << endl;
		std::cout << "slope: " << slope << endl;

//varaibles amplitudes

		double Amp,Area,content_BaseLine,content_hEMC;

		TH1D* hEMC= new TH1D("hEMC","hEMC",PreSamples+IntegrationLength,0,PreSamples+IntegrationLength);	

// Fills hEMC
		for (int j=1;j<=(IntegrationLength+PreSamples); j++){

			content_hEMC = hEM->GetBinContent(j);
			content_BaseLine = slope*j+constant;

			hEMC->SetBinContent(j, content_hEMC - content_BaseLine);
		}

// Amplitude
		Amp = hEMC->GetMaximum();
		std::cout << "Amplitude: " << Amp << endl;
// Area
		Area = hEMC->Integral(p2,p3);
		std::cout << "Area: " << Area << endl;


		AreaHisto->Fill(Area);
		AmplitudeHisto->Fill(Amp);

/// Probar con y sin suavizado 


/// guardalo en un file
	DataFile << file << ";" << EventTS.at(i) << ";" << Area << ";" << Amp << endl;


	}





	

/// Guardem les amplituds en un fitxer

/// Visualitzacions

    TCanvas *C1 = new TCanvas("C1","",1000,900);
    C1->cd();
    C1->SetFrameFillColor(1);

    dersignal->Draw("HIST SAME");



	// Stop measuring time and calculate the elapsed time
    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    
    printf("Result: %.20f\n", sum);
    
    printf("Time measured: %.3f seconds.\n", elapsed);
	
}

	

	






	







 
