// example to calculate amplitudes in a test run

// Ejecutate $Time in linux

R__LOAD_LIBRARY(/media/roger/28721BB8721B8A28/root/TFGcode-main/3He_DSP_routines.C+);

void StepSize(string FileName = "", int step = 10){

	TH1D * signal = GetMovieRaw2root(FileName,"raw_0");
	
	TH1D * Smooth = SmoothWFM(signal,step);

	TH1D * Splitted_signal=SplitMovie(Smooth, 14.79e6, 15.00e6);






	TCanvas *C1 = new TCanvas("C1","",1000,900);
    Splitted_signal->Draw("Hist");
	TH1D * DerSignalsmooth = DerivativeWFM(Splitted_signal,1000);
	TCanvas *C2 = new TCanvas("C2","",1000,900);
    DerSignalsmooth->Draw("Hist");


	

}


	







 
