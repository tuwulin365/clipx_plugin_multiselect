#ifndef CLIPX_PLUGIN_H
#define CLIPX_PLUGIN_H

#include <ClipXPlugin.h>

class SampleClipXPlugin : public ClipXPlugin
{
public:
    virtual const char *getName();   // Plugin name
    virtual GUID getGUID();          // Plugin unique GUID identifier (change it for your own plugin!)
    virtual void onCreate();         // Creation callback
    virtual void onDestroy();          // Destruction callback, delete everything here, not in this class' destructor
    virtual void about(HWND parent); // About box
};

#endif
