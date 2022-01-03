#include <precomp.h>
#include "plugin.h"
#include "SampleClipboardMonitor.h"
#include "SampleConfigPage.h"

#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

_DECLARE_SERVICETSINGLE(svc_ClipXClipboardMonitor, SampleClipboardMonitor);

//for debug
void ClipxPluginLog(char *pStr, int iLine)
{
    ofstream ofile;
    ofile.open("c:\\log.txt", ios::app);
    if (ofile)
    {
        ofile << pStr << " : " << iLine << endl;
        ofile.close();        
    }
}


// the user copied some text in the clipboard
int SampleClipboardMonitor::onNewTextClipboard(const char *text)
{
    return 1;
}

// the user copied a bitmap in the clipboard (HBITMAP format)
int SampleClipboardMonitor::onNewBitmapClipboard(HBITMAP bmp)
{
    return 1;
}

// the user copied a bitmap in the clipboard (packed DIB format)
int SampleClipboardMonitor::onNewDIBitmapClipboard(BITMAPINFO *dib)
{
    return 1;
}

int SampleClipboardMonitor::onNewFileListClipboard(HDROP filelist)
{
    return 1;
}

