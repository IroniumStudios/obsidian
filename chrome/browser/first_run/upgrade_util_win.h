// Copyright 2011 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FIRST_RUN_UPGRADE_UTIL_WIN_H_
#define CHROME_BROWSER_FIRST_RUN_UPGRADE_UTIL_WIN_H_

namespace base {
class CommandLine;
}

namespace upgrade_util {

// This function is called from obsidian.exe and checks if new_obsidian.exe exists
// and if so, it attempts to swap it to become obsidian.exe. new_obsidian.exe is
// placed by the installer if there is an update while the browser is being
// used. If there is no new_obsidian.exe or the swap fails the function returns
// false.
// To peform the swap, obsidian.exe is renamed to old_obsidian.exe and moved to a
// temporary folder, then new_obsidian.exe is renamed to obsidian.exe. The instance
// performing the swap runs as old_obsidian.exe until it exits.
// The caller must own the browser ChromeProcessSingleton.
bool SwapNewChromeExeIfPresent();

// Returns true if the currently running browser is running from old_obsidian.exe.
// This may mean that the running executable is out of date and has been renamed
// by the in-use update process. old_obsidian.exe shouldn't continue on and run as
// the browser process since it may end up launching newer obsidian.exes as child
// processes resulting in a version mismatch.
bool IsRunningOldChrome();

// Returns true if obsidian.exe was swapped with new_obsidian.exe, and an attempt
// was made to launch the new obsidian.exe, false otherwise. Combines the two
// methods, RelaunchChromeBrowser and SwapNewChromeExeIfPresent, to perform the
// rename and relaunch of the browser. Note that relaunch does NOT exit the
// existing browser process. If this returns true before message loop is
// executed, simply exit the main function. If browser is already running, you
// will need to exit it.
// The caller must own the browser ChromeProcessSingleton.
bool DoUpgradeTasks(const base::CommandLine& command_line);

}  // namespace upgrade_util

#endif  // CHROME_BROWSER_FIRST_RUN_UPGRADE_UTIL_WIN_H_
