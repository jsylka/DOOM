// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// DESCRIPTION:
//	WAD I/O functions.
//
//-----------------------------------------------------------------------------


#ifndef __W_WAD__
#define __W_WAD__


#ifdef __GNUG__
#pragma interface
#endif


//
// TYPES
//

/**
 * Wad info is a header at the beginning of the .wad
 *
 * I wad is an internal wad
 * P was is a patch wad
 *
 * 1st four bytes are for the magic number (iwad | pwad)
 * next 4 bytes are for the number of lumps in the wad
 * next 4 bytes is for the address of the directory listing (near end of wad)
 */
typedef struct
{
    // Should be "IWAD" or "PWAD".
    char		identification[4];		
    int			numlumps;
    int			infotableofs;
    
} wadinfo_t;


/**
 * The directory at location of wadinfo_t.int has 16 byte sections
 *
 * first 4 is the position in the wad of the lump
 * second 4 is the size in bytes
 * name is a 8 char name, if the name is less than 8 chars its padded with 0s
 */
typedef struct
{
    int			filepos;
    int			size;
    char		name[8];
    
} filelump_t;

//
// WADFILE I/O related stuff.
// So a lump info - holds book keeping info, and the main part is the handle which is a file and a position into the file
// where the data resides, if we are so inclined we can 'cache' the data in lumpcache
//
typedef struct
{
    char	name[8];
    int		handle;
    int		position;
    int		size;
} lumpinfo_t;

// all lumps will be in this look up table - lump # -> data (we use this instead of doing disk i/o in the wad file)
extern	void**		lumpcache;
extern	lumpinfo_t*	lumpinfo;
extern	int		numlumps;

/**
 * Loads multiple wad files - called from D_DoomMain
 */
void    W_InitMultipleFiles (char** filenames);
/**
 *
 */
void    W_Reload (void);

/**
 * Given a name, we check lumpinfo for the lump, it does a really cool string comparison
 */
int	W_CheckNumForName (char* name);
/**
 * get the lump index by name
 */
int	W_GetNumForName (char* name);

/**
 * Gets the size of the lump by index
 */
int	W_LumpLength (int lump);
/**
 * Reads data from wad file into buffer - indexed by lump
 */
void    W_ReadLump (int lump, void *dest);

/**
 * given an index to a lump and a tag, we will cache the lump data and return it to you
 */
void*	W_CacheLumpNum (int lump, int tag);
/**
 * given a name and a tag, we will cache the lump data and return it to you
 */
void*	W_CacheLumpName (char* name, int tag);




#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
