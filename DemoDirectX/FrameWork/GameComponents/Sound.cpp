#include "Sound.h"
//include "GameLog.h"
#include "GameGlobal.h"

Sound* Sound::instance = nullptr;

Sound* Sound:: getInstance()
{
	if (instance == nullptr)
		instance = new Sound(GameGlobal::getCurrentHWND());

	return instance;
}

Sound::Sound(HWND hWnd)
{
	primaryBuffer = 0;
	HRESULT result;

	DSBUFFERDESC bufferDesc; 

	result = DirectSoundCreate8(NULL, &pDevice, NULL);


	result = pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); 

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = pDevice -> CreateSoundBuffer(&bufferDesc, &primaryBuffer, NULL);

	/*if(FAILED(result))
	{
		GAMELOG("Can not create primaryBuffer");
	}*/
	volume = 75.0f;
	isMute = false;


	//Aladdin Sound
	loadSound("Resources/Sound/Aladdin Hurt.wav", "AladdinHurt");       //mất máu
	loadSound("Resources/Sound/Aladdin Cut.wav", "AladdinCut");			//Chém trên
	setVolume(90, "AladdinCut");										
	loadSound("Resources/Sound/Aladdin Cut.wav", "AladdinCutDown");		//chém dưới
	loadSound("Resources/Sound/Aladdin Die.wav", "AladdinDie");			//chết
	loadSound("Resources/Sound/Coming Out.wav", "Revive");				//hồi sinh từ bình
	loadSound("Resources/Sound/Object Throw.wav", "ThrowApple");		//ném táo
	loadSound("Resources/Sound/Aladdin Oof.wav", "AladdinLanding");		//Tiếp đất
	loadSound("Resources/Sound/Wow!.wav", "Wow!");						//Ăn 1 số vật phẩm như GenieBonus ,1Up.
	loadSound("Resources/Sound/Apple Splat.wav", "AppleSplat");			//táo vỡ
	loadSound("Resources/Sound/Body Crunch.wav", "BodyCrunch");			//chưa rõ

	//Game Object sounds
	loadSound("Resources/Sound/Flagpole.wav", "Flagpole");				//Springboard
	loadSound("Resources/Sound/Camel Spit.wav", "CamelSpit");			//lạc đà
	loadSound("Resources/Sound/Fire From Coal.wav", "FireFromCoal");

	// Items sounds
	loadSound("Resources/Sound/Extra Health.wav", "ExtraHealth");
	loadSound("Resources/Sound/Apple Collect.wav", "AppleCollect");
	loadSound("Resources/Sound/Continue Point.wav", "ContinuePoint");
	loadSound("Resources/Sound/Gem Collect.wav", "GemCollect");
	loadSound("Resources/Sound/Peddler Shop.wav", "PelderShop");


	//Enemies sound
	loadSound("Resources/Sound/Guard Hit 1.wav", "GuardHit1");
	loadSound("Resources/Sound/Guard's Pants.wav", "GuardPants");
	loadSound("Resources/Sound/Balloon Pop.wav", "BalloonPop");
	loadSound("Resources/Sound/Sword Spinning.wav", "SwordSpinning");
	loadSound("Resources/Sound/Jafar Snake.wav", "JafarSnake");

	//Scene sounds
	loadSound("Resources/Sound/Scene1.wav", "Scene1");				//Scene 1
	setVolume(95, "Scene1");

	loadSound("Resources/Sound/BossTune.wav", "BossTune");		//Scene Final
	setVolume(95, "BossTune");

	loadSound("Resources/Sound/BeginSceneSound.wav", "BeginSceneSound");		//Begin Scene Sound
	setVolume(95, "BeginSceneSound");

	loadSound("Resources/Sound/LevelComplete.wav", "LevelComplete");		//Level Complete
	setVolume(100, "LevelComplete");

	loadSound("Resources/Sound/GameOver.wav", "GameOver");		//GameOver
	setVolume(95, "GameOver");
	
	//Intro sounds

	loadSound("Resources/Sound/IntroSound1.wav", "Intro1");			//thần đèn bắn súng rụng chim=)).
	setVolume(95, "Intro1");

	loadSound("Resources/Sound/IntroSound2.wav", "Intro2");			//menu start;
	setVolume(95, "Intro2");

	loadSound("Resources/Sound/IntroSound3.wav", "Intro3");			//chữ giới thiệu.
	setVolume(95, "Intro3");

	//Weapon sounds;
	loadSound("Resources/Sound/Sword Ching.wav", "Sword Ching");			//chữ giới thiệu.
	setVolume(95, "Sword Ching");
}

