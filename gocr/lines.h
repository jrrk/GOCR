//
//  lines.h
//  gocr
//
//  Created by Carl Wieland on 8/25/15.
//  Copyright © 2015 Carl Wieland. All rights reserved.
//

#ifndef lines_h
#define lines_h

#define MAXlines 1024

/* ToDo: if we have a tree instead of a list, a line could be a node object */
struct tlines {
    int num;
    int dx, dy;		/* direction of text lines (straight/skew) */
    int m1[MAXlines],   /* start of line = upper bound of 'A' */
    m2[MAXlines],   /* upper bound of 'e' */
    m3[MAXlines],	/* lower bound of 'e' = baseline */
    m4[MAXlines];	/* stop of line = lower bound of 'q' */
    /* ToDo: add sureness per m1,m2 etc? */
    int x0[MAXlines],
    x1[MAXlines];	/* left and right border */
    int wt[MAXlines];   /* weight, how sure thats correct in percent, v0.41 */
    int pitch[MAXlines]; /* word pitch (later per box?), v0.41 */
    int mono[MAXlines];  /* spacing type, 0=proportional, 1=monospaced */
};


#endif /* lines_h */
