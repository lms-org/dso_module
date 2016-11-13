#include "dsodometry.h"
#include "dsodometry.h"

#include "util/settings.h"
#include "FullSystem/FullSystem.h"


using namespace dso;

bool Dsodometry::initialize() {
    image = readChannel<lms::imaging::Image>("IMAGE");
    return true;
}

bool Dsodometry::deinitialize() {
    return true;
}

bool Dsodometry::cycle() {
    cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::MONO8);
        assert(cv_ptr->image.type() == CV_8U);
        assert(cv_ptr->image.channels() == 1);


        if(setting_fullResetRequested)
        {
            IOWrap::Output3DWrapper* wrap = fullSystem->outputWrapper;
            delete fullSystem;
            if(wrap != 0) wrap->reset();
            fullSystem = new FullSystem();
            fullSystem->linearizeOperation=false;
            fullSystem->outputWrapper = wrap;
            if(undistorter->photometricUndist != 0)
                fullSystem->setGammaFunction(undistorter->photometricUndist->getG());
            setting_fullResetRequested=false;
        }

        MinimalImageB minImg((int)cv_ptr->image.cols, (int)cv_ptr->image.rows,(unsigned char*)cv_ptr->image.data);
        ImageAndExposure* undistImg = undistorter->undistort<unsigned char>(&minImg, 1,0, 1.0f);
        fullSystem->addActiveFrame(undistImg, frameID);
        frameID++;
    delete undistImg;
    return true;
}
