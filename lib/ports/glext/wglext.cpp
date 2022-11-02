#ifdef flagWIN32

#include "maindef.h"
#include <gl/GL.h>
#include "wglext.h"




/* july 22 2013 */

WGLPROC_RETURN1(BOOL,wglGetPixelFormatAttribivARB,
			(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, 
			const int *piAttributes, int *piValues),
			(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues))
WGLPROC_RETURN1(BOOL, wglGetPixelFormatAttribfvARB,
(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, 
const int *piAttributes, FLOAT *pfValues),
(hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues))
WGLPROC_RETURN1(BOOL, wglChoosePixelFormatARB,
(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList,
UINT nMaxFormats, int *piFormats, UINT *nNumFormats),
(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats))
WGLPROC_RETURN1(HGLRC, wglCreateContextAttribsARB,
(HDC hDC, HGLRC hShareContext, const int *attribList),
(hDC, hShareContext, attribList))
WGLPROC_RETURN1(const char *, wglGetExtensionsStringARB, (HDC hdc), (hdc))

WGLPROC_RETURN1(BOOL, wglMakeContextCurrentARB ,
(HDC hDrawDC, HDC hReadDC, HGLRC hglrc),
(hDrawDC, hReadDC, hglrc))
WGLPROC_RETURN1(HDC, wglGetCurrentReadDCARB, (void), ())


/* july 28 2013 */

WGLPROC_RETURN1(HANDLE,wglCreateBufferRegionARB ,
(HDC hDC, int iLayerPlane, UINT uType), (hDC, iLayerPlane, uType))
WGLPROC_VOID(wglDeleteBufferRegionARB, (HANDLE hRegion), (hRegion))
WGLPROC_RETURN1(BOOL,wglSaveBufferRegionARB ,
(HANDLE hRegion, int x, int y, int width, int height), (hRegion, x,y,width, height))
WGLPROC_RETURN1(BOOL, wglRestoreBufferRegionARB,
(HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc),
(hRegion, x,y,width, height,xSrc, ySrc))



WGLPROC_RETURN1(HPBUFFERARB,
wglCreatePbufferARB,
(HDC hDC, int iPixelFormat, int iWidth, int iHeight,
const int *piAttribList),
(hDC, iPixelFormat, iWidth, iHeight, piAttribList))
WGLPROC_RETURN1(HDC, wglGetPbufferDCARB ,(HPBUFFERARB hPbuffer), (hPbuffer))
WGLPROC_RETURN1(int, wglReleasePbufferDCARB ,
(HPBUFFERARB hPbuffer, HDC hDC),(hPbuffer, hDC))
WGLPROC_RETURN1(BOOL, wglDestroyPbufferARB ,
(HPBUFFERARB hPbuffer),(hPbuffer))
WGLPROC_RETURN1(BOOL, wglQueryPbufferARB,
(HPBUFFERARB hPbuffer, int iAttribute, int *piValue),
(hPbuffer,iAttribute, piValue))


WGLPROC_RETURN1(BOOL, wglBindTexImageARB,
(HPBUFFERARB hPbuffer, int iBuffer), (hPbuffer, iBuffer))
WGLPROC_RETURN1(BOOL, wglReleaseTexImageARB,
(HPBUFFERARB hPbuffer, int iBuffer), (hPbuffer, iBuffer))
WGLPROC_RETURN1(BOOL, wglSetPbufferAttribARB ,
(HPBUFFERARB hPbuffer, const int *piAttribList),
(hPbuffer,piAttribList))



WGLPROC_RETURN1(BOOL, wglSetStereoEmitterState3DL,
(HDC hDC, UINT uState), (hDC, uState))

