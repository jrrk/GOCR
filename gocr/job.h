//
//  job.h
//  gocr
//
//  Created by Carl Wieland on 8/25/15.
//  Copyright © 2015 Carl Wieland. All rights reserved.
//

#ifndef job_h
#define job_h
#include "unicode.h"  /* FORMAT definition */
#include "list.h"
#include <stddef.h>
#ifdef HAVE_GETTIMEOFDAY
#include <sys/time.h>
#endif
#include "pnm.h"
#include "list.h"
#include "lines.h"
typedef struct cfgStruct {    /* configuration */
    int cs;   /* critical grey value (pixel<cs => black pixel) */
    /* range: 0..255,  0 means autodetection */
    int spc;  /* spacewidth/dots (0 = autodetect); default value: 0 */
    int mode; /* operation modes; default value: 0 */
    /* operation mode (see --help) */
    int dust_size;    /* dust size; default value: 10 */
    int only_numbers; /* numbers only; default value: 0 */
    int verbose; /* verbose mode; default value: 0 */
    /* verbose option (see --help) */
    FORMAT out_format; /* output format; default value: ISO8859_1 */
    char *lc; /* debuglist of chars (_ = not recognized chars) */
    /* default value: "_" */
    char *db_path; /* pathname for database; default value: NULL */
    char *cfilter; /* char filter; default value: NULL, ex: "A-Za-z" */
    /* limit of certainty where chars are accepted as identified */
    int  certainty; /* in units of 100 (percent); 0..100; default 95 */
    char *unrec_marker; /* output this string for every unrecognized char */
} cfgStruct;

typedef struct resStruct {         /* results */
    List boxlist;  /* store every object in a box, which contains */
    /* the characteristics of the object (see struct box) */
    List linelist; /* recognized text lines after recognition */
    
    struct tlines lines; /* used to access to line-data (statistics) */
    /* here the positions (frames) of lines are */
    /* stored for further use */
    int avX,avY;         /* average X,Y (avX=sumX/numC) */
    int sumX,sumY,numC;  /* sum of all X,Y; num chars */
}resStruct;

typedef struct tmpStruct { /* temporary stuff, e.g. buffers */
#ifdef HAVE_GETTIMEOFDAY
    struct timeval init_time; /* starting time of this job */
#endif
    pix ppo; /* pixmap for visual debugging output, obsolete */
    
    /* sometimes recognition function is called again and again, if result was 0
     n_run tells the pixel function to return alternative results */
    int n_run;   /* num of run, if run_2 critical pattern get other results */
    /* used for 2nd try, pixel uses slower filter function etc. */
    List dblist; /* list of boxes loaded from the character database */
}tmpStruct;

typedef struct srcStruct {       /* source data */
    char *fname; /* input filename; default value: "-" */
    pix p;       /* source pixel data, pixelmap 8bit gray */
} srcStruct;

/* job_t contains all information needed for an OCR task */
typedef struct job_t {
    struct srcStruct src;
    struct tmpStruct tmp;
    struct resStruct res;
    struct cfgStruct cfg;
} job_t;

/* initialze job structure */
void job_init(job_t *job);        /* once for cfg and db */
void job_init_image(job_t *job);  /* for each of a multiimage */

/* free job structure */
void job_free_image(job_t *job); /* for each of a multiimage */

/* FIXME jb: remove JOB; 2010-09-25 renamed to OCR_JOB */
/*  as a first step OCR_JOB will be remain in DO_DEBUG mode only */
extern job_t *OCR_JOB;

#endif /* job_h */
