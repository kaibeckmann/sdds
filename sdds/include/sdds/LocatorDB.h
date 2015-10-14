/*
 * =====================================================================================
 *
 *       Filename:  LocatorDB.h
 *
 *    Description:  LocatorDB class manages the Locator object within the 
 *    systems. It holds a pool for locator objects that might be used for 
 *    incoming packates.
 *    This class is a singelton withing the system, therefor no this reference 
 *    is needed as parameter for the methodes. But the init methode have to be 
 *    called in the init phase of the middleware.
 *    Some of the methodes are abstract and have to be implemented in the 
 *    generaded code!
 *
 *        Version:  1.0
 *        Created:  03.03.2010 10:42:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kai Beckmann (kai), kai-oliver.beckmann@hs-rm.de
 *        Company:  Hochschule RheinMain - DOPSY Labor für verteilte Systeme
 *
 * =====================================================================================
 */
#ifndef  LOCATORDB_H_INC
#define  LOCATORDB_H_INC

#include <stdio.h>
#include "Locator.h"
#include "sdds_types.h"

struct LocatorDB_t;
typedef struct LocatorDB_t* LocatorDB;

#define AbstractAddressField void*

#define SDDS_LOCATORDB_RT_FOUND 4
#define SDDS_LOCATORDB_RT_NOTFOUND 5
#define SDDS_LOCATORDB_RT_NOFREELOCATORS 6
#define SDDS_LOCATORDB_RT_ISINUSE 7



rc_t LocatorDB_init(void);

rc_t LocatorDB_newLocator(Locator* loc);
rc_t LocatorDB_findLocator(Locator toFind, Locator* loc);
rc_t LocatorDB_freeLocator(Locator loc);
rc_t LocatorDB_isUsedLocator(Locator loc);
rc_t LocatorDB_newMultiLocator(Locator* loc);



#endif   /* ----- #ifndef LOCATORDB_H_INC  ----- */
