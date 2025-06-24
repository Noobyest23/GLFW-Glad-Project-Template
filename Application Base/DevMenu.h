#ifndef NAPP_DEVMENU
#define NAPP_DEVMENU

#include "string"
#include "query.h"

class DevMenu {
public:
    static void Draw();
    static void SetVisible(bool visible);
    static bool IsVisible();

    static void UpdateRenderInfo(RenderInfo);

    static bool shouldQuery;
private:
    static bool visible;

    static RenderInfo lastQueryInfo;
};


#endif // !NAPP_DEVMENU