WGLPROC_RETURN1(UINT,wglGetGPUIDsAMD ,(UINT maxCount, UINT *ids),
(maxCount, ids))
WGLPROC_RETURN1(INT,wglGetGPUInfoAMD,
(UINT id, int property, GLenum dataType, UINT size, void *data),
(id, property, dataType,size,data))
WGLPROC_RETURN1(UINT, wglGetContextGPUIDAMD, (HGLRC hglrc), (hglrc))
WGLPROC_RETURN1(HGLRC, wglCreateAssociatedContextAMD, (UINT id), (id))
WGLPROC_RETURN1(HGLRC , wglCreateAssociatedContextAttribsAMD,
(UINT id, HGLRC hShareContext, const int *attribList), (id, hShareContext,attribList))
WGLPROC_RETURN1(BOOL, wglDeleteAssociatedContextAMD, (HGLRC hglrc),
(hglrc))
WGLPROC_RETURN1(BOOL, wglMakeAssociatedContextCurrentAMD, (HGLRC hglrc),
(hglrc))
WGLPROC_RETURN1(HGLRC, wglGetCurrentAssociatedContextAMD, (void), ())

/* july 29 2013  3:03 pm */

WGLPROC_VOID(wglBlitContextFramebufferAMD,
(HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1,
GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, 
GLint dstY1, GLbitfield mask, GLenum filter),
(dstCtx, srcX0,srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1,mask, filter))



WGLPROC_RETURN1(GLboolean,wglCreateDisplayColorTableEXT, (GLushort id), (id))
WGLPROC_RETURN1(GLboolean,wglLoadDisplayColorTableEXT,
(const GLushort *table, GLuint length), (table,length))
WGLPROC_RETURN1(GLboolean, wglBindDisplayColorTableEXT, (GLushort id), (id))
WGLPROC_VOID( wglDestroyDisplayColorTableEXT, (GLushort id),(id))


WGLPROC_RETURN1(BOOL, wglMakeContextCurrentEXT,
(HDC hDrawDC, HDC hReadDC, HGLRC hglrc), (hDrawDC, hReadDC, hglrc))
WGLPROC_RETURN1(HDC, wglGetCurrentReadDCEXT, (void),())


WGLPROC_RETURN1(HPBUFFEREXT, wglCreatePbufferEXT,
(HDC hDC, int iPixelFormat, int iWidth, int iHeight,
const int *piAttribList),
(hDC, iPixelFormat, iWidth, iHeight, piAttribList))
WGLPROC_RETURN1(HDC, wglGetPbufferDCEXT, (HPBUFFEREXT hPbuffer),
(hPbuffer))
WGLPROC_RETURN1(int, wglReleasePbufferDCEXT,
(HPBUFFEREXT hPbuffer, HDC hDC), (hPbuffer,hDC))
WGLPROC_RETURN1(BOOL, wglDestroyPbufferEXT, (HPBUFFEREXT hPbuffer),
(hPbuffer))
WGLPROC_RETURN1(BOOL, wglQueryPbufferEXT,
(HPBUFFEREXT hPbuffer, int iAttribute, int *piValue),
(hPbuffer,iAttribute,piValue))


WGLPROC_RETURN1(BOOL, wglGetPixelFormatAttribivEXT,
(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes,
int *piAttributes, int *piValues),
(hdc, iPixelFormat, iLayerPlane,nAttributes, piAttributes, piValues))
WGLPROC_RETURN1(BOOL, wglGetPixelFormatAttribfvEXT,
(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes,
int *piAttributes, FLOAT *pfValues),
(hdc, iPixelFormat,iLayerPlane, nAttributes, piAttributes, pfValues))
WGLPROC_RETURN1(BOOL, wglChoosePixelFormatEXT,
(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList,
UINT nMaxFormats, int *piFormats, UINT *nNumFormats),
(hdc, piAttribIList, pfAttribFList,nMaxFormats,piFormats,nNumFormats)) 




WGLPROC_RETURN1(BOOL, wglSwapIntervalEXT, (int interval), (interval))
WGLPROC_RETURN1(int, wglGetSwapIntervalEXT, (void), ())


WGLPROC_RETURN1(BOOL, wglGetDigitalVideoParametersI3D,
(HDC hDC, int iAttribute, int *piValue),
(hDC, iAttribute, piValue))
WGLPROC_RETURN1(BOOL, wglSetDigitalVideoParametersI3D ,
(HDC hDC, int iAttribute, const int *piValue),
(hDC,iAttribute,piValue))

