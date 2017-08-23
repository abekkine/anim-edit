#ifndef TEXT_MANAGER_H_
#define TEXT_MANAGER_H_

#include <stdio.h>
#include <stdarg.h>

#include <FTGL/ftgl.h>

#include <map>
#include <string>

class TextManager
{
private:
	FTGLPixmapFont* font_;
	FTGLPixmapFont* defaultFont_;
	typedef std::map<std::string, FTGLPixmapFont*> FontContainerType;
	FontContainerType fonts_;
	char pBuffer_[1024];

public:
	TextManager();
	~TextManager();
	void Init();
	void Render(const char* fmt, ...);
	void Render(std::string message);
	void UseFont(std::string label, int size);
	void AddFont(std::string label, std::string path);
};

#endif  // TEXT_MANAGER_H_


