#include "TextManager.h"

#include <iostream>

TextManager* TextManager::instance_ = 0;

TextManager* TextManager::Instance()
{
	if (instance_ == 0)
	{
		instance_ = new TextManager();
	}

	return instance_;
}

TextManager::TextManager()
{
}

TextManager::~TextManager()
{
}

void TextManager::Init()
{
	defaultFont_ = new FTGLPixmapFont("FreeMono.ttf");

	if (defaultFont_->Error())
	{
		std::cerr << "FTGL font unable to load!" << std::endl;
		throw;
	}

	defaultFont_->FaceSize(40);

	font_ = defaultFont_;
}

void TextManager::Render(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(pBuffer_, 1000, fmt, ap);
	va_end(ap);

	font_->Render(pBuffer_);
}

void TextManager::Render(std::string message)
{
	font_->Render(message.c_str());
}

void TextManager::UseFont(std::string label, int size)
{
	FontContainerType::const_iterator it;
	it = fonts_.find(label);
	if (it != fonts_.end())
	{
		font_ = fonts_[label];
	}
	else
	{
		std::cout << "Requested font not found. Using default instead." << std::endl;
		fonts_[label] = defaultFont_;
		font_ = defaultFont_;
	}
	font_->FaceSize(size);
}

void TextManager::AddFont(std::string label, std::string path)
{
	font_ = new FTGLPixmapFont(path.c_str());
	if (font_->Error())
	{
		std::cerr << "Unable to add given font!" << std::endl;
		throw;
	}
	
	fonts_[label] = font_;
}
