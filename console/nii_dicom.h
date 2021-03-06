#include <stdbool.h>
#include <string.h>
#include "nifti1.h"

#ifndef MRIpro_nii_dcm_h

#define MRIpro_nii_dcm_h

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef myEnableJasper
    #define kDCMvers "12Dec2015j" //JASPER for JPEG2000
#else
	#ifdef myDisableOpenJPEG
    #define kDCMvers "12Dec2015" //no decompressor
	#else
    #define kDCMvers "12Dec2015o" //OPENJPEG for JPEG2000
    #endif
#endif

static const int kMaxDTI4D = 4000; //#define kMaxDTIv  4000
#define kDICOMStr  31
#define kMANUFACTURER_UNKNOWN  0
#define kMANUFACTURER_SIEMENS  1
#define kMANUFACTURER_GE  2
#define kMANUFACTURER_PHILIPS  3
#define kMANUFACTURER_TOSHIBA  4
static const int kSliceOrientUnknown = 0;
static const int kSliceOrientTra = 1;
static const int kSliceOrientSag = 2;
static const int kSliceOrientCor = 3;
static const int kSliceOrientMosaicNegativeDeterminant = 4;
static const int kCompressNone = 0;
static const int kCompressYes = 1;
static const int kCompressC3 = 2; //obsolete JPEG lossless
static const int kCompress50 = 3; //obsolete JPEG lossy
    struct TDTI {
        float V[4];
        float sliceTiming;
    };
    struct TDTI4D {
        struct TDTI S[kMaxDTI4D];
    };
    
    struct TCSAdata {
        float dtiV[4], sliceNormV[4], bandwidthPerPixelPhaseEncode, sliceMeasurementDuration;
        int numDti, multiBandFactor, sliceOrder, slice_start, slice_end, mosaicSlices,protocolSliceNumber1,phaseEncodingDirectionPositive;
    };
    struct TDICOMdata {
        //struct TDTI * dti4D; //only for 4D diffusion volumes - otherwise use more compact CSA.dtiV
        long seriesNum;
        int xyzDim[5];//, xyzOri[4];
        int coilNum, echoNum,sliceOrient,numberOfDynamicScans, manufacturer, converted2NII, acquNum, imageNum, imageStart, imageBytes, bitsStored, bitsAllocated, samplesPerPixel,patientPositionSequentialRepeats,locationsInAcquisition, compressionScheme; //
        float TE, TR,intenScale,intenIntercept, gantryTilt, lastScanLoc, angulation[4];
        float orient[7], patientPosition[4], patientPositionLast[4], xyzMM[4], stackOffcentre[4]; //patientPosition2nd[4],
        double dateTime, acquisitionTime;
        bool isValid, is3DAcq, isExplicitVR, isLittleEndian, isPlanarRGB, isSigned, isHasPhase,isHasMagnitude,isHasMixed, isFloat, isResampled;
        char phaseEncodingRC;
        char  patientID[kDICOMStr], patientOrient[kDICOMStr], patientName[kDICOMStr],protocolName[kDICOMStr],scanningSequence[kDICOMStr], studyDate[kDICOMStr],studyTime[kDICOMStr], imageComments[kDICOMStr];
        struct TCSAdata CSA;
    };
    
    size_t nii_ImgBytes(struct nifti_1_header hdr);
    struct TDICOMdata readDICOMv(char * fname, bool isVerbose, int compressFlag, struct TDTI4D *dti4D);
    //struct TDICOMdata readDICOMv(char * fname, bool isVerbose, int compressFlag); //if compressFlag = 0, compressed DICOM will be reported as invalid
    struct TDICOMdata readDICOM(char * fname);
    struct TDICOMdata clear_dicom_data();
    unsigned char * nii_flipY(unsigned char* bImg, struct nifti_1_header *h);
    unsigned char * nii_flipZ(unsigned char* bImg, struct nifti_1_header *h);
    void changeExt (char *file_name, const char* ext);
    struct TDICOMdata  nii_readParRec (char * parname, bool isVerbose, struct TDTI4D *dti4D);
    unsigned char * nii_planar2rgb(unsigned char* bImg, struct nifti_1_header *hdr, int isPlanar);
    
    int headerDcm2Nii2(struct TDICOMdata d, struct TDICOMdata d2, struct nifti_1_header *h);
    //unsigned char * nii_loadImgX(char* imgname, struct nifti_1_header *hdr, struct TDICOMdata dcm, bool iVaries);
    unsigned char * nii_loadImgXL(char* imgname, struct nifti_1_header *hdr, struct TDICOMdata dcm, bool iVaries, int compressFlag);
    //int foo (float vx);
#ifdef  __cplusplus
}
#endif

#endif
