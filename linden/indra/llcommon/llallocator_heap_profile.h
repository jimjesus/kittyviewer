/** 
 * @file llallocator_heap_profile.h
 * @brief Declaration of the parser for tcmalloc heap profile data.
 * @author Brad Kittenbrink
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

#ifndef LL_LLALLOCATOR_HEAP_PROFILE_H
#define LL_LLALLOCATOR_HEAP_PROFILE_H

#include "stdtypes.h"

#include <map>
#include <vector>

class LLAllocatorHeapProfile
{
public:
    typedef int stack_marker;

    typedef std::vector<stack_marker> stack_trace;

    struct line {
        line(U32 live_count, U64 live_size, U32 tot_count, U64 tot_size) :
            mLiveSize(live_size),
            mTotalSize(tot_size),
            mLiveCount(live_count),
            mTotalCount(tot_count)
        {
        }
        U64 mLiveSize, mTotalSize;
        U32 mLiveCount, mTotalCount;
        stack_trace mTrace;
    };

    typedef std::vector<line> lines_t;

    LLAllocatorHeapProfile()
    {
    }

	void parse(std::string const & prof_text);

    void dump(std::ostream & out) const;

public:
    lines_t mLines;
};


#endif // LL_LLALLOCATOR_HEAP_PROFILE_H
