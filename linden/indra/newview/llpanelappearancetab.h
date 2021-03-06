/** 
 * @file llpanelappearancetab.h
 * @brief Tabs interface for Side Bar "My Appearance" panel
 *
 * $LicenseInfo:firstyear=2009&license=viewergpl$
 * 
 * Copyright (c) 2009-2010, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlife.com/developers/opensource/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlife.com/developers/opensource/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 * 
 */

#ifndef LL_LLPANELAPPEARANCETAB_H
#define LL_LLPANELAPPEARANCETAB_H

#include "llpanel.h"

class LLPanelAppearanceTab : public LLPanel
{
public:
	LLPanelAppearanceTab() : LLPanel() {}
	virtual ~LLPanelAppearanceTab() {}

	virtual void setFilterSubString(const std::string& string) = 0;

	virtual bool isActionEnabled(const LLSD& userdata) = 0;

	virtual void showGearMenu(LLView* spawning_view) = 0;

	static const std::string& getFilterSubString() { return sFilterSubString; }

protected:
	static std::string		sFilterSubString;
};

#endif //LL_LLPANELAPPEARANCETAB_H
