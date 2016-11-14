#include "dsodometry.h"



bool Dsodometry::initialize() {
    image = readChannel<lms::imaging::Image>("IMAGE");

    dso::setting_desiredImmatureDensity = 1000;
    dso::setting_desiredPointDensity = 1200;
    dso::setting_minFrames = 5;
    dso::setting_maxFrames = 7;
    dso::setting_maxOptIterations=4;
    dso::setting_minOptIterations=1;
    dso::setting_logStuff = false;
    dso::setting_kfGlobalWeight = 1.3;


    //printf("MODE WITH CALIBRATION, but without exposure times!\n");
    //setting_photometricCalibration = 2;

    dso::setting_photometricCalibration = 0; //no calibration given
    dso::setting_affineOptModeA = 0;
    dso::setting_affineOptModeB = 0;
    //TODO do we need to set setting_useExposure = 0;

    fullSystem = new dso::FullSystem();
    fullSystem->linearizeOperation=false;
    return true;
}

bool Dsodometry::deinitialize() {
    return true;
}

bool Dsodometry::cycle() {
    /*
        if(setting_fullResetRequested){
            dso::IOWrap::Output3DWrapper* wrap = fullSystem->outputWrapper;
            delete fullSystem;
            if(wrap != 0) wrap->reset();
            fullSystem = new FullSystem();
            fullSystem->linearizeOperation=false;
            fullSystem->outputWrapper = wrap;

            if(undistorter->photometricUndist != 0)
                fullSystem->setGammaFunction(undistorter->photometricUndist->getG());

            dso::setting_fullResetRequested=false;
        }
    */
        //dso::MinimalImageB minImg(image->width(),image->height(),const_cast<unsigned char*>(image->data())); //yay const cast
        dso::ImageAndExposure *myImage = new dso::ImageAndExposure(image->width(),image->height());
        for(int x = 0; x < image->width(); x++){
            for(int y = 0; y<image->height(); y++){
                myImage->image[x+y*image->width()] = (float)image->data()[x+y*image->width()];
            }
        }
        fullSystem->addActiveFrame(myImage, frameID);
        frameID++;
        if(fullSystem->isLost){
            logger.error("system is lost");
            return false;
        }
        //TODO how do we get the position from it?
    return true;
}
