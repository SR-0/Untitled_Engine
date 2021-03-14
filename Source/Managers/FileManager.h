#pragma once
#include <fstream>
#include <cctype>
#include <iostream>
#include <string>





class FileManager
{
public:

	FileManager() = default;

public:

	static void Update();

public:

	static void Save(const char* file);
	static void Load(const char* file);

public:

	static std::ofstream OutFile;
	static std::ifstream InFile;

};

