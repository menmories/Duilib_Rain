#pragma once

#include <irrKlang.h>
#include <unordered_map>
using namespace std;

#ifdef _WIN64
#pragma comment(lib, "win64/irrKlang.lib")
#else
#pragma comment(lib, "win32/irrKlang.lib")
#endif

class CMusicPlayer
{
public:
	static CMusicPlayer* Get();

	bool IsInitSuccess()const;
	
	bool AddNewSound(const char* filename);

	bool Play2D(const char* filename);

	void Stop();
private:
	bool LoadSoundSourceFile(const char* sourceFile, void** data, int* len);

	CMusicPlayer();
	~CMusicPlayer();
private:
	irrklang::ISoundEngine* m_soundEngine;
	unordered_map<string, irrklang::ISoundSource*> m_playList;
};

