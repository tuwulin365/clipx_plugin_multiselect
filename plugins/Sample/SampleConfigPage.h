#ifndef SAMPLE_CONFIGPAGE_H
#define SAMPLE_CONFIGPAGE_H

#include <ClipXConfigPage.h>

extern int gb_enabled;

extern int gb_set1_enabled;
extern int gb_set1_save_full;
extern int gb_set1_save_history;
extern int gb_set1_save_newline;
extern int gb_set1_full_match;
extern char gs_set1_regex[4096];
extern char gs_set1_file[4096];

extern int gb_set2_enabled;
extern int gb_set2_save_full;
extern int gb_set2_save_history;
extern int gb_set2_save_newline;
extern int gb_set2_full_match;
extern char gs_set2_regex[4096];
extern char gs_set2_file[4096];

extern HWND g_last_dlg;

class SampleConfigPage : public ClipXConfigPage
{
    // return the name that appears in the config list
    virtual const char *getPageTitle();
    // save settings to ini
    virtual void saveSettings(const char *inifile, const char *section);
    // load settings from ini
    virtual void loadSettings(const char *inifile, const char *section);
    // create and return the config page
    virtual HWND createPage(HWND parent);
    // settings should be copied to dialog's work variables
    virtual void copySettings();
    // settings should be validated (user clicked ok/apply)
    virtual void applySettings();
};

#endif
