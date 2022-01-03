#include <precomp.h>
#include "plugin.h"

// Construct the plugin object and export it

DECLARE_CLIPX_PLUGIN(SampleClipXPlugin)

// plugin implementation

#define PLUGIN_NAME "ClipX Multiselect"
#ifdef _DEBUG
#define PLUGIN_VER  "v1.00 debug"
#else
#define PLUGIN_VER  "v1.00"
#endif
#define PLUGIN_TM   "2022-01-03"

const char *SampleClipXPlugin::getName()
{
    return PLUGIN_NAME " " PLUGIN_VER;
}

GUID SampleClipXPlugin::getGUID()
{
    // This is the GUID for your plugin, you must change it to your own when you create your own plugin.
    // To do this, use GUIDGEN.EXE, which comes with Microsoft VisualC++
    // {D8D22477-355B-40F4-89A3-1AED442D5E66}
    static const GUID PLUGIN_GUID =
    { 0xd8d22477, 0x355b, 0x40f4, { 0x89, 0xa3, 0x1a, 0xed, 0x44, 0x2d, 0x5e, 0x66 } };

    return PLUGIN_GUID;
}

void SampleClipXPlugin::onCreate()
{
    // plugin is loaded
}

void SampleClipXPlugin::onDestroy()
{
    // plugin is unloaded
}

void SampleClipXPlugin::about(HWND parent)
{
    MessageBox(parent, PLUGIN_NAME " " PLUGIN_VER " " PLUGIN_TM "\n\n同时选择粘贴多条文本记录。\ntuwulin365@126.com", "关于", MB_ICONINFORMATION | MB_OK);
}

