#pragma once

#include "pch.h"

template<typename T>
class Singleton
{
protected:

	static std::string mName;
	static std::shared_ptr<T> mInstance;

	Singleton()
	{
	}

public:
	Singleton(Singleton& other) = delete;
	void operator=(const Singleton&) = delete;

	static std::shared_ptr<T> GetInstance()
	{
		if (!mInstance)
		{
			mInstance = std::shared_ptr<T>(new T());
		}

		return mInstance;
	}

	std::string name() const
	{
		return mName;
	}

};

template <typename T>
std::shared_ptr<T> Singleton<T>::mInstance{ nullptr };

template <typename T>
std::string Singleton<T>::mName;