WGLPROC_RETURN1(BOOL, wglGetGammaTableParametersI3D,
(HDC hDC, int iAttribute, int *piValue),
(hDC,iAttribute,piValue))
WGLPROC_RETURN1(BOOL,wglSetGammaTableParametersI3D,
(HDC hDC, int iAttribute, const int *piValue),
(hDC,iAttribute,piValue))
WGLPROC_RETURN1(BOOL, wglGetGammaTableI3D,
(HDC hDC, int iEntries, USHORT *puRed, USHORT *puGreen, USHORT *puBlue),
(hDC,iEntries,puRed,puGreen,puBlue))
WGLPROC_RETURN1(BOOL, wglSetGammaTableI3D,
(HDC hDC, int iEntries, const USHORT *puRed, const USHORT *puGreen,
const USHORT *puBlue),
(hDC,iEntries, puRed, puGreen, puBlue))


WGLPROC_RETURN1(BOOL, wglEnableGenlockI3D, (HDC hDC), (hDC))
WGLPROC_RETURN1(BOOL, wglDisableGenlockI3D, (HDC hDC), (hDC))
WGLPROC_RETURN1(BOOL, wglIsEnabledGenlockI3D, (HDC hDC, BOOL *pFlag), (hDC, pFlag))
WGLPROC_RETURN1(BOOL, wglGenlockSourceI3D, (HDC hDC, UINT uSource), (hDC, uSource))
WGLPROC_RETURN1(BOOL, wglGetGenlockSourceI3D, (HDC hDC, UINT *uSource), (hDC, uSource))
WGLPROC_RETURN1(BOOL, wglGenlockSourceEdgeI3D, (HDC hDC, UINT uEdge), (hDC, uEdge))
WGLPROC_RETURN1(BOOL, wglGetGenlockSourceEdgeI3D, (HDC hDC, UINT *uEdge), (hDC, uEdge))
WGLPROC_RETURN1(BOOL, wglGenlockSampleRateI3D, (HDC hDC, UINT uRate), (hDC, uRate))
WGLPROC_RETURN1(BOOL, wglGetGenlockSampleRateI3D, (HDC hDC, UINT *uRate), (hDC, uRate))
WGLPROC_RETURN1(BOOL, wglGenlockSourceDelayI3D, (HDC hDC, UINT uDelay), (hDC, uDelay))
WGLPROC_RETURN1(BOOL, wglGetGenlockSourceDelayI3D, (HDC hDC, UINT *uDelay), (hDC, uDelay))
WGLPROC_RETURN1(BOOL, wglQueryGenlockMaxSourceDelayI3D, (HDC hDC, UINT *uMaxLineDelay, UINT *uMaxPixelDelay), (hDC, uMaxLineDelay, uMaxPixelDelay))


WGLPROC_RETURN1(LPVOID, wglCreateImageBufferI3D,
(HDC hDC, DWORD dwSize, UINT uFlags), (hDC, dwSize, uFlags))
WGLPROC_RETURN1(BOOL, wglDestroyImageBufferI3D,
(HDC hDC, LPVOID pAddress), (hDC, pAddress))
WGLPROC_RETURN1(BOOL, wglAssociateImageBufferEventsI3D,
(HDC hDC, const HANDLE *pEvent, const LPVOID *pAddress,
const DWORD *pSize, UINT count),
(hDC,pEvent,pAddress, pSize, count))
WGLPROC_RETURN1(BOOL,wglReleaseImageBufferEventsI3D,
(HDC hDC, const LPVOID *pAddress, UINT count),
(hDC,pAddress,count))



WGLPROC_RETURN1(BOOL, wglEnableFrameLockI3D, (void), ())
WGLPROC_RETURN1(BOOL, wglDisableFrameLockI3D, (void),())
WGLPROC_RETURN1(BOOL, wglIsEnabledFrameLockI3D, (BOOL *pFlag), (pFlag))
WGLPROC_RETURN1(BOOL, wglQueryFrameLockMasterI3D, (BOOL *pFlag), (pFlag))


