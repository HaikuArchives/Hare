/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#include "CheckMark.h"

#include <Debug.h>

CheckMark::CheckMark()
	:
	BBitmap(BRect(0, 0, kImageWidth, kImageHeight), kImageColorSpace)
{
	SetBits(kImageBits, BitsLength(), 0, kImageColorSpace);
}
