/******************************************************************************
 * Filename:      LDP.cpp                                                       *
 * Date:          13/05/2014                                                  *
 * Programmer:    Jie Liang				                                      *
 * Description:   interface for the 3D Local Derivative Pattern class         *
 * Compiler:                                       *
 * Copyright:     Computer Vision & Image Processing Lab                      *
 *                Institute for Integrated and Intelligent Systems (IIIS)     *
 *                Griffith University, Nathan Campus                          *
 *                Queensland 4111                                             *
 *                Australia                                                   *
 * Revisions:                                                                 *
 * Date           Version        Reviser                      Comments        *
 * 13/05/2014     1.0            Jie Liang                    --------        *   
 * error: DerivativeImages\pos1 = z*width*height + y * width + x - 1;
   this is not right-center
 ******************************************************************************/

#include "mex.h"
#include "stdafx.h"
//#include "LBPRecognition.h"
#include "LDP.h"
#include <string.h>
#include <math.h>
#include <fstream>
#include <stdio.h>

//#ifdef _DEBUG
//#undef THIS_FILE
//static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
//#endif

/////////////////////////////////////////////////////////////////////////////
// CLDP construction/destruction

//extern CString g_strWorkPath;


CLDP::CLDP(int imageWidth, int imageHeight, int imageLength) : imageWidth(imageWidth), imageHeight(imageHeight), imageLength(imageLength)
{
	
	Data1 = new int[imageWidth * imageHeight];	// Right - Center
	Data2 = new int[imageWidth * imageHeight];	// Topright - Center
	Data3 = new int[imageWidth * imageHeight];	// Top - Center
	Data4 = new int[imageWidth * imageHeight];	// Topleft - Center
	TempData1 = new int[imageWidth * imageHeight];
	TempData2 = new int[imageWidth * imageHeight];
	TempData3 = new int[imageWidth * imageHeight];
	TempData4 = new int[imageWidth * imageHeight];

	Data45_0 = new int[imageWidth * imageHeight * imageLength];
	Data45_45 = new int[imageWidth * imageHeight * imageLength];
	Data45_90 = new int[imageWidth * imageHeight * imageLength];
	Data45_135 = new int[imageWidth * imageHeight * imageLength];

	Data90_0 = new int[imageWidth * imageHeight * imageLength];
	Data90_45 = new int[imageWidth * imageHeight * imageLength];
	Data90_90 = new int[imageWidth * imageHeight * imageLength];
	Data90_135 = new int[imageWidth * imageHeight * imageLength];

	Data135_0 = new int[imageWidth * imageHeight * imageLength];
	Data135_45 = new int[imageWidth * imageHeight * imageLength];
	Data135_90 = new int[imageWidth * imageHeight * imageLength];
	Data135_135 = new int[imageWidth * imageHeight * imageLength];
	

	Data0 = new int[imageWidth * imageHeight * imageLength];

	TempData = new int[imageWidth * imageHeight * imageLength];
	TempLdpData = new int[imageWidth * imageHeight * imageLength];	
	
	memset( Data1, 0, sizeof(int) * imageWidth * imageHeight );
	memset( Data2, 0, sizeof(int) * imageWidth * imageHeight );
	memset( Data3, 0, sizeof(int) * imageWidth * imageHeight );
	memset( Data4, 0, sizeof(int) * imageWidth * imageHeight );

	memset( TempData1, 0, sizeof(int) * imageWidth * imageHeight );
	memset( TempData2, 0, sizeof(int) * imageWidth * imageHeight );
	memset( TempData3, 0, sizeof(int) * imageWidth * imageHeight );
	memset( TempData4, 0, sizeof(int) * imageWidth * imageHeight );

	memset( Data45_0, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data45_45, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data45_90, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data45_135, 0, sizeof(int) * imageWidth * imageHeight * imageLength );

	memset( Data90_0, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data90_45, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data90_90, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data90_135, 0, sizeof(int) * imageWidth * imageHeight * imageLength );

	memset( Data135_0, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data135_45, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data135_90, 0, sizeof(int) * imageWidth * imageHeight * imageLength );
	memset( Data135_135, 0, sizeof(int) * imageWidth * imageHeight * imageLength );

	memset( Data0, 0, sizeof(int) * imageWidth * imageHeight * imageLength );


	memset( TempData, 0, sizeof(int) * imageWidth * imageHeight * imageLength);
	memset( TempLdpData, 0, sizeof(int) * imageWidth * imageHeight * imageLength);
}

