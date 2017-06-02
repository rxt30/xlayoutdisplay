#include "Layout.h"
#include "xrandrrutil.h"

using namespace std;

Layout::Layout(int argc, char **argv) :
    settings(Settings(argc, argv)),
    displs(discoverDispls()) {
}

const int Layout::apply() {

    // output verbose information
    if (settings.verbose || settings.info)
        printf("%s\n\nlid %s\n",
               renderUserInfo(displs).c_str(), Laptop::instance()->isLidClosed() ? "closed" : "open or not present");

    // current info is all output, we're done
    if (settings.info)
        return EXIT_SUCCESS;

    // determine desired state
    orderDispls(displs, settings.order);
    activateDispls(displs, settings.primary);

    // arrange mirrored or left to right
    if (settings.mirror)
        mirrorDispls(displs);
    else
        ltrDispls(displs);

    // determine DPI for all displays
    string dpiExplaination = calculateDpi(displs);
    if (settings.verbose)
        printf("\n%s\n", dpiExplaination.c_str());

    // render desired cmd for xrandr
    const string xrandrCmd = renderCmd(displs);
    if (settings.verbose || settings.dryRun)
        printf("\n%s\n", xrandrCmd.c_str());

    // execute xrandr or exit
    if (settings.dryRun)
        return EXIT_SUCCESS;
    else
        return system(xrandrCmd.c_str());
}
