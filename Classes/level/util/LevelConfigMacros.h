#ifndef _LEVEL_CONFIG_MACROS_H_
#define _LEVEL_CONFIG_MACROS_H_

#include "base/ccMacros.h"

/* SOLO rapidxml::xml_node<>*  */

#define Optional(x) x != NULL? x->value() : "";
#define OptionalTag(x) x != NULL? x : NULL;

#define NotNull(x)  Optional(x)  CCASSERT(x != NULL,"Config data cannot be NULL");	
#define NotNullTag(x) OptionalTag(x)  CCASSERT(x != NULL,"Config data cannot be NULL");	

#define OptionalReturn(x) Optional(x) if(x != NULL) return;

#define MapNullToZero(x) x == ""? "0" : x;

#endif