CLDP::~CLDP()
{
	delete[] Data1;
	delete[] Data2;
	delete[] Data3;
	delete[] Data4;
	delete[] TempData1;
	delete[] TempData2;
	delete[] TempData3;
	delete[] TempData4;

	delete[]  Data45_0;
	delete[] Data45_45;
	delete[] Data45_90;
	delete[] Data45_135;

	delete[] Data90_0;	// Topleft - Center
	delete[] Data90_45;
	delete[] Data90_90;
	delete[] Data90_135;

	delete[] Data135_0;	// Topleft - Center
	delete[] Data135_45;
	delete[] Data135_90;
	delete[] Data135_135;

	delete[] Data0;
	delete[] TempData;
	delete[] TempLdpData;
}



/////////////////////////////////////////////////////////////////////////////
// CLDP commands

bool CLDP::LdpFeatureExtraction(const uint8_t* srcData, uint8_t* ldpData, const IntPoint sizeImg)
{
	int width = sizeImg.x;
	int height = sizeImg.y;

	// Lmp's 2nd-order LDP
	//
	int pos = 0;
	for( int y=0; y<height; y++ )
		for( int x=0; x<width; x++ )
		{
			TempData1[pos] = (int)srcData[pos];
			pos++;
		}
	DerivativeImages( TempData1, sizeImg );
	//for test
	


	//LmpOperator( Data1, ldpData, sizeImg );
	//LmpOperator( Data2, ldpData + (width * height), sizeImg );
	//LmpOperator( Data3, ldpData + (width * height * 2), sizeImg );
	//LmpOperator( Data4, ldpData + (width * height * 3), sizeImg );

	return true;
}
// this function is to output derivativeData for test.
bool CLDP::LdpFeatureExtraction(const uint8_t* srcData, int16_t* derivativeData, uint8_t* ldpData, const Int3DPoint sizeImg) // 3d ldp
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	// Lmp's 2nd-order LDP
	for(int z=0; z<length; z++)	
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				TempData[x+y*width+z*width*height] = (int)srcData[y+x*height+z*width*height];
			}
    
	DerivativeImages( TempData, sizeImg );
    int pos = 0;
	for(int z=0; z<length; z++)
		for( int x=0; x<width; x++ )
			for( int y=0; y<height; y++ )
			{
				derivativeData[y+x*height+z*width*height] = (int16_t)Data90_0[x+y*width+z*width*height];
				derivativeData[y+x*height+z*width*height + width*height*length] = (int16_t)Data90_90[x+y*width+z*width*height];
				derivativeData[y+x*height+z*width*height + 2*width*height*length] = (int16_t)Data0[x+y*width+z*width*height];
			}

	LmpOperator( Data90_0, ldpData, sizeImg );
	LmpOperator( Data90_90, ldpData + (width * height * length), sizeImg );
	LmpOperator( Data0, ldpData + (width * height * length * 2), sizeImg );

	return true;
}

bool CLDP::LdpFeatureExtraction(const uint8_t* srcData, uint8_t* ldpData, const Int3DPoint sizeImg) // 3d ldp
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	

	for(int z=0; z<length; z++)	
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				TempData[x+y*width+z*width*height] = (int)srcData[y+x*height+z*width*height];
			}

	DerivativeImages( TempData, sizeImg );

    LmpOperator( Data90_0, ldpData, sizeImg );
    LmpOperator( Data90_90, ldpData + (width * height * length), sizeImg );
    LmpOperator( Data0, ldpData + (width * height * length * 2), sizeImg );
   // LmpOperator( Data90_135, ldpData + (width * height * length * 3), sizeImg );


	return true;
}
long CLDP::LdpHistogramConstruction(const uint8_t* ldpData, HIST_BIN_TYPE* ldpHistData, const IntPoint sizeImg,
									const IntPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	long index = 0;




	index += LdpSubhistogramConstruction( ldpData, ldpHistData, sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height),
								ldpHistData + TOTAL_HIST_SIZE, sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height * 2),
								ldpHistData + (TOTAL_HIST_SIZE * 2), sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height * 3),
		ldpHistData + (TOTAL_HIST_SIZE * 3), sizeImg, sizeSubimg, numBin );
	return index;
}

