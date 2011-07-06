#ifndef __SMAD_FILER_H
#define __SMAD_FILER_H


// defines for the origin argument seek function

#define SMAD_POS_BEG	SEEK_SET
#define SMAD_POS_CUR	SEEK_CUR
#define SMAD_POS_END	SEEK_END


//defines for open and protection modes
// can be changed according to the filing backend used

#define SMAD_O_RDWR			_O_RDWR
#define SMAD_O_RDONLY		_O_RDONLY
#define SMAD_O_WRONLY		_O_WRONLY
#define SMAD_O_APPEND		_O_APPEND
#define SMAD_O_BINARY		_O_BINARY
#define SMAD_O_CREATE		_O_CREAT
#define SMAD_O_TEMPORARY    _O_TEMPORARY
#define SMAD_O_SHORT_LIVED  _O_SHORT_LIVED
#define SMAD_O_EXCL			_O_EXCL
#define SMAD_O_RANDOM		_O_RANDOM
#define SMAD_O_SEQUENTIAL	_O_SEQUENTIAL
#define SMAD_O_TEXT			_O_TEXT
#define SMAD_O_TRUNCATE		_O_TRUNC
#define SMAD_S_IREAD		_S_IREAD
#define SMAD_S_IWRITE		_S_IWRITE
#define SMAD_S_RDWR			_S_IREAD|_S_IWRITE

class SMADFiler{
	int handle;
	bool is_open;


public:
	SMADFiler&    operator=	(const SMADFiler&);
	SMADFiler	(const SMADFiler&);
	SMADFiler   (const char*, int);
	SMADFiler   (const char*, int, int);
    SMADFiler   ():is_open(false){};
	~SMADFiler();

	int		write		(const char*, unsigned int);
	int		read		(char*,unsigned int);
	int     append      (const char*, unsigned int);
	int		open		(const char*, int);
	int		open		(const char*, int, int);
	int		close		();
//	int		create		(const char*, int);
	long	setpos		(long, int);
	long	getpos		();
	int		commit		();
	int		gethandle	();
	int		peekbyte	();
    int		eof			();
	bool    isopen      ();
	int     getbyte     ();
	int     putbyte     (int byte);
	
	

};

typedef SMADFiler smadfiler;

#endif
