#ifndef XLAYOUTDISPLAYS_MODE_H
#define XLAYOUTDISPLAYS_MODE_H

#include <memory>
#include <X11/extensions/Xrandr.h>

// a mode that may be used by an Xrandr display
class Mode {
public:
    Mode(const RRMode &rrMode, const unsigned int &width, const unsigned int &height, const unsigned int &refresh) :
            rrMode(rrMode), width(width), height(height), refresh(refresh) {
    }

    Mode(const RRMode id, const XRRScreenResources *resources);

    virtual ~Mode() {
    }

    // order by width, refresh, height in descending order
    bool operator<(const Mode &o);

    RRMode rrMode;
    unsigned int width;
    unsigned int height;
    unsigned int refresh;
};

typedef std::shared_ptr<Mode> ModeP;

#endif //XLAYOUTDISPLAYS_MODE_H