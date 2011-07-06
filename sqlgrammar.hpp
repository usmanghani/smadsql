#ifndef BISON_SQLGRAMMAR_HPP
# define BISON_SQLGRAMMAR_HPP

#ifndef YYSTYPE
typedef union {
	char*					str;
  double 				val;
	SQLvar				ret;		// multiple-type return value
	SQLarray*			array;	// array of elements
	bool					bool;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	NUM	257
# define	STRING	258
# define	FUNC	259
# define	LIT_STR	260
# define	LIT_STR_PARSE	261
# define	POW	262
# define	TOK_EXIT	263
# define	SELECT	264
# define	INSERT	265
# define	UPDATE	266
# define	DELETE	267
# define	FROM	268
# define	WHERE	269
# define	INTO	270
# define	LESS_NEG	271
# define	NEG	272


extern YYSTYPE SMADlval;

#endif /* not BISON_SQLGRAMMAR_HPP */
