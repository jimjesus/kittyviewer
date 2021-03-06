/** 
 * @file lltextureview.h
 * @brief LLTextureView class header file
 *
 * $LicenseInfo:firstyear=2001&license=viewergpl$
 * 
 * Copyright (c) 2001-2010, Linden Research, Inc.
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

#ifndef LL_LLTEXTUREVIEW_H
#define LL_LLTEXTUREVIEW_H

#include "llcontainerview.h"

class LLViewerFetchedTexture;
class LLTextureBar;
class LLGLTexMemBar;
class LLAvatarTexBar;

class LLTextureView : public LLContainerView
{
	friend class LLTextureBar;
	friend class LLGLTexMemBar;
	friend class LLAvatarTexBar;
protected:
	LLTextureView(const Params&);
	friend class LLUICtrlFactory;
public:
	~LLTextureView();

	/*virtual*/ void draw();
	/*virtual*/ BOOL handleMouseDown(S32 x, S32 y, MASK mask);
	/*virtual*/ BOOL handleMouseUp(S32 x, S32 y, MASK mask);
	/*virtual*/ BOOL handleKey(KEY key, MASK mask, BOOL called_from_parent);

	static void addDebugImage(LLViewerFetchedTexture* image) { sDebugImages.insert(image); }
	static void removeDebugImage(LLViewerFetchedTexture* image) { sDebugImages.insert(image); }
	static void clearDebugImages() { sDebugImages.clear(); }

private:
	BOOL addBar(LLViewerFetchedTexture *image, BOOL hilight = FALSE);
	void removeAllBars();

private:
	BOOL mFreezeView;
	BOOL mOrderFetch;
	BOOL mPrintList;
	
	LLTextBox *mInfoTextp;

	std::vector<LLTextureBar*> mTextureBars;
	U32 mNumTextureBars;

	LLGLTexMemBar* mGLTexMemBar;
	LLAvatarTexBar* mAvatarTexBar;
public:
	static std::set<LLViewerFetchedTexture*> sDebugImages;
};

class LLGLTexSizeBar;
class LLTextureSizeView : public LLContainerView
{
protected:
	LLTextureSizeView(const Params&);
	friend class LLUICtrlFactory;
public:	
	~LLTextureSizeView();

	/*virtual*/ void draw();
	/*virtual*/ BOOL handleHover(S32 x, S32 y, MASK mask) ;
	
	void setType(S32 type) {mType = type ;}
	enum
	{
		TEXTURE_MEM_OVER_SIZE,
		TEXTURE_MEM_OVER_CATEGORY
	};
private:
	//draw background for TEXTURE_MEM_OVER_SIZE
	F32 drawTextureSizeDistributionGraph() ;
	//draw real-time texture mem bar over size
	void drawTextureSizeGraph();

	//draw background for TEXTURE_MEM_OVER_CATEGORY
	F32 drawTextureCategoryDistributionGraph() ;
	//draw real-time texture mem bar over category
	void drawTextureCategoryGraph();

private:
	std::vector<LLGLTexSizeBar*> mTextureSizeBar ;
	LLRect mTextureSizeBarRect ;
	S32    mTextureSizeBarWidth ;	
	S32    mType ;
};
extern LLTextureView *gTextureView;
extern LLTextureSizeView *gTextureSizeView;
extern LLTextureSizeView *gTextureCategoryView;
#endif // LL_TEXTURE_VIEW_H
