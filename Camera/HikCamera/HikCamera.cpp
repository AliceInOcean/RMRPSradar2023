#include "HikCamera.h"

namespace Camera
{
    void imageCallback(unsigned char *data, MV_FRAME_OUT_INFO_EX *pFrameInfo, void *pUser)
    {
        auto target =static_cast<HikCamera*>(pUser);
        std::chrono::steady_clock::time_point now= std::chrono::steady_clock::now();
        long duration = std::chrono::duration_cast<std::chrono::milliseconds>(now-target->mLastTime).count();
        if (duration>1000)
        {
            target->mFPS =(target->mCount);
            target->mLastTime = now;
            target->mCount = 0;
        }
        target->mCount = target->mCount + 1;
        if(pFrameInfo)
        {
            target->mRawImage = cv::Mat(pFrameInfo->nHeight,pFrameInfo->nWidth,CV_8UC1,data);
        }

    }
}
cv::Mat Camera::HikCamera::convertToBGR(const cv::Mat image)
{
    cv::Mat result;
    if(!image.empty())
        cv::cvtColor(image,result,cv::COLOR_BayerBG2BGR);
    return result;
}



void Camera::HikCamera::open()
{
    MV_CC_DEVICE_INFO_LIST device_list;
    memset(&device_list, 0, sizeof (MV_CC_DEVICE_INFO_LIST));

    MV_CC_EnumDevices(MV_GIGE_DEVICE|MV_USB_DEVICE,&device_list);

    MV_CC_CreateHandle(&mHandle,device_list.pDeviceInfo[mIndex]);

    MV_CC_OpenDevice(mHandle);

    MV_CC_SetEnumValue(mHandle,"TriggerMode",0);

    MV_CC_RegisterImageCallBackEx(mHandle,imageCallback, this);

    MV_CC_StartGrabbing(mHandle);
}

void Camera::HikCamera::close()
{
    MV_CC_StopGrabbing(mHandle);
    MV_CC_CloseDevice(mHandle);
    MV_CC_DestroyHandle(mHandle);
}

//fmt

void Camera::HikCamera::setExposureTime(float exposure_time)
{
    MV_CC_SetFloatValue(mHandle,"ExposureTime",exposure_time);
}


void Camera::HikCamera::setWhiteBalance(int channel, float ratio)
{
    switch (channel)
    {
        case 0:
            MV_CC_SetEnumValue(mHandle,"BalanceRatioSelector",0);
            MV_CC_SetFloatValue(mHandle,"BalanceRatio",ratio);
            break;
        case 1:
            MV_CC_SetEnumValue(mHandle,"BalanceRatioSelector",1);
            MV_CC_SetFloatValue(mHandle,"BalanceRatio",ratio);
            break;
        case 2:
            MV_CC_SetEnumValue(mHandle,"BalanceRatioSelector",2);
            MV_CC_SetFloatValue(mHandle,"BalanceRatio",ratio);
            break;
        default:
            break;
    }
}

void Camera::HikCamera::setGain(float value)
{
    MV_CC_SetFloatValue(mHandle, "Gain", value);
}

float Camera::HikCamera::getFPS()
{
    return mFPS;
}

cv::Mat Camera::HikCamera::getImage()
{
    return convertToBGR(mRawImage);
}