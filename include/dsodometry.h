#ifndef DSODOMETRY_H
#define DSODOMETRY_H

#include <lms/module.h>

/**
 * @brief LMS module dsodometry
 **/
class Dsodometry : public lms::Module {
public:
    bool initialize() override;
    bool deinitialize() override;
    bool cycle() override;
};

#endif // DSODOMETRY_H
