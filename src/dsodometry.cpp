#include "dsodometry.h"
#include "MyIOWrapper.h"


bool Dsodometry::initialize() {
    image = readChannel<lms::imaging::Image>("IMAGE");
    frameID = 0;

    //set some default values
    dso::setting_desiredImmatureDensity = 1000;
    dso::setting_desiredPointDensity = 1200;
    dso::setting_minFrames = 5;
    dso::setting_maxFrames = 7;
    dso::setting_maxOptIterations=4;
    dso::setting_minOptIterations=1;
    dso::setting_logStuff = false;
    dso::setting_kfGlobalWeight = 1.3;


    //disable calibration (just for testing)
    dso::setting_photometricCalibration = 0; //no calibration given
    dso::setting_affineOptModeA = 0;
    dso::setting_affineOptModeB = 0;

    //TODO do we need to set
    dso::setting_useExposure = 0;

    //create dso fullsystem
    fullSystem = new dso::FullSystem();
    fullSystem->linearizeOperation=false;
    //TODO what to do as we get the image from the camera? fullSystem->setGammaFunction(reader->getPhotometricGamma());
    //add the IOWrapper
    fullSystem->outputWrapper.push_back(new dso::IOWrap::SampleOutputWrapper());

    if(!fullSystem->initFailed){
        logger.error("init")<<"fullSystem initFailed";
        return false;
    }
    return true;
}

bool Dsodometry::deinitialize() {
    logger.info("deinitialize")<<"waiting for dso";
    fullSystem->blockUntilMappingIsFinished();
    fullSystem->printResult("dso_result.txt");
    logger.info("deinitialize")<<"printed dso result";
    return true;
}

bool Dsodometry::cycle() {
    if(!fullSystem->initialized){
        logger.error("cycle")<<"fullSystem not initialized";
        return false;
    }
    //get the image from the camera
    dso::ImageAndExposure *myImage = new dso::ImageAndExposure(image->width(),image->height());
    for(int x = 0; x < image->width(); x++){
        for(int y = 0; y<image->height(); y++){
            myImage->image[x+y*image->width()] = (float)image->data()[x+y*image->width()];
        }
    }
    //Add the new image
    logger.debug("adding new image, id")<<frameID;
    fullSystem->addActiveFrame(myImage, frameID);
    frameID++;

    //check if the system is lost
    if(fullSystem->isLost){
        logger.error("system is lost");
        return false;
    }
    //print the results
    std::string myString;
    fullSystem->printResult(myString);
    logger.error("result: ")<<myString; //empty :/
    return true;
}
