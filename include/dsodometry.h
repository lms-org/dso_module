#ifndef DSODOMETRY_H
#define DSODOMETRY_H

#include <lms/module.h>
#include <lms/imaging/image.h>

/**
 * @brief LMS module dsodometry
 **/
class Dsodometry : public lms::Module {
    lms::ReadDataChannel<lms::imaging::Image> image;
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
};

#endif // DSODOMETRY_H
