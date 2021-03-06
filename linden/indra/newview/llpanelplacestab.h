/** 
 * @file llpanelplacestab.h
 * @brief Tabs interface for Side Bar "Places" panel
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

#ifndef LL_LLPANELPLACESTAB_H
#define LL_LLPANELPLACESTAB_H

#include "llpanel.h"

class LLPanelPlaces;

class LLPanelPlacesTab : public LLPanel
{
public:
	LLPanelPlacesTab() : LLPanel() {}
	virtual ~LLPanelPlacesTab() {}

	virtual void onSearchEdit(const std::string& string) = 0;
	virtual void updateVerbs() = 0;		// Updates buttons at the bottom of Places panel
	virtual void onShowOnMap() = 0;
	virtual void onShowProfile() = 0;
	virtual void onTeleport() = 0;
	virtual bool isSingleItemSelected() = 0;

	bool isTabVisible(); // Check if parent TabContainer is visible.

	void setPanelPlacesButtons(LLPanelPlaces* panel);
	void onRegionResponse(const LLVector3d& landmark_global_pos,
										U64 region_handle,
										const std::string& url,
										const LLUUID& snapshot_id,
										bool teleport);

	const std::string& getFilterSubString() { return sFilterSubString; }
	void setFilterSubString(const std::string& string) { sFilterSubString = string; }

protected:
	LLButton*				mTeleportBtn;
	LLButton*				mShowOnMapBtn;
	LLButton*				mShowProfile;

	// Search string for filtering landmarks and teleport history locations
	static std::string		sFilterSubString;
};

#endif //LL_LLPANELPLACESTAB_H
