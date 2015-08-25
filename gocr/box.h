//
//  box.h
//  gocr
//
//  Created by Carl Wieland on 8/25/15.
//  Copyright © 2015 Carl Wieland. All rights reserved.
//

#ifndef box_h
#define box_h

#include "unicode.h"  /* FORMAT definition */
#include "list.h"
#include <stddef.h>
#ifdef HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif

#define NumAlt 10 /* maximal number of alternative chars (table length) */
#define MaxNumFrames 8       /* maximum number of frames per char/box */
#define MaxFrameVectors 128  /* maximum vectors per frame (*8=1KB/box) */
/* ToDo: use only malloc_box(),free_box(),copybox() for creation, destroy etc.
 *       adding reference_counter to avoid pointer pointing to freed box
 */
struct box { /* this structure should contain all pixel infos of a letter */
    int x0,x1,y0,y1,x,y,dots; /* xmin,xmax,ymin,ymax,reference-pixel,i-dots */
    int num_boxes, /* 1 "abc", 2 "!i?", 3 "&auml;" (composed objects) 0.41 */
    num_subboxes;   /* 1 for "abdegopqADOPQR", 2 for "B"  (holes) 0.41 */
    wchar_t c;		/* detected char (same as tac[0], obsolete?) */
    wchar_t modifier;	/* default=0, see compose() in unicode.c */
    int num;		/* same number = same char */
    int line;		/* line number (points to struct tlines lines) */
    int m1,m2,m3,m4;	/* m2 = upper boundary, m3 = baseline */
    /* planed: sizeof hole_1, hole_2, certainty (run1=100%,run2=90%,etc.) */
    pix *p;		/* pointer to pixmap (v0.2.5) */
    /* tac, wac is used together with setac() to manage very similar chars */
    int num_ac;         /* length of table (alternative chars), default=0 */
    wchar_t tac[NumAlt]; /* alternative chars, only used by setac(),getac() */
    int     wac[NumAlt]; /* weight of alternative chars */
    char   *tas[NumAlt]; /* alternative UTF8-strings or XML codes if tac[]=0 */
    /*   replacing old obj */
    /* ToDo: (*obj)[NumAlt] + olen[NumAlt] ??? */
    /* ToDo: bitmap for possible Picture|Object|Char ??? */
    /*  char    *obj; */     /* pointer to text-object ... -> replaced by tas[] */
    /*  ... (melted chars, barcode, picture coords, ...) */
    /*  must be freed before box is freed! */
    /*  do _not_ copy only the pointer to object */
    /* --------------------------------------------------------
     *  extension since v0.41 js05, Store frame vectors,
     *  which is a table of vectors sourrounding the char and its
     *  inner white holes. The advantage is the independence from
     *  resolution, handling of holes, overlap and rotation.
     * --------------------------------------------------------- */
    int num_frames;      /* number of frames: 1 for cfhklmnrstuvwxyz */
    /*                   2 for abdegijopq */
    int frame_vol[MaxNumFrames]; /* volume inside frame +/- (black/white) */
    int frame_per[MaxNumFrames]; /* periphery, summed length of vectors */
    int num_frame_vectors[MaxNumFrames]; /* index to next frame */
    /* biggest frame should be stored first (outer frame) */
    /* biggest has the maximum pair distance */
    /* num vector loops */
    int frame_vector[MaxFrameVectors][2]; /* may be 16*int=fixpoint_number */
    
};
typedef struct box Box;



#endif /* box_h */
