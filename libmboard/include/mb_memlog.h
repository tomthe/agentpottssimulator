/* $Id: mb_memlog.h 1930 2009-07-02 13:47:53Z lsc $ */
/*!
 * \file mb_memlog.h
 * \code
 *      Author: Lee-Shawn Chin 
 *      Date  : Aug 2008 
 *      Copyright (c) 2008 STFC Rutherford Appleton Laboratory
 * \endcode
 * 
 * \brief Header file for src/utils/memlog.c
 * 
 */
#ifndef MB_MEMLOG_H_
#define MB_MEMLOG_H_

#ifdef _LOG_MEMORY_USAGE

/* Memory Logging management routines */
/* ... see src/util/memlog.c ... */
void memlog_init(void);
void memlog_finalise(void);
void memlog_milestone(const char *label);

/* Replacement routines for memory allocation/deallocation */
/* ... see src/util/memlog.c ... */
void memlog_free(void *ptr);
void *memlog_calloc(size_t nmemb, size_t size);
void *memlog_malloc(size_t size);
void *memlog_realloc(void *ptr, size_t size);

/* override memory routines (unless NO_OVERRIDE_MEM_ROUTINES defined) */
#ifndef NO_OVERRIDE_MEM_ROUTINES
    #define free(ptr) memlog_free(ptr)
    #define calloc(nmemb, size) memlog_calloc(nmemb, size)
    #define malloc(size) memlog_malloc(size)
    #define realloc(ptr, size) memlog_realloc(ptr, size)
#endif /* NO_OVERRIDE_MEM_ROUTINES */

#endif /* _LOG_MEMORY_USAGE */

#endif /* MB_MEMLOG_H_ */