long CLDP::LdpHistogramConstruction(const uint8_t* ldpData, HIST_BIN_TYPE* ldpHistData, const Int3DPoint sizeImg,
									const IntPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	long index = 0;



	index += LdpSubhistogramConstruction( ldpData, ldpHistData, sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height * length),
										  ldpHistData + TOTAL_HIST_SIZE, sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height * length* 2),
							              ldpHistData + (TOTAL_HIST_SIZE * 2), sizeImg, sizeSubimg, numBin );
	

	return index;
}
long CLDP::LdpHistogramConstruction(const uint8_t* ldpData, HIST_BIN_TYPE* ldpHistData, const Int3DPoint sizeImg,
									const Int3DPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	int sublength = sizeSubimg.z;
	long index = 0;



	index += LdpSubhistogramConstruction( ldpData, ldpHistData, sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height * length),
		ldpHistData + TOTAL_HIST_SIZEXYZ, sizeImg, sizeSubimg, numBin );
	index += LdpSubhistogramConstruction( ldpData + (width * height * length* 2),
		ldpHistData + (TOTAL_HIST_SIZEXYZ * 2), sizeImg, sizeSubimg, numBin );
	/*index += LdpSubhistogramConstruction( ldpData + (width * height * length* 3),
		ldpHistData + (TOTAL_HIST_SIZEXYZ * 3), sizeImg, sizeSubimg, numBin );*/
	//index += LdpSubhistogramConstruction( ldpData + (width * height * length* 4),
	//	ldpHistData + (TOTAL_HIST_SIZEXYZ * 4), sizeImg, sizeSubimg, numBin );
	//index += LdpSubhistogramConstruction( ldpData + (width * height * length* 5),
	//	ldpHistData + (TOTAL_HIST_SIZEXYZ * 5), sizeImg, sizeSubimg, numBin );
	return index;
}

long CLDP::LdpSubhistogramConstruction(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const IntPoint sizeImg,
									const IntPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	int binlength = 256 / numBin;	// Number of greylevel values in each quantized bin
	int subnumberx = width / subwidth;	// Number of subparts in width
	int subnumbery = height / subheight;	// Number of subparts in height
	HIST_BIN_TYPE histograms[HIST_BIN_NUM];	// Spatically enhanced histogram
	long index = 0;	// Byte size of the final spatially enhanced histogram

	for( int subparty = 0; subparty < subnumbery; subparty++ )	// Search subparts
	for( int subpartx = 0; subpartx < subnumberx; subpartx++ )
	{
		memset( histograms, 0, sizeof(int) * numBin );	// Clear the histograms

		for( int suby = 0; suby < subheight; suby++ )	// Search positions of each subpart
		for( int subx = 0; subx < subwidth; subx++ )
		{
			int y = subparty * subheight + suby;
			int x = subpartx * subwidth + subx;
			long pos = y * width + x;
			histograms[ lbpData[pos] / binlength ]++;	// Histogram quantization
		}

		for( int bin = 0; bin < numBin; bin++ )
			lbpHistData[ index++ ] = histograms[bin];	// Concatenate the histograms
	}

	return index;
}

