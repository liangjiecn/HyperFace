/******************************************************************************
 * Filename:      LDP.h                                                       *
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
 ******************************************************************************/
#ifndef AFX_LDP_H
#define AFX_LDP_H

#include <stdint.h>
#include "StdAfx.h"


typedef struct IntPoint
{
	int x;
	int y;
}IntPoint;

typedef struct Int3DPoint
{
	int x;
	int y;
	int z;
}Int3DPoint;

typedef struct Double3DPoint
{
	double x;
	double y;
	double z;

}Double3DPoint;


class CLDP
{
// Construction/Destruction
private:
	int imageWidth;
	int imageHeight;
	int imageLength;

	int subImageWidth;      // block size
	int subImageHeight;
	int subImageLength;

public:
	CLDP(int imageWidth, int imageHeight, int imageLength);
	 ~CLDP();

// Operations
public:
	// Extract LDP feature from a face image srcData and save it to ldpData
	bool LdpFeatureExtraction(const uint8_t* srcData, uint8_t* ldpData, const IntPoint sizeImg); 
	//
	bool LdpFeatureExtraction(const uint8_t* srcData, uint8_t* ldpData, const Int3DPoint sizeImg); // 3d ldp
	// Extract 3DLDP feature from a hyperspectral face image srcData and save it to ldpData
	bool LdpFeatureExtraction(const uint8_t* srcData, int16_t* derivativeData, uint8_t* ldpData, const Int3DPoint sizeImg);
	// Construct LDP spatially enhanced histogram from ldpData and save it to ldpHistData.
	// The byte size of the ldpHistData is returned. NOTE: When the subpart's size is over
	// 16x16=256, the uint8_t type of ldpHistData has to be increased into int type
	long LdpHistogramConstruction(const uint8_t* ldpData, HIST_BIN_TYPE* ldpHistData, const IntPoint sizeImg,
								const IntPoint sizeSubimg, const int numBin);


	long LdpHistogramConstruction(const uint8_t* ldpData, HIST_BIN_TYPE* ldpHistData, const Int3DPoint sizeImg,
								const IntPoint sizeSubimg, const int numBin);
	//separate regions in Z direction 
	long LdpHistogramConstruction(const uint8_t* ldpData, HIST_BIN_TYPE* ldpHistData, const Int3DPoint sizeImg,
								const Int3DPoint sizeSubimg, const int numBin);

	long LdpSubhistogramConstruction(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const IntPoint sizeImg,
								const IntPoint sizeSubimg, const int numBin);
	// I have not 
	long LdpSubhistogramConstruction(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const Int3DPoint sizeImg,
								const IntPoint sizeSubimg, const int numBin);
	long LdpSubhistogramConstruction(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const Int3DPoint sizeImg,
								const Int3DPoint sizeSubimg, const int numBin);
	long LdpSubhistogramConstructionWithOutEyes(const uint8_t* lbpData, HIST_BIN_TYPE* lbpHistData, const Int3DPoint sizeImg,
		const Int3DPoint sizeSubimg, const int numBin);
	// Extract derivative images (0, 45, 90, 135)
	void DerivativeImages(const int* srcData, const IntPoint sizeImg);
	// Extract derivative images (x+, y+, z+)
	void DerivativeImages(const int* srcData, const Int3DPoint sizeImg);
	// Local Multiplication Pattern operator (8 neighbors)
    void DerivativeImagesXY(const int* srcData, const Int3DPoint sizeImg);
    // Local Multiplication Pattern operator (in XY plain)
	void DerivativeImagesWithAverageZ(const int* srcData, const Int3DPoint sizeImg);
	bool LmpOperator(const int* img, uint8_t* lbpData, const IntPoint sizeImg);
	// Local Multiplication Pattern operator (8 corners in 3*3*3 cube)
	bool LmpOperator(const int* img, uint8_t* lbpData, const Int3DPoint sizeImg);

// Attributes
private:
	int *Data1;	// Right - Center
	int *Data2;	// Topright - Center
	int *Data3; // Top - Center
	int *Data4;	// Topleft - Center
	int *TempData1;
	int *TempData2;
	int *TempData3;
	int *TempData4;

	int *Data45_0;
	int *Data45_45;
	int *Data45_90;
	int *Data45_135;

	int *Data90_0;	// Topleft - Center
	int *Data90_45;
    int *Data90_90;
	int *Data90_135;
	
	int *Data135_0;	// Topleft - Center
	int *Data135_45;
	int *Data135_90;
	int *Data135_135;

	int *Data0;


	int *TempData;
	int *TempLdpData;
};

#endif
