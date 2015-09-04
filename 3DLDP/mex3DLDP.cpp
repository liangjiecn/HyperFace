#include <iostream>

#include "mex.h"
#include "LDP.h"

using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	// nlhs
	// Number of expected output mxArrays
	// plhs
	// Array of pointers to the expected output mxArrays
	// nrhs
	// Number of input mxArrays
	// prhs
	// Array of pointers to the input mxArrays.Do not modify any prhs values in your MEX-file.Changing the data in these read-only mxArrays can             produce undesired side effects.

	// [ldpHist, ldpData] = mexLDP(image, subImageSize, order)
    if(nrhs != 3)
        mexErrMsgTxt("Invalid number of parameters");

    if(mxGetClassID(prhs[0]) != mxUINT8_CLASS || mxGetClassID(prhs[1]) != mxDOUBLE_CLASS || mxGetClassID(prhs[2]) != mxDOUBLE_CLASS)
        mexErrMsgTxt("Expected UINT8 image, DOUBLE subImageSize and DOUBLE order");

	//define input
    uint8_t *im;
	const int *dimim;
	int NumofRows, NumofColumns, NumofBands, width, height, length;
	int subWidth, subHeight, subLength;
	Int3DPoint imageSize;
	Int3DPoint subImageSize;
	int numBin;
	int order;

	//parse input
	im = (uint8_t*)mxGetData(prhs[0]);
	// data is transposed (rows lie in y direction, cols lie in x direction), but accesses should be aligned correctly nonetheless
	dimim = mxGetDimensions(prhs[0]);
	NumofRows = dimim[0];
	NumofColumns = dimim[1];
	NumofBands = dimim[2];
	width = NumofColumns;
	height = NumofRows;
	length = NumofBands;
    subWidth = (int)mxGetPr(prhs[1])[0];
	subHeight = (int)mxGetPr(prhs[1])[1];
	subLength= (int)mxGetPr(prhs[1])[2];
	/*if(((width / subWidth) * subWidth != width) || ((height / subHeight) * subHeight != height))
	mexErrMsgTxt("Subimage size must divide the image size evenly");*/
	order = (int)mxGetScalar(prhs[2]);
	if(order > 4 || order < 2)
		mexErrMsgTxt("LDP Order must be between 2 and 4, inclusive");
    imageSize.x = width;
	imageSize.y = height;
	imageSize.z = length;
    subImageSize.x = subWidth;
	subImageSize.y = subHeight;
	subImageSize.z = subLength;
    numBin = 16; // HIST_BIN_NUM;
	int pos = 0;

	//define output
	mxArray *ldpDataMat = mxCreateNumericMatrix(NumofRows, NumofColumns * NumofBands *3,  mxUINT8_CLASS, mxREAL);
	uint8_t *ldpData = (uint8_t*)mxGetData(ldpDataMat);

	mxArray *derivativeDataMat = mxCreateNumericMatrix(NumofRows, NumofColumns * NumofBands *3,  mxINT16_CLASS, mxREAL);
	int16_t *derivativeData = (int16_t*)mxGetData(derivativeDataMat);


	mxArray *ldpHistMat = mxCreateNumericMatrix(3* ((width / subWidth) * (height / subHeight) * (length / subLength)* numBin), 1, mxSINGLE_CLASS, mxREAL);
	HIST_BIN_TYPE *ldpHistData = (HIST_BIN_TYPE*)mxGetData(ldpHistMat);


	//process
	CLDP ldp(width, height, length);

   // ldp.LdpFeatureExtraction(im, ldpData, imageSize); //normal mode
	ldp.LdpFeatureExtraction(im, derivativeData, ldpData, imageSize); //debug mode with derivative information
    bool histOk = !!ldp.LdpHistogramConstruction(ldpData, ldpHistData, imageSize, subImageSize, numBin);
    
	  plhs[0] = ldpHistMat;
	if(nlhs == 1)
	{
		mxDestroyArray(ldpDataMat);
		mxDestroyArray(derivativeDataMat);
	}
    else if(nlhs == 2)
    {    
		plhs[1] = ldpDataMat;
		mxDestroyArray(derivativeDataMat);
	}
	else if(nlhs == 3)
	{
		plhs[1] = ldpDataMat;
	    plhs[2] = derivativeDataMat;
	}

	
//		mxDestroyArray(ldpDataMat);


    if(!histOk)
        mexErrMsgTxt("Error in parameters to LdpHistogramConstruction");

}