long CLDP::LdpSubhistogramConstruction(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const Int3DPoint sizeImg,
									   const IntPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	int binlength = 256 / numBin;	// Number of greylevel values in each quantized bin
	int subnumberx = width / subwidth;	// Number of subparts in width
	int subnumbery = height / subheight;	// Number of subparts in height
	int histograms[HIST_BIN_NUM];	// Spatically enhanced histogram
	long index = 0;	// Byte size of the final spatially enhanced histogram

	for(int z=0; z<length; z++)	
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				TempLdpData[x+y*width+z*width*height] = (int)lbpData[y+x*height+z*width*height];
			}

	for( int subparty = 0; subparty < subnumbery; subparty++ )	// Search subparts
		for( int subpartx = 0; subpartx < subnumberx; subpartx++ )
		{
			memset( histograms, 0, sizeof(int) * numBin );	// Clear the histograms
			for( int z = 1; z < length-2; z++) // the coding first and last two bands are not valid 
			//for( int z = 15; z < 49; z++) // the coding first and last two bands are not valid 
				for( int suby = 0; suby < subheight; suby++ )	// Search positions of each subpart
					for( int subx = 0; subx < subwidth; subx++ )
					{
						int y = subparty * subheight + suby;
						int x = subpartx * subwidth + subx;
						long pos = z*width*height + y * width + x;
						histograms[ TempLdpData[pos] / binlength ]++;	// Histogram quantization
					}
					for( int bin = 0; bin < numBin; bin++ )
						lbpHistData[ index++ ] = histograms[bin];	// Concatenate the histograms
		}

		return index;
}
long CLDP::LdpSubhistogramConstruction(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const Int3DPoint sizeImg,
									   const Int3DPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	int sublength = sizeSubimg.z;
	int binlength = 256 / numBin;	// Number of greylevel values in each quantized bin
	int subnumberx = width / subwidth;	// Number of subparts in width
	int subnumbery = height / subheight;	// Number of subparts in height
	int subnumberz = length / sublength; //Number of subpartz in length
	int histograms[HIST_BIN_NUM];	// Spatically enhanced histogram
	long index = 0;	// Byte size of the final spatially enhanced histogram

	for(int z=0; z<length; z++)	
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				TempLdpData[x+y*width+z*width*height] = (int)lbpData[y+x*height+z*width*height];
			}
			for( int subpartz = 0; subpartz < subnumberz; subpartz++)
				for( int subparty = 0; subparty < subnumbery; subparty++ )	// Search subparts
					for( int subpartx = 0; subpartx < subnumberx; subpartx++ )
					{
						memset( histograms, 0, sizeof(int) * numBin );	// Clear the histograms
						for( int subz = 0; subz < sublength; subz++) // the coding first and last two bands are not valid 
							//for( int z = 15; z < 49; z++) // the coding first and last two bands are not valid 
							for( int suby = 0; suby < subheight; suby++ )	// Search positions of each subpart
								for( int subx = 0; subx < subwidth; subx++ )
								{
									int y = subparty * subheight + suby;
									int x = subpartx * subwidth + subx;
									//int z = 2+ subpartz * sublength + subz; // skip the first two bands
									int z = subpartz * sublength + subz; 
									long pos = z*width*height + y * width + x;
									histograms[ TempLdpData[pos] / binlength ]++;	// Histogram quantization
								}
								for( int bin = 0; bin < numBin; bin++ )
									lbpHistData[ index++ ] = histograms[bin];	// Concatenate the histograms
					}

				return index;
}

long CLDP::LdpSubhistogramConstructionWithOutEyes(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const Int3DPoint sizeImg,
								   const Int3DPoint sizeSubimg, const int numBin)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;
	int subwidth = sizeSubimg.x;
	int subheight = sizeSubimg.y;
	int sublength = sizeSubimg.z;
	int binlength = 256 / numBin;	// Number of greylevel values in each quantized bin
	int subnumberx = width / subwidth;	// Number of subparts in width
	int subnumbery = height / subheight;	// Number of subparts in height
	int subnumberz = length / sublength; //Number of subpartz in length
	int histograms[HIST_BIN_NUM];	// Spatically enhanced histogram
	long index = 0;	// Byte size of the final spatially enhanced histogram

	for(int z=0; z<length; z++)	
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				TempLdpData[x+y*width+z*width*height] = (int)lbpData[y+x*height+z*width*height];
			}
			for( int subpartz = 0; subpartz < subnumberz; subpartz++)
				for( int subparty = 0; subparty < subnumbery; subparty++ )	// Search subparts
					for( int subpartx = 0; subpartx < subnumberx; subpartx++ )
					{
						if(subpartx>0 && subpartx<3 && subparty>0 && subparty<3)//left eyes
							continue;
						if(subpartx>4 && subpartx<7 && subparty>0 && subparty<3)//right eyes
							continue;
						memset( histograms, 0, sizeof(int) * numBin );	// Clear the histograms
						for( int subz = 0; subz < sublength; subz++) // the coding first and last two bands are not valid 
							//for( int z = 15; z < 49; z++) // the coding first and last two bands are not valid 
								for( int suby = 0; suby < subheight; suby++ )	// Search positions of each subpart
									for( int subx = 0; subx < subwidth; subx++ )
									{
										int y = subparty * subheight + suby;
										int x = subpartx * subwidth + subx;
										int z = 2+ subpartz * sublength + subz; // skip the first two bands
										long pos = z*width*height + y * width + x;
										histograms[ TempLdpData[pos] / binlength ]++;	// Histogram quantization
									}
									for( int bin = 0; bin < numBin; bin++ )
										lbpHistData[ index++ ] = histograms[bin];	// Concatenate the histograms
					}

					return index;
}

