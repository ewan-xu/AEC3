//
//  PinPointAECAndroidAPI.hpp
//  PinPointAECAndroid
//
//

#ifndef PinPointAEC3AndroidAPI
#define PinPointAEC3AndroidAPI

#ifdef __cplusplus
extern "C"
{
#endif

void* PinPointAEC3AndroidCreate(int sampleRate);
void PinPointAEC3AndroidDelete(void *object);
void PinPointAEC3AndroidProcessCapture(void* object, float* audioBuffer, int numberOfFrames);
void PinPointAEC3AndroidAnalyzeRender(void* object, float* audioBuffer, int numberOfFrames);

#ifdef __cplusplus
}
#endif

#endif
