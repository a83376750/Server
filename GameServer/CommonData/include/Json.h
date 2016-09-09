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
	BufferStream(const char* str);
	BufferStream(std::string& str);

public:
	//写入json(SAX)
	void Write(std::string key, std::string value);
	void Write(const char *key, const char *value);
	void WriteObjectStart();
	void WriteObjectEnd();
	void WriteArrayStart();
	void WriteArrayEnd();


	//读取json(DOM)
	unsigned int ReadUInt(std::string& key);
	int ReadInt(std::string& key);
	const char* ReadString(std::string& key);
	float ReadFloat(std::string& key);
	double ReadDouble(std::string& key);
	rapidjson::Value& ReadArray(std::string& key);
	rapidjson::Value& ReadObject(std::string& key);

	//获取json字符串
	const char* GetJsonString();

public:
	void InitData();
	void InitDocument(std::string& JsonString);
	void InitDocument(const char *JsonString);
private:
	rapidjson::Value&  DocumentParse(const char *str);

private:
	rapidjson::Document m_d;
private:
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
	rapidjson::StringBuffer m_sBuffer;
	rapidjson::Value v;
	bool	WriteObjectFlag;
	bool	WriteArrayFlag;
	bool	IsDocRead;
};

#ifdef DEBUG
void writeTest();
void test();
#endif