#pragma once

#include <iostream>
#include <string>

#include "../ThirdLibrary/rapidjson/allocators.h"
#include "../ThirdLibrary/rapidjson/writer.h"
#include "../ThirdLibrary/rapidjson/stringbuffer.h"
#include "../ThirdLibrary/rapidjson/document.h"
#include "../ThirdLibrary/rapidjson/prettywriter.h"

class BufferStream
{
public:
	BufferStream();
	~BufferStream();
public:
	//写入json
	void Write(std::string key, std::string value);
	void Write(const char *key, const char *value);
	void WriteObjectStart();
	void WriteObjectEnd();
	void WriteArrayStart();
	void WriteArrayEnd();

	//读取json
	unsigned int ReadUInt(std::string key);
	int ReadInt(std::string key);
	const char* ReadString(std::string key);
	float ReadFloat(std::string key);
	double ReadDouble(std::string key);
	rapidjson::Value& ReadArray(std::string key);
	rapidjson::Value& ReadObject(std::string key);

	//获取json字符串
	const char* GetJsonString();

public:
	void InitDocument(std::string JsonString);
	void InitDocument(const char *JsonString);
	void InitStringBuffer();
private:
	rapidjson::Value&  DocumentParse(const char *str);

private:
	rapidjson::Document m_d;
private:
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
	rapidjson::Value v;
};
