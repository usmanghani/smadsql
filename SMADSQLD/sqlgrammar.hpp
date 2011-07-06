#ifndef BISON_SQLGRAMMAR_HPP
# define BISON_SQLGRAMMAR_HPP

#ifndef YYSTYPE
typedef union {
	double					val;
	char				*	str;
	Table				*	tableptr;
	Column				*	colptr;
	Function			*	funcptr;
	TreeExpr			*	exprtree;
	SQLassign			*	assignexpr;
	SQLexpr				*	searchexpr;
	SQLsearch			*	searchptr;
	SQLnewfield			*	fielddef;
	SQLList<Column>		*	fieldlist;
	SQLList<Table*>		*	tablelist;
	SQLList<SQLsearch>	*	searchlist;
	SQLList<TreeExpr*>	*	exprlist;
	SQLList<SQLassign*>	*	assignlist;
	SQLList<SQLnewfield*>*	tabledef;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	NUM	257
# define	STRING	258
# define	FUNC	259
# define	LIT_STR	260
# define	LIT_STR_PARSE	261
# define	SELECT	262
# define	INSERT	263
# define	UPDATE	264
# define	DELETE	265
# define	CREATE	266
# define	TABLE	267
# define	AND	268
# define	NOT	269
# define	OR	270
# define	FROM	271
# define	WHERE	272
# define	INTO	273
# define	VALUES	274
# define	SET	275
# define	ORDER	276
# define	BY	277
# define	AS	278
# define	IN	279
# define	NULLX	280
# define	LIKE	281
# define	IS	282
# define	SHUTDOWN	283
# define	ALL	284
# define	DISTINCT	285
# define	INT	286
# define	DOUBLE	287
# define	CHAR	288
# define	TEXT	289
# define	ASC	290
# define	DESC	291
# define	GROUP	292
# define	LIMIT	293
# define	BETWEEN	294
# define	TOK_NEQUAL	295
# define	TOK_GE	296
# define	TOK_LE	297
# define	TOK_EXIT	298
# define	NEG	299
# define	UMINUS	300


extern YYSTYPE SMADlval;

#endif /* not BISON_SQLGRAMMAR_HPP */
