#ifndef SAMPLE_CLIPBOARDMONITOR_H
#define SAMPLE_CLIPBOARDMONITOR_H

#include <ClipXClipboardMonitor.h>

class SampleClipboardMonitor : public ClipXClipboardMonitor
{
public:
    // the user copied some text in the clipboard, return 0 to ignore it, 1 to let clipx record it
    virtual int onNewTextClipboard(const char *text);
    // the user copied a bitmap in the clipboard (HBITMAP format), return 0 to ignore it, 1 to let clipx record it
    virtual int onNewBitmapClipboard(HBITMAP bmp);
    // the user copied a bitmap in the clipboard (packed DIB format), return 0 to ignore it, 1 to let clipx record it
    virtual int onNewDIBitmapClipboard(BITMAPINFO *dib);
    virtual int onNewFileListClipboard(HDROP filelist);
};

#endif
