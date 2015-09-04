#ifndef __StdAfx_h
#define __StdAfx_h


#define LBP_P				8
#define LBP_R				1

#define ROUNDING_ERROR		0.000001
#define PI					3.141592653589793

//#define IMG_SIZE_X			256
//#define IMG_SIZE_Y			256
//#define SUBIMG_SIZE_X		16	// Size x of subimages, <= 16 for uint8_t
//#define SUBIMG_SIZE_Y		16	// Size y of subimages, <= 16 for uint8_t
#define HIST_BIN_TYPE		float
#define	HIST_BIN_NUM		16	// Number of total quantized histogram bins
#define	TOTAL_HIST_SIZE		((imageWidth / subwidth) * (imageHeight / subheight) * HIST_BIN_NUM)
#define	TOTAL_HIST_SIZEXYZ  ((imageWidth / subwidth) * (imageHeight / subwidth) * (imageLength / sublength) * HIST_BIN_NUM)
//#define MAX_FILE_NUMBER		120	// 120 for AR, 1196 for FERET, 1680/3360 for LFW

//#define DATABASE_IDENTITY_AR	// For CMS calculation on AR, FERET, LFW databases
//#define FILENAME_IDENTITY	2	// The first 5/9 characters identifying a person in AR/FERET



#endif // __StdAfx_h