void CLDP::DerivativeImages(const int* srcData, const IntPoint sizeImg)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int pos = 0;	// Current pixel position
	int pos1;		// Alternative pixel position

	for( int y=0; y<height; y++ )
	for( int x=0; x<width; x++ )
	{
		// Right - Center
		if( x == width - 1 )
			Data1[pos] = 1;
		else
		{
			pos1 = y * width + x - 1;
			Data1[pos] = srcData[pos1] - srcData[pos];
		}

		// Top - Center
		if( y == 0 )
			Data3[pos] = 1;
		else
		{
			pos1 = (y - 1) * width + x;
			Data3[pos] = srcData[pos1] - srcData[pos];
		}

		// Topleft - Center
		if( (y == 0) || (x == 0) )
			Data4[pos] = 0;
		else
		{
			pos1 = (y - 1) * width + x - 1;
			Data4[pos] = srcData[pos1] - srcData[pos];
		}

		// Topright - Center
		if( (y == 0) || (x == width - 1) )
			Data2[pos] = 0;
		else
		{
			pos1 = (y - 1) * width + x + 1;
			Data2[pos] = srcData[pos1] - srcData[pos];
		}

		pos++;	// Next position
	}
}
void CLDP::DerivativeImages(const int* srcData, const Int3DPoint sizeImg)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;

	int pos = 0;	// Current pixel position
	int pos1;		// Alternative pixel position
	for(int z = 0; z<length; z++)
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				

				// right inside

				//if( (x == width - 1) || (z == length - 1) )
				//	Data45_0[pos] = 1;
				//else
				//{
				//	pos1 = (z + 1)*width*height + y* width + x + 1;
				//	Data45_0[pos] = srcData[pos1] - srcData[pos];
				//}

				//if( (x == width - 1) || (y == 0) || (z == length - 1) )
				//	Data45_45[pos] = 1;
				//else
				//{
				//	pos1 = (z + 1)*width*height + (y - 1)* width + x + 1;
				//	Data45_45[pos] = srcData[pos1] - srcData[pos];
				//}

				//if( (y == 0) || (z == length - 1) )
				//	Data45_90[pos] = 1;
				//else
				//{
				//	pos1 = (z + 1)*width*height + (y - 1) * width + x;
				//	Data45_90[pos] = srcData[pos1] - srcData[pos];
				//}

				//if( (x == 0) || (y == 0) || (z == length - 1) )
				//	Data45_135[pos] = 1;
				//else
				//{
				//	pos1 = (z + 1)*width*height + (y - 1) * width + x - 1;
				//	Data45_135[pos] = srcData[pos1] - srcData[pos];
				//}

				if( x == width - 1 )
					Data90_0[pos] = 1;
				else
				{
					pos1 = z*width*height + y * width + x + 1;
					Data90_0[pos] = srcData[pos1] - srcData[pos];
				}
				////top right
				//if( (x == width - 1) || (y == 0) )
				//	Data90_45[pos] = 1;
				//else
				//{
				//	pos1 = z*width*height + (y - 1) * width + x + 1;
				//	Data90_45[pos] = srcData[pos1] - srcData[pos];
				//}
				//// /up - Center
				if( y == 0 )
					Data90_90[pos] = 1;
				else
				{
					pos1 = z*width*height + (y - 1) * width + x;
					Data90_90[pos] = srcData[pos1] - srcData[pos];
				}
				////top left
				//if( (x == 0) || (y == 0) )
				//	Data90_135[pos] = 1;
				//else
				//{
				//	pos1 = z*width*height + (y - 1) * width + x - 1;
				//	Data90_135[pos] = srcData[pos1] - srcData[pos];
				//}// X+/Right - Center


				/*if( (x == width - 1) || (z == 0) )
				Data135_0[pos] = 1;
				else
				{
				pos1 = (z - 1)*width*height + y* width + x + 1;
				Data135_0[pos] = srcData[pos1] - srcData[pos];
				}

				if( (x == width - 1) || (y == 0) || (z == 0) )
				Data135_45[pos] = 1;
				else
				{
				pos1 = (z - 1)*width*height + (y - 1)* width + x + 1;
				Data135_45[pos] = srcData[pos1] - srcData[pos];
				}

				if( (y == 0) || (z == 0) )
				Data135_90[pos] = 1;
				else*/
				/*{
				pos1 = (z - 1)*width*height + (y - 1) * width + x;
				Data135_90[pos] = srcData[pos1] - srcData[pos];
				}

				if( (x == 0) || (y == 0) || (z == 0) )
				Data135_135[pos] = 1;
				else
				{
				pos1 = (z - 1)*width*height + (y - 1) * width + x - 1;
				Data135_135[pos] = srcData[pos1] - srcData[pos];
				}*/


				// Z+/Inside - Center
				if( (z == length - 1) )
					Data0[pos] = 1;
				else
				{
					pos1 = (z + 1)*width*height + y* width + x;
					Data0[pos] = srcData[pos1] - srcData[pos];
				}


				pos++;	// Next position
			}
}
void CLDP::DerivativeImagesXY(const int* srcData, const Int3DPoint sizeImg)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;

	int pos = 0;	// Current pixel position
	int pos1;		// Alternative pixel position
	for(int z = 0; z<length; z++)
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				
				if( x == width - 1 )
					Data90_0[pos] = 1;
				else
				{
					pos1 = z*width*height + y * width + x + 1;
					Data90_0[pos] = srcData[pos1] - srcData[pos];
				}
				//top right
				if( (x == width - 1) || (y == 0) )
					Data90_45[pos] = 1;
				else
				{
					pos1 = z*width*height + (y - 1) * width + x + 1;
					Data90_45[pos] = srcData[pos1] - srcData[pos];
				}
				//// /up - Center
				if( y == 0 )
					Data90_90[pos] = 1;
				else
				{
					pos1 = z*width*height + (y - 1) * width + x;
					Data90_90[pos] = srcData[pos1] - srcData[pos];
				}
				//top left
				if( (x == 0) || (y == 0) )
					Data90_135[pos] = 1;
				else
				{
					pos1 = z*width*height + (y - 1) * width + x - 1;
					Data90_135[pos] = srcData[pos1] - srcData[pos];
				}
				
				

				pos++;	// Next position
			}
}
void CLDP::DerivativeImagesWithAverageZ(const int* srcData, const Int3DPoint sizeImg)
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;

	int pos = 0;	// Current pixel position
	int pos1;		// Alternative pixel position
	int p1,p2,p3,p4,p5,p6,p7,p8,p9;
	int averg, averg1;
	for(int z = 0; z<length; z++)
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				// X+/Right - Center
				if( x == width - 1 )
					Data90_0[pos] = 1;
				else
				{
					pos1 = z*width*height + y * width + x + 1;
					Data90_0[pos] = srcData[pos1] - srcData[pos];
				}

				// Y+/Down - Center
				if( y == height - 1 )
					Data90_90[pos] = 1;
				else
				{
					pos1 = z*width*height + (y + 1) * width + x;
					Data90_90[pos] = srcData[pos1] - srcData[pos];
				}

				// Z+/Inside - Center
				if( (z == length - 1) || x == 0 || x == width - 1 || y == 0 || y == height - 1)
					Data0[pos] = 1;
				else
				{
					p1 = pos - width - 1;
					p2 = pos - width;
					p3 = pos - width + 1;
					p4 = pos + 1;
					p5 = pos + width + 1;
					p6 = pos + width;
					p7 = pos + width - 1;
					p8 = pos - 1;
					averg = srcData[p1] + srcData[p2] +srcData[p3] +srcData[p4] +srcData[p5] +srcData[p6] +srcData[p7] +srcData[p8] +srcData[pos];
					averg = averg/9;

					pos1 = (z + 1)*width*height + y* width + x;
					p1 = pos1 - width - 1;
					p2 = pos1 - width;
					p3 = pos1 - width + 1;
					p4 = pos1 + 1;
					p5 = pos1 + width + 1;
					p6 = pos1 + width;
					p7 = pos1 + width - 1;
					p8 = pos1 - 1;
					averg1 = srcData[p1] + srcData[p2] +srcData[p3] +srcData[p4] +srcData[p5] +srcData[p6] +srcData[p7] +srcData[p8] +srcData[pos1];
					averg1 = averg1/9;
					Data0[pos] = averg1 - averg;
				}

				pos++;	// Next position
			}
}
bool CLDP::LmpOperator(const int* img, uint8_t* lbpData, const IntPoint sizeImg) //f function
{
	int w,h;
	w = sizeImg.x;
	h = sizeImg.y;

	double *pInterData;
	pInterData = new double[w*h];
	double minInterData,maxInterData;
	minInterData = 1000;
	maxInterData =-1000;

	uint8_t *PLbpData;
	const int *PTempImgData;

	PLbpData = lbpData;
	PTempImgData = img;

	int i,j;
	int pixelPos;
	int tempPixelPos;

	int iTemp,jTemp;
	int totalGray;
	int tempGray;
	int tempCenterGray;

	int pixelPosY;
	pixelPosY = 0;

	int tempPixelPosY;

	for(j=0;j<h;j++)
	{
		for(i=0;i<w;i++)
		{
			//pixelPos = j*w+i;
			pixelPos = pixelPosY+i;

			if(i==0||i==w-1||j==0||j==h-1)
			{
				PLbpData[pixelPos] =   PTempImgData[pixelPos];
				pInterData[pixelPos] = PTempImgData[pixelPos]*2;
				continue;
			}

			tempCenterGray = PTempImgData[pixelPos];
			totalGray = 0;

			tempPixelPosY = (j-1)*w;
			for(jTemp=j-1;jTemp<=j+1;jTemp++)
			{
				for(iTemp=i-1;iTemp<=i+1;iTemp++)
				{
					//tempPixelPos = jTemp*w+iTemp;
					tempPixelPos = tempPixelPosY+iTemp;

					tempGray = PTempImgData[tempPixelPos];

					if(iTemp==i-1&&jTemp==j-1)//g1
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 1;
					}

					if(iTemp==i&&jTemp==j-1)//g2
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 2;
					}

					if(iTemp==i+1&&jTemp==j-1)//g3
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 4;
					}

					if(iTemp==i-1&&jTemp==j)//g4
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 8;
					}

					if(iTemp==i+1&&jTemp==j)//g5
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 16;
					}

					if(iTemp==i-1&&jTemp==j+1)//g6
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 32;
					}

					if(iTemp==i&&jTemp==j+1)//g7
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 64;
					}

					if(iTemp==i+1&&jTemp==j+1)//g8
					{
						if(tempGray * tempCenterGray <= 0)
							totalGray += 128;
					}
				}

				tempPixelPosY += w;
			}

			PLbpData[pixelPos] = uint8_t(totalGray);
			//PLbpData[pixelPos] = BYTE((totalGray+tempCenterGray)*0.5);

			pInterData[pixelPos] = totalGray+tempCenterGray;

			if(pInterData[pixelPos]<minInterData)
				minInterData = pInterData[pixelPos];

			if(pInterData[pixelPos]>maxInterData)
				maxInterData = pInterData[pixelPos];
		}

		pixelPosY+=w;
	}


	double coef;
	coef = 255.0/(maxInterData-minInterData);

