#include "CheckMark.h"

#include <Debug.h>

CheckMark::CheckMark()
	:
	BBitmap(BRect(0, 0, kImageWidth, kImageHeight), kImageColorSpace)
{
	SetBits(kImageBits, BitsLength(), 0, kImageColorSpace);
}
