#pragma once

template <typename T>
class singletonBase
{
protected:
	static T* singleton; //½Ì±ÛÅæ ÀÎ½ºÅÏ½º ¼±¾ð

	singletonBase(){};
	~singletonBase(){};

public:
	static T* getSingleton();
	void releaseSingleton();

};

//½Ì±ÛÅæ ÃÊ±âÈ­
template<typename T>
T* singletonBase<T>::singleton = NULL;

//½Ì±ÛÅæ °ª °¡Á®¿Â´Ù
template<typename T>
T* singletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;
	return singleton;
}

//½Ì±ÛÅæ ¸Þ¸ð¸® ÇØÁ¦
template<typename T>
void singletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = NULL;
	}
}
