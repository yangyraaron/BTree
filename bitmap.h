/* 
 * File:   bitmap.h
 * Author: wisedulab2
 *
 * Created on November 11, 2013, 6:03 PM
 */

#ifndef BITMAP_H
#define	BITMAP_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    int* bp_create(int);
    void bp_free(int*);
    void bp_set(int*,int);
    int bp_test(int*,int);
    void bp_clear(int*,int);

#ifdef	__cplusplus
}
#endif

#endif	/* BITMAP_H */

