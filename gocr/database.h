//
//  db.h
//  gocr
//
//  Created by Carl Wieland on 8/25/15.
//  Copyright © 2015 Carl Wieland. All rights reserved.
//

#ifndef db_h
#define db_h
#include "job.h"
#include "box.h"

/* declared in database.c */
int load_db(job_t *job);
wchar_t ocr_db(struct box *box1, job_t *job);

#endif /* db_h */