Sound::~Sound()
{
	for (auto it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
	{
		if(it -> second)
		{
			it -> second -> Release();
			it -> second = NULL;
		}
		
	}
	if(primaryBuffer)
		primaryBuffer ->Release();
	if(pDevice)
		pDevice -> Release();
	pDevice = NULL;
	
	primaryBuffer = NULL;

	
}

void Sound :: create(HWND hWnd)
{
	if(instance == nullptr)
	{
		instance = new Sound(hWnd);
	}

}

float Sound :: getVolume()
{
	return volume;
}

void Sound :: loadSound(char* fileName, std:: string name)
{
	if(soundBufferMap.find(name) != soundBufferMap.end())
		return;
	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	/*if(error != 0)
	{
		GAMELOG(" Can not load: %s", fileName);
		return ;
	}*/

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);
	//fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);

	/*if((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
	   (waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
	{
		GAMELOG(" file format does not support: %s", fileName);
	}*/

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;
	//IDirectSoundBuffer8

	//long result = pDevice->CreateSoundBuffer(&bufferDesc, &secondaryBuffer, NULL);

	pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;

	/*if(FAILED(result))
	{
		GAMELOG(" Can not create secondaryBuffer ");
		return;
	}*/

	//fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET); // move the filePointer cursor to data section

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);


	wavData = new unsigned char[ waveHeaderStruct.dataSize];

	

	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	/*if(error != 0)
	{
		GAMELOG(" Can not close file ");
	}
*/
	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if(FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if(wavData != NULL)
	delete wavData;
	wavData = 0;
	long tempVolume = (volume) / 100 *(- DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer) -> SetVolume(tempVolume);

	soundBufferMap[name] = secondaryBuffer;


}

void Sound :: play(std:: string name, bool infiniteLoop, int times)
{
	if(isMute||isPlaying(name)==true)
	{
		return;
	}
	std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
	it = soundBufferMap.find(name);
	if(it == soundBufferMap.end())
		return;
	if(infiniteLoop)
	{
		it -> second -> Play(0, 0 , DSBPLAY_LOOPING);
	}
	else
	{
		it -> second -> Stop();
		it -> second -> SetCurrentPosition(0);
		it -> second -> Play(0, 0, times - 1);
	}

}

void Sound :: stop(std::string name)
{
	if(name == "")
	{
		for ( std::map< std::string, IDirectSoundBuffer8*> ::iterator it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it -> second ->Stop();
			it -> second ->SetCurrentPosition(0);
		}
	}
	else
	{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if(it == soundBufferMap.end())
			return;
		else it -> second ->Stop();
	}
}

bool Sound::isPlaying(std::string name)
{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if (it == soundBufferMap.end())
			return false;
		else
		{
			DWORD result;
			it->second->GetStatus(&result);
			if (result == DSBSTATUS_PLAYING)
				return true;
			else return false;
		}

}

void Sound :: setVolume(float percentage, std:: string name)
{
	volume = percentage;
	if(name == "")
	{
		long volumne = (percentage) / 100 *(- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for ( std::map< std::string, IDirectSoundBuffer8*> ::iterator it = soundBufferMap.begin(); it != soundBufferMap.end(); it++)
		{
			it -> second ->SetVolume(volumne);
		}
	}
	else
	{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = soundBufferMap.find(name);
		if(it == soundBufferMap.end())
			return;
		long volumne = (percentage) / 100 *(- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it -> second ->SetVolume(volumne);
	}
}

void Sound :: mute()
{
	isMute = true;
	Sound::getInstance() -> stop();
}

void Sound :: unMute()
{
	isMute = false;
}

void Sound :: cleanUp()
{
	delete this;
}
