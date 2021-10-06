/*
 * Copyright 2000-2021, Hare Team. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef __GENRE_LIST_H__
#define __GENRE_LIST_H__

#define NUM_GENRES 115
#define OTHER_INDEX 12

class GenreList {
public:
	GenreList();
	~GenreList();
	
	static BString Genre(int genreindex);
	static int Genre(BString genre);
	static int NumGenres();
	static int GenreSort(const void* g1, const void* g2);
};

#endif

