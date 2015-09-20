#include"j1FileSystem.h"
#include"p2Log.h"
#include"j1App.h";
#include"PhysFS/include/physfs.h"
#include"SDL\include\SDL.h"
#include"SDL_mixer\include\SDL_mixer.h"
#include"SDL_image\include\SDL_image.h"
#include"j1Textures.h"
#include"j1Audio.h";

#pragma comment( lib, "PhysFS/libx86/physfs.lib" )

j1FileSystem::j1FileSystem() : j1Module()
{
	file_system = NULL;
}

// Destructor
j1FileSystem::~j1FileSystem()
{}


bool j1FileSystem::LoadFilePHYSFS(const char* file)
{
	bool ret = true;
	PHYSFS_File* handle = PHYSFS_openRead(file);
	unsigned int mem = PHYSFS_fileLength(handle);
	char name[256];
	if (file != NULL)
	{
		PHYSFS_fileLength(handle);
		PHYSFS_read(handle, name, mem, 1);
		PHYSFS_close(handle);

		ret = false;
	}
	else
	{
		PHYSFS_getLastError();
		ret = false;
	}

	return ret;
}

SDL_RWops* j1FileSystem::LoadFileRW(const char* file)
{
	SDL_RWops* file_to_load = SDL_RWFromFile(file, "read");
	if (file_to_load == NULL)
	{
		LOG("Failed to read the file %s\n", SDL_GetError());
	}

	return file_to_load;
}

SDL_Texture* j1FileSystem::LoadTexture(const char* file)
{
	SDL_RWops* load_file_rw = LoadFileRW(file);
	SDL_Texture* ret = NULL;
	SDL_Surface* image = IMG_Load_RW(load_file_rw, 1);

	if (!load_file_rw)
	{
		LOG("Failed to load the image %s\n", IMG_GetError());
	}
	else
	{
		ret = App->tex->LoadSurface(image);
		SDL_FreeSurface(image);
	}

	return ret;
	
}

Mix_Chunk* j1FileSystem::LoadAudio(const char* file)
{	
	Mix_Chunk* ret = NULL;
	SDL_RWops* load_file_rw = LoadFileRW(file);
	Mix_Chunk* sample = Mix_LoadWAV_RW(load_file_rw, 1);

	if (!load_file_rw)
	{
		LOG("Failed to load the sample %s\n", Mix_GetError());
	}
	else
	{
		ret = sample;
	}

	return ret;

}

bool j1FileSystem::Awake()
{
	bool ret = true;
	LOG("Init File System event system");
	PHYSFS_init(NULL);
	return ret;
}

bool j1FileSystem::CleanUp()
{
	bool ret = true;
	LOG("Quitting File System event");
	PHYSFS_deinit();
	return ret;
}
