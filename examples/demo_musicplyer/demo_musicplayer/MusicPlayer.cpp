#include "stdafx.h"
#include "MusicPlayer.h"


CMusicPlayer::CMusicPlayer()
	: m_soundEngine(nullptr)
{
	m_soundEngine = irrklang::createIrrKlangDevice();
}


CMusicPlayer::~CMusicPlayer()
{
	if (m_soundEngine)
	{
		m_soundEngine->drop();
	}
}

CMusicPlayer* CMusicPlayer::Get()
{
	static CMusicPlayer player;
	return &player;
}

bool CMusicPlayer::IsInitSuccess() const
{
	return m_soundEngine ? true : false;
}

bool CMusicPlayer::AddNewSound(const char* filename)
{
	void* data = nullptr;
	int len = 0;
	if (!LoadSoundSourceFile(filename, &data, &len))
	{
		return false;
	}
	irrklang::ISoundSource* source = m_soundEngine->addSoundSourceFromMemory(data, len, filename, false);
	if (!source)
	{
		delete[] data;
		return false;
	}
	m_playList.insert(std::pair<string, irrklang::ISoundSource*>(filename, source));
	return true;
}

bool CMusicPlayer::Play2D(const char* filename)
{
	auto iter = m_playList.find(filename);
	if (iter == m_playList.end())
	{
		return false;
	}
	m_soundEngine->play2D(iter->second);
	return true;
}

void CMusicPlayer::Stop()
{
	m_soundEngine->stopAllSounds();
}

bool CMusicPlayer::LoadSoundSourceFile(const char* sourceFile, void** data, int* len)
{
	FILE* pFile = fopen(sourceFile, "rb");
	if (!pFile)
	{
		return false;
	}
	fseek(pFile, 0, SEEK_END);
	long fileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);
	char* buf = nullptr;
	if (fileSize > 0)
	{
		*len = fileSize;
		buf = new char[fileSize];
		int readSize = fread(buf, 1, fileSize, pFile);
		if (fileSize != readSize)
		{
			delete[] buf;
			buf = nullptr;
		}
	}
	*data = buf;
	fclose(pFile);
	return true;
}

