/*
*
* Copyright (c) 2018-2019 TEE.COM. All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef _TEE_CLASSIFY_ENGINE_H_
#define _TEE_CLASSIFY_ENGINE_H_
#include "TEETypes.h"
#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
    #define NXDLL __declspec(dllimport)
#else
    #define NXDLL 
#endif
    typedef enum {
        ePixfmtBGR = 0, // BGRBGR
        ePixfmtRGB = 1, // RGBRGB
    }NXPixFmt;

    typedef struct {
        int w;
        int h;
        NXPixFmt pixfmt;
        unsigned char *data;
    }NXImg;

    /* Inference engine send result data callback function */
    typedef NXRet(*LPResultCB)(nxvoid *pPrivateData, unsigned char const *retBuf, int bufLen, unsigned long long id, int classNum);

    typedef struct {
        int stickNum;
        int threadNum;
		int netType;
		int classNum;
		int sg_beginID;
		int delayTime;
        char const *modelPath; /* stick model + host model path */
        char const *stickCNNName; /* stick cnn file name (absolute file name) */
        char const *hostNetName; /* post-process network run on host (absolute file name) */
        LPResultCB pCB;
        nxvoid *pCBData;
    }NXEngineConf;

    /*  Create inference engine */
    NXRet NXDLL NXCreateInferenceEngine(nxvoid **ppEngine, NXEngineConf const *pConf);

    /* send an image to engine and engine set *pID value. engine will send the id to callback function */
    NXRet NXDLL NXPushTask(nxvoid *engine, NXImg const *pImg, unsigned long long *pID);

    /* clear all task */
    NXRet NXDLL NXClearAllTask(nxvoid *engine);

    NXRet NXDLL NXDestroyInferenceEngine(nxvoid *pEngine);
#ifdef __cplusplus
}
#endif
#endif // _TEE_CLASSIFY_ENGINE_H_