WGLPROC_RETURN1(BOOL, wglGetFrameUsageI3D, (float *pUsage), (pUsage))
WGLPROC_RETURN1(BOOL, wglBeginFrameTrackingI3D, (void),())
WGLPROC_RETURN1(BOOL, wglEndFrameTrackingI3D, (void),())
WGLPROC_RETURN1(BOOL, wglQueryFrameTrackingI3D, 
(DWORD *pFrameCount, DWORD *pMissedFrames, float *pLastMissedUsage),
(pFrameCount, pMissedFrames, pLastMissedUsage))


WGLPROC_RETURN1(BOOL, wglDXSetResourceShareHandleNV,
(void *dxObject, HANDLE shareHandle), (dxObject,shareHandle))
WGLPROC_RETURN1(HANDLE, wglDXOpenDeviceNV, (void *dxDevice),
(dxDevice))
WGLPROC_RETURN1(BOOL, wglDXCloseDeviceNV, (HANDLE hDevice), (hDevice))
WGLPROC_RETURN1(HANDLE, wglDXRegisterObjectNV,
(HANDLE hDevice, void *dxObject, GLuint name, GLenum type, GLenum access),
(hDevice,dxObject, name, type, access))
WGLPROC_RETURN1(BOOL, wglDXUnregisterObjectNV ,
(HANDLE hDevice, HANDLE hObject), (hDevice, hObject))
WGLPROC_RETURN1(BOOL, wglDXObjectAccessNV ,
(HANDLE hObject, GLenum access),
(hObject,access))
WGLPROC_RETURN1(BOOL, wglDXLockObjectsNV,
(HANDLE hDevice, GLint count, HANDLE *hObjects),
(hDevice,count,hObjects))
WGLPROC_RETURN1(BOOL, wglDXUnlockObjectsNV,
(HANDLE hDevice, GLint count, HANDLE *hObjects),
(hDevice,count,hObjects))


WGLPROC_RETURN1(BOOL, wglCopyImageSubDataNV ,
(HGLRC hSrcRC, GLuint srcName, GLenum srcTarget, GLint srcLevel, 
GLint srcX, GLint srcY, GLint srcZ, HGLRC hDstRC, GLuint dstName, 
GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, 
GLint dstZ, GLsizei width, GLsizei height, GLsizei depth),
(hSrcRC,srcName, srcTarget, srcLevel,srcX, srcY,srcZ,
hDstRC,dstName,dstTarget,dstLevel, dstX,dstY,dstZ,
width,height,depth))


WGLPROC_RETURN1(BOOL, wglEnumGpusNV, (UINT iGpuIndex, HGPUNV *phGpu),
(iGpuIndex,phGpu))
WGLPROC_RETURN1(BOOL, wglEnumGpuDevicesNV,
(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice),
(hGpu,iDeviceIndex,lpGpuDevice))
WGLPROC_RETURN1(HDC, wglCreateAffinityDCNV,
(const HGPUNV *phGpuList), (phGpuList))
WGLPROC_RETURN1(BOOL, wglEnumGpusFromAffinityDCNV ,
(HDC hAffinityDC, UINT iGpuIndex, HGPUNV *hGpu),
(hAffinityDC,iGpuIndex,hGpu))
WGLPROC_RETURN1(BOOL, wglDeleteDCNV, (HDC hdc), (hdc))


WGLPROC_RETURN1(int, wglEnumerateVideoDevicesNV ,
(HDC hDC, HVIDEOOUTPUTDEVICENV *phDeviceList),
(hDC,phDeviceList))
WGLPROC_RETURN1(BOOL, wglBindVideoDeviceNV,
(HDC hDC, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice,
const int *piAttribList),
(hDC,uVideoSlot,hVideoDevice,piAttribList))
WGLPROC_RETURN1(BOOL, wglQueryCurrentContextNV,
(int iAttribute, int *piValue), (iAttribute, piValue))