//	for(i=0;i<w*h;i++)
//	{
//		PLbpData[i] = BYTE(coef*(pInterData[i]-minInterData));
//	}

	delete pInterData;
	return true;
}
bool CLDP::LmpOperator(const int* img, uint8_t* codeData, const Int3DPoint sizeImg) //f function
{
	int width = sizeImg.x;
	int height = sizeImg.y;
	int length = sizeImg.z;

	double *pInterData;
	pInterData = new double[width*height*length];
	double minInterData,maxInterData;
	minInterData = 1000;
	maxInterData =-1000;

	uint8_t *PcodeData; //code data
	const int *PTempImgData; // derivative data

	PcodeData = codeData; //output, code data
	PTempImgData = img; //derivative data

	int pixelPos;
	int tempPixelPos;

	int xTheta,yTheta,zTheta;
	int totalGray;
	int tempGray;
	int tempCenterGray;


	for(int z=0; z<length; z++)	
		for( int y=0; y<height; y++ )
			for( int x=0; x<width; x++ )
			{
				pixelPos = x + width*y+ z*width*height;
				if(x==0||x==width-1||y==0||y==height-1|| z==0 ||z==length-1)
				{
					PcodeData[y+x*height+z*width*height] =   PTempImgData[pixelPos];
					pInterData[pixelPos] = PTempImgData[pixelPos]*2;
					continue;
				}

				tempCenterGray = PTempImgData[pixelPos];
				totalGray = 0;
				for(zTheta=z-1;zTheta<=z+1;zTheta++)//3 by 3 by 3 cube
				{
					for(yTheta=y-1;yTheta<=y+1;yTheta++)
					{
						for(xTheta=x-1;xTheta<=x+1;xTheta++)
						{
							tempPixelPos = xTheta+yTheta*width+zTheta*width*height;
							tempGray = PTempImgData[tempPixelPos];
							if(xTheta==x-1&&yTheta==y-1&&zTheta==z-1)//g1 (1, 1, 1)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 1;
							}

							if(xTheta==x+1&&yTheta==y-1&&zTheta==z-1)//g2 (3, 1, 1) 
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 2;
							}

							if(xTheta==x+1&&yTheta==y+1&&zTheta==z-1)//g3 (3, 3, 1)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 4;
							}

							if(xTheta==x-1&&yTheta==y+1&&zTheta==z-1)//g4 (1, 3, 1)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 8;
							}

							if(xTheta==x-1&&yTheta==y-1&&zTheta==z+1)//g5 (1, 1, 3)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 16;
							}

							if(xTheta==x+1&&yTheta==y-1&&zTheta==z+1)//g6 (3, 1, 3)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 32;
							}

							if(xTheta==x-1&&yTheta==y+1&&zTheta==z+1)//g7 (1, 3, 3)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 64;
							}

							if(xTheta==x+1&&yTheta==y+1&&zTheta==z+1)//g8 (3, 3, 3)
							{
								if(tempGray * tempCenterGray <= 0)
									totalGray += 128;
							}

							//if(xTheta==x-1&&yTheta==y&&zTheta==z)//g1 (1, 2, 2)
							//{
							//	if(tempGray * tempCenterGray <= 0)
							//		totalGray += 1;
							//}

							//if(xTheta==x+1&&yTheta==y&&zTheta==z)//g2 (3, 2, 2) 
							//{
							//	if(tempGray * tempCenterGray <= 0)
							//		totalGray += 2;
							//}

							//if(xTheta==x&&yTheta==y-1&&zTheta==z)//g3 (2, 1, 2)
							//{
							//	if(tempGray * tempCenterGray <= 0)
							//		totalGray += 4;
							//}

							//if(xTheta==x&&yTheta==y+1&&zTheta==z)//g4 (2, 3, 2)
							//{
							//	if(tempGray * tempCenterGray <= 0)
							//		totalGray += 8;
							//}

							//if(xTheta==x&&yTheta==y&&zTheta==z-1)//g5 (2, 2, 1)
							//{
							//	if(tempGray * tempCenterGray <= 0)
							//		totalGray += 16;
							//}

							//if(xTheta==x&&yTheta==y&&zTheta==z+1)//g6 (2, 2, 3)
							//{
							//	if(tempGray * tempCenterGray <= 0)
							//		totalGray += 32;
							//}


						}
					}
				}
			PcodeData[y+x*height+z*width*height] = uint8_t(totalGray); // assign the Matlab data following the rows
			pInterData[pixelPos] = totalGray+tempCenterGray;// I don't understand pInterData
			if(pInterData[pixelPos]<minInterData)
				minInterData = pInterData[pixelPos];

			if(pInterData[pixelPos]>maxInterData)
				maxInterData = pInterData[pixelPos];
		}
	double coef;
	coef = 255.0/(maxInterData-minInterData);
	delete pInterData;
	return true;
}
