#include "packedfile.h"
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <string>

//#define TMPDIR
#define PACKED 0
#define RESDIR "res/"

struct Myfile
{
	FILE* f;
	Sint64 len;
	Sint64 base;
	Sint64 here;
};
//TODO: 这些函数还要写
static Sint64 myseekfunc(SDL_RWops *context, Sint64 offset, int whence)
{
  return SDL_SetError("Can't seek in this kind of SDL_RWops");
}

static size_t myreadfunc(SDL_RWops *context, void *ptr, size_t size, size_t maxnum)
{
  SDL_memset(ptr,0,size*maxnum);
  return maxnum;
}

static size_t mywritefunc(SDL_RWops *context, const void *ptr, size_t size, size_t num)
{

	return num;
}

static int myclosefunc(SDL_RWops *context)
{
	if(context->type != 0xfaccbfef)
	{
		return SDL_SetError("Wrong kind of SDL_RWops for myclosefunc()");
	}
#if PACKED
	return SDL_SetError("Not support now. ")
#else
#endif
	Myfile *file = (Myfile*)context->hidden.unknown.data1;
	delete file;
	SDL_FreeRW(context);
	return 0;
}

Sint64 getFileSize(const char* fn)
{
	Sint64 len;
	FILE* f = fopen(fn, "r");
	fseek(f,0,SEEK_END);
	len=ftell(f);
	fclose(f);
	return len;
}

//need to be released
SDL_RWops* pfOpenSDL_RWops(const char* fn)
{
	SDL_RWops *c=SDL_AllocRW();
	if(c==NULL) return NULL;
	c->seek  = myseekfunc;
	c->read  = myreadfunc;
	c->write = mywritefunc;
	c->close = myclosefunc;
	c->type  = 0xfaccbfef;
#if PACKED
	return SDL_SetError("Not support now. ")
#else
	char mPath[256] = {0};
	strcat(mPath, RESDIR);
	strcat(mPath, fn);
	Myfile* file = new Myfile();
	file->f = fopen(mPath, "rb");
	file->base = 0;
	file->len = getFileSize(mPath);
	file->here = 0;
	c->hidden.unknown.data1=&file; //FILE*
#endif
	return c;
}

std::string pfGetString(const char* fn)
{
#if PACKED
	SDL_SetError("Not support now. ")
	return "";
#else
	std::string tstr;
	char mPath[256] = {0};
	strcat(mPath, RESDIR);
	strcat(mPath, fn);
	FILE *f  = fopen(mPath, "rb");
	Sint64 nLen = getFileSize(mPath);
	char* buffer = (char*) malloc(nLen+1);
	buffer[nLen]=0;
	if(!buffer) {    
		SDL_SetError("out of memory!");
		return "";
	}
	fread(buffer, 1, nLen, f);
	tstr = buffer;
	free(buffer);
	fclose(f);
	return tstr;
#endif
}

