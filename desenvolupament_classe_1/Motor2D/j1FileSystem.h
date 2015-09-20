#ifndef __j1FileSystem_H__
#define __j1FileSystem_H__
#include "j1Module.h"
#include"SDL\include\SDL.h"
#include"SDL_mixer\include\SDL_mixer.h"
#include"SDL_image\include\SDL_image.h"
#include"PhysFS\include\physfs.h"


struct FileSystem;

class j1FileSystem : public j1Module
{
	public:

		j1FileSystem();

		bool LoadFilePHYSFS(const char* file);
		SDL_RWops* LoadFileRW(const char* file);
		SDL_Texture* LoadTexture(const char* file);
		Mix_Chunk*	LoadAudio(const char* file);

		// Destructor
		virtual ~j1FileSystem();

		// Called before render is available
		bool Awake();

		// Called before quitting
		bool CleanUp();

private:
	FileSystem* file_system;
	
};


#endif //__j1FileSystem_H__