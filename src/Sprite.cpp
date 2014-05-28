#include "Sprite.h"
#include "Window.h"
#include "Logger.h"
#include <cassert>

Sprite::Sprite(const std::string& path_) :
	sdlTexture(nullptr),
	width(0),
	height(0),
	path(path_),
	flipHorizontal(false)
{
	loadFrom(this->path);
}

Sprite::Sprite(SDL_Surface* const surface_) :
	sdlTexture(surfaceToTexture(surface_)),
	width(0),
	height(0),
	path("font"),
	flipHorizontal(false)
{
	// Display error log if image wasn't loaded.
	if(this->sdlTexture == nullptr){
		Logger::error("Sprite load failed: " + this->path);
	}
}

Sprite::~Sprite(){
	if(this->sdlTexture != nullptr){
		SDL_DestroyTexture(this->sdlTexture);
		this->sdlTexture = nullptr;
	}
}

void Sprite::loadFrom(const std::string& path_){
	assert(Window::getRenderer() != nullptr && "Window renderer should not be null!");


	SDL_Surface* loadedSurface = IMG_Load(path_.c_str());

	// Returns whether the Sprites texture is null or not.
	this->sdlTexture = surfaceToTexture(loadedSurface);

	// Display error log if image wasn't loaded.
	if(this->sdlTexture == nullptr){
		Logger::error("Sprite load failed: " + path_);
	}
}

void Sprite::render(const double x_, const double y_, SDL_Rect* const clip_,
	const bool stretch_, const double angle_, SDL_Point* const center_,
	SDL_RendererFlip flip_){

	// This is the destination SDL_Rect structure.
	SDL_Rect renderQuad = {(int)x_, (int)y_, (int)this->width, (int)this->height};

	if(clip_ != nullptr){
		renderQuad.w = clip_->w;
		renderQuad.h = clip_->h;
	}
	else{

	}

	if(flipHorizontal){
		flip_ = SDL_FLIP_HORIZONTAL;
	}
	else{
		flip_ = SDL_FLIP_NONE;
	}

	int logicalw = 0;
	int logicalh = 0;
	Window::getLogicalSize(&logicalw, &logicalh);
	SDL_Rect stretch = {(int)x_,(int)y_,logicalw,logicalh};

	int successfullRender = (!stretch_) ?
		SDL_RenderCopyEx(Window::getRenderer(), this->sdlTexture, clip_,
			&renderQuad, angle_, center_, flip_) :
		SDL_RenderCopyEx(Window::getRenderer(), this->sdlTexture, clip_,
			&stretch, angle_, center_, flip_);
	
	if(successfullRender != 0){
		Logger::errorSDL("Failed to render sprite.", SDL_GetError());
	}
}

unsigned int Sprite::getWidth(){
	return this->width;
}

unsigned int Sprite::getHeight(){
	return this->height;
}

void Sprite::setWidth(unsigned int width_){
	this->width = width_;
}

void Sprite::setHeight(unsigned int height_){
	this->height = height_;
}
void Sprite::setHorizontalFlip(bool isRight_){
	if(isRight_){
		this->flipHorizontal = false;
	}
	else{
		this->flipHorizontal = true;
	}
}

SDL_Texture* Sprite::surfaceToTexture(SDL_Surface* const surface_){
	// The final texture.
	SDL_Texture* newTexture = nullptr;

	if(surface_ != nullptr){
		// Create texture from the surface pixels.
        newTexture = SDL_CreateTextureFromSurface(Window::getRenderer(), surface_);
		if(newTexture != nullptr){
			// Set the Sprites width and height, from the loaded surface.
			this->width = surface_->w;
			this->height = surface_->h;
		}
		else{
			Logger::errorSDL("Could not create texture from surface.", SDL_GetError());
		}

		// Free the loaded surface.
		SDL_FreeSurface(surface_);
	}
	else{
		Logger::errorSDL("Could not load surface from path.", IMG_GetError());
	}

	return newTexture;
}

std::string Sprite::getPath(){
	return this->path;
}
