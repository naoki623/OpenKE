#ifndef VALID_H
#define VALID_H
#include "Setting.h"
#include "Reader.h"
#include "Corrupt.h"

INT lastValidHead = 0;
INT lastValidTail = 0;
INT lastValidRel = 0;
	
REAL l_valid_filter_tot = 0;
REAL r_valid_filter_tot = 0;
REAL l1_valid_filter_tot = 0;
REAL r1_valid_filter_tot = 0;
REAL rel_valid_filter_tot = 0;
REAL rel1_valid_filter_tot = 0;

REAL validRelHit1 = 0;
REAL validRelHit10 = 0;
REAL validLinkHit1 = 0;
REAL validLinkHit10 = 0;

extern "C"
void validInit() {
    lastValidHead = 0;
    lastValidTail = 0;
    lastValidRel = 0;
    l_valid_filter_tot = 0;
    r_valid_filter_tot = 0;
    l1_valid_filter_tot = 0;
    r1_valid_filter_tot = 0;
    rel_valid_filter_tot = 0;
    rel1_valid_filter_tot = 0;
    validRelHit1 = 0;
    validRelHit10 = 0;
    validLinkHit1 = 0;
    validLinkHit10 = 0;
}

extern "C"
void getValidHeadBatch(INT *ph, INT *pt, INT *pr) {
    for (INT i = 0; i < entityTotal; i++) {
	ph[i] = i;
	pt[i] = validList[lastValidHead].t;
	pr[i] = validList[lastValidHead].r;
    }
}

extern "C"
void getValidTailBatch(INT *ph, INT *pt, INT *pr) {
    for (INT i = 0; i < entityTotal; i++) {
	ph[i] = validList[lastValidTail].h;
	pt[i] = i;
	pr[i] = validList[lastValidTail].r;
    }
}

extern "C"
void getValidRelBatch(INT *ph, INT *pt, INT *pr) {
    for (INT i = 0; i < relationTotal; i++) {
	ph[i] = validList[lastValidRel].h;
	pt[i] = validList[lastValidRel].t;
	pr[i] = i;
    }
}

extern "C"
void validHead(REAL *con) {
    INT h = validList[lastValidHead].h;
    INT t = validList[lastValidHead].t;
    INT r = validList[lastValidHead].r;
    REAL minimal = con[h];
    INT l_filter_s = 0;
    for (INT j = 0; j < entityTotal; j++) {
	if (j != h) {
	    REAL value = con[j];
   	    if (value < minimal && ! _find(j, t, r)) {
		l_filter_s += 1;
	    }
	}
    }
    if (l_filter_s < 10) l_valid_filter_tot += 1;
    if (l_filter_s < 1) l1_valid_filter_tot += 1;
    lastValidHead ++;
}

extern "C"
void validTail(REAL *con) {
    INT h = validList[lastValidTail].h;
    INT t = validList[lastValidTail].t;
    INT r = validList[lastValidTail].r;
    REAL minimal = con[t];
    INT r_filter_s = 0;
    for (INT j = 0; j < entityTotal; j++) {
	if (j != t) {
	    REAL value = con[j];
	    if (value < minimal && ! _find(h, j, r)) {
	        r_filter_s += 1;
	    }
	}
    }
    if (r_filter_s < 10) r_valid_filter_tot += 1;
    if (r_filter_s < 1) r1_valid_filter_tot += 1;
    lastValidTail ++;
}

REAL validHit10 = 0;
extern "C"
REAL  getValidHit10() {
    l_valid_filter_tot /= validTotal;
    r_valid_filter_tot /= validTotal;
    validHit10 = (l_valid_filter_tot + r_valid_filter_tot) / 2;
   // printf("result: %f\n", validHit10);
    return validHit10;
}

extern "C"
void validRel(REAL *con) {
    INT h = validList[lastValidRel].h;
    INT t = validList[lastValidRel].t;
    INT r = validList[lastValidRel].r;
    REAL minimal = con[r];
    INT rel_filter_s = 0;
    for (INT j = 0; j < relationTotal; j++) {
	if (j != r) {
	    REAL value = con[j];
	    if (value < minimal && ! _find(h, t, j)) {
	        rel_filter_s += 1;
	    }
	}
    }
    if (rel_filter_s < 10) rel_valid_filter_tot += 1;
    if (rel_filter_s < 1) rel1_valid_filter_tot += 1;
    lastValidRel ++;
}

extern "C"
REAL  getValidRelHit10() {
    validRelHit10 = rel_valid_filter_tot / validTotal;
    return validRelHit10;
}


extern "C"
REAL  getValidRelHit1() {
    validRelHit1 = rel1_valid_filter_tot / validTotal;
    return validRelHit1;
}

extern "C"
REAL  getValidLinkHit10() {
    l_valid_filter_tot /= validTotal;
    r_valid_filter_tot /= validTotal;
    validLinkHit10 = (l_valid_filter_tot + r_valid_filter_tot) / 2;
    return validLinkHit10;
}

extern "C"
REAL  getValidLinkHit1() {
    l1_valid_filter_tot /= validTotal;
    r1_valid_filter_tot /= validTotal;
    validLinkHit1 = (l1_valid_filter_tot + r1_valid_filter_tot) / 2;
    return validLinkHit1;
}

#endif
