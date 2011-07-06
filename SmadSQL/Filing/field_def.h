#ifndef __FIELD_DEF_H
#define __FIELD_DEF_H

#include <string>
using std::string;

enum fld_typ;

struct FIELD_DEF{
    string name;
	enum fld_typ type;
};
#endif
