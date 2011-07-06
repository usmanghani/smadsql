%{
//////////////////////////////////////////////////
// SMAD-SQL v0.1
// Copyleft (C)2003 by:
// Faisal Nasim (Email: Faisal@Nasim.org)
// Usman Ghani (Email: worldsoft64@yahoo.com)
//
// THIS CODE IS LICENSED UNDER GNU GPL
//////////////////////////////////////////////////

// LEXER (developer: Faisal@Nasim.org)
// $Id: Server.hpp,v 1.1 2003/06/13 17:32:17 faisal Exp faisal $

#include <base.hpp>
#include "sqlgrammar.hpp"

unsigned long SMADlineno = 1;
%}
%option c++
%option interactive

SIN_COMMENT		(\/\/).*?\n
MUL_COMMENT		\/\*([^*\0]*)\*\/
TOKEN			[x]

%%

{SIN_COMMENT} ;
{MUL_COMMENT} ;

SELECT			{ return SELECT;	}
INSERT			{ return INSERT;	}
DELETE			{ return DELETE;	}
CREATE			{ return CREATE;	}
TABLE			{ return TABLE;		}
FROM			{ return FROM;		}
WHERE			{ return WHERE;		}
AS				{ return AS;		}
INTO			{ return INTO;		}
VALUES			{ return VALUES;	}
IS				{ return IS;		}
NULL			{ return NULLX;		}
LIKE			{ return LIKE;		}
SHUTDOWN		{ return SHUTDOWN;	}
ALL				{ return ALL;		}
DISTINCT		{ return DISTINCT;	}
ASC				{ return ASC;		}
DESC			{ return DESC;		}
GROUP			{ return GROUP;		}
LIMIT			{ return LIMIT;		}
AND				{ return AND;		}
OR				{ return OR;		}
NOT				{ return NOT;		}

SET				{ return SET;		}

INT				{ return INT;	}
DOUBLE			{ return DOUBLE;	}
CHAR			{ return CHAR;}
TEXT			{ return TEXT;		}

IN				{ return IN;		}
BETWEEN			{ return BETWEEN;	}
\!\=			{ return TOK_NEQUAL;}
\>\=			{ return TOK_GE;	}
\<\=			{ return TOK_LE;	}
TRUE			{ SMADlval.val = (double) 1; return NUM; }
FALSE			{ SMADlval.val = (double) 0; return NUM; }

{TOKEN}			{ return yytext[0]; }

[\t ] ;

\"[^"]*\" {
    SMADlval.str = strdup ( yytext );

    if ( yytext [yyleng-2] == '\\' ) {
      yyless ( yyleng - 1 );
      yymore();
      break;
   }

//    bad way! no other way :)
    SMADlval.str++;
    SMADlval.str[yyleng-2] = 0;
    return LIT_STR_PARSE;
  }

\'[^']*\' {
    SMADlval.str = strdup ( yytext );

    if ( yytext [yyleng-2] == '\\' ) {
      yyless ( yyleng - 1 );
      yymore();
      break;
    }

//    bad way! no other way :)
    SMADlval.str++;
    SMADlval.str [yyleng-2] = 0;
    return LIT_STR;
  }

[A-Za-z_][A-Za-z0-9_]* {
//    yylval.str = new char [strlen(yytext)+1]; strcpy ( yylval.str , yytext );
    SMADlval.str = strdup ( yytext );
    return STRING;
  }

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
    SMADlval.val = atof ( yytext );
    return NUM;
  }

\n		{ SMADlineno++; }
. 		return yytext[0];

%%

yywrap () {return 1;}
