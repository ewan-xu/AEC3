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

__attribute__(( visibility("default") ))  void* PinPointAEC3AndroidCreate(int sampleRate);
__attribute__(( visibility("default") ))  void PinPointAEC3AndroidDestroy(void *object);
__attribute__(( visibility("default") ))  void PinPointAEC3AndroidProcessCapture(void* object, float* audioBuffer, int numberOfFrames);
__attribute__(( visibility("default") ))  void PinPointAEC3AndroidAnalyzeRender(void* object, float* audioBuffer, int numberOfFrames);

#ifdef __cplusplus
}
#endif

#endif