WGLPROC_RETURN1(BOOL, wglJoinSwapGroupNV, (HDC hDC, GLuint group),
(hDC, group))
WGLPROC_RETURN1(BOOL, wglBindSwapBarrierNV,
(GLuint group, GLuint barrier), (group,barrier))
WGLPROC_RETURN1(BOOL, wglQuerySwapGroupNV,
(HDC hDC, GLuint *group, GLuint *barrier),
(hDC,group,barrier))
WGLPROC_RETURN1(BOOL, wglQueryMaxSwapGroupsNV,
(HDC hDC, GLuint *maxGroups, GLuint *maxBarriers),
(hDC, maxGroups, maxBarriers))
WGLPROC_RETURN1(BOOL, wglQueryFrameCountNV, (HDC hDC, GLuint *count),
(hDC, count))
WGLPROC_RETURN1(BOOL, wglResetFrameCountNV ,(HDC hDC), (hDC))



WGLPROC_RETURN1(void*, wglAllocateMemoryNV,
(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority),
(size,readfreq,writefreq,priority))
WGLPROC_VOID( wglFreeMemoryNV, (void *pointer), (pointer))


WGLPROC_RETURN1(BOOL,wglBindVideoCaptureDeviceNV,
(UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice),
(uVideoSlot, hDevice))
WGLPROC_RETURN1(UINT, wglEnumerateVideoCaptureDevicesNV,
(HDC hDc, HVIDEOINPUTDEVICENV *phDeviceList),
(hDc,phDeviceList))
WGLPROC_RETURN1(BOOL, wglLockVideoCaptureDeviceNV,
(HDC hDc, HVIDEOINPUTDEVICENV hDevice),
(hDc,hDevice))
WGLPROC_RETURN1(BOOL, wglQueryVideoCaptureDeviceNV,
(HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int *piValue),
(hDc,hDevice,iAttribute,piValue))
WGLPROC_RETURN1(BOOL, wglReleaseVideoCaptureDeviceNV,
(HDC hDc, HVIDEOINPUTDEVICENV hDevice),
(hDc,hDevice))



WGLPROC_RETURN1(BOOL, wglGetVideoDeviceNV,
(HDC hDC, int numDevices, HPVIDEODEV *hVideoDevice),
(hDC,numDevices,hVideoDevice))
WGLPROC_RETURN1(BOOL, wglReleaseVideoDeviceNV, (HPVIDEODEV hVideoDevice),
(hVideoDevice))
WGLPROC_RETURN1(BOOL,wglBindVideoImageNV,
(HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer),
(hVideoDevice,hPbuffer,iVideoBuffer))
WGLPROC_RETURN1(BOOL, wglReleaseVideoImageNV,
(HPBUFFERARB hPbuffer, int iVideoBuffer),
(hPbuffer,iVideoBuffer))
WGLPROC_RETURN1(BOOL, wglSendPbufferToVideoNV,
(HPBUFFERARB hPbuffer, int iBufferType, unsigned long *pulCounterPbuffer, 
BOOL bBlock),
(hPbuffer,iBufferType,pulCounterPbuffer,bBlock))
WGLPROC_RETURN1(BOOL, wglGetVideoInfoNV,
(HPVIDEODEV hpVideoDevice, unsigned long *pulCounterOutputPbuffer, 
unsigned long *pulCounterOutputVideo),
(hpVideoDevice,pulCounterOutputPbuffer,pulCounterOutputVideo))



WGLPROC_RETURN1(BOOL, wglGetSyncValuesOML,
(HDC hdc, INT64 *ust, INT64 *msc, INT64 *sbc),
(hdc,ust,msc,sbc))
WGLPROC_RETURN1(BOOL, wglGetMscRateOML,
(HDC hdc, INT32 *numerator, INT32 *denominator),
(hdc,numerator,denominator))
WGLPROC_RETURN1(INT64, wglSwapBuffersMscOML,
(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder),
(hdc,target_msc,divisor,remainder))
WGLPROC_RETURN1(INT64, wglSwapLayerBuffersMscOML,
(HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder),
(hdc,fuPlanes,target_msc,divisor,remainder))
WGLPROC_RETURN1(BOOL, wglWaitForMscOML,
(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 *ust,
INT64 *msc, INT64 *sbc),
(hdc,target_msc,divisor,remainder, ust,msc, sbc))
WGLPROC_RETURN1(BOOL, wglWaitForSbcOML,
(HDC hdc, INT64 target_sbc, INT64 *ust, INT64 *msc, INT64 *sbc),
(hdc,target_sbc,ust,msc,sbc))


#endif
