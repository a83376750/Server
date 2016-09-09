#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <functional>

#include "../ThirdLibrary/rapidjson/allocators.h"
#include "../ThirdLibrary/rapidjson/writer.h"
#include "../ThirdLibrary/rapidjson/stringbuffer.h"
#include "../ThirdLibrary/rapidjson/document.h"
#include "../ThirdLibrary/rapidjson/prettywriter.h"
#include "../ThirdLibrary/rapidjson/error/en.h"
#include "../ThirdLibrary/rapidjson/schema.h"

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
	void Write(const char *key, int value);
	void Write(const char *key, unsigned int value);
	void Write(const char *key, double value);
	//写入一个NULL值
	void Write(const char *key);

	template<class ... Types>
	void WriteArray(const char *key, Types ... args)
	{
		//va_list ap;
		//va_start(ap, count);
		//for(int i = 0; i < count; ++i)
		//{
		//	va_arg(ap, int);
		//}
		//va_end(ap);

		m_writer.StartArray();
		int nCount = sizeof...(args);
		auto t1 = std::make_tuple(args...);/*
		std::cout << std::get<0>(t1) << " ";
		std::cout << std::get<1>(t1) << " ";
		std::cout << std::get<2>(t1) << " ";
		std::cout << std::get<3>(t1) << " ";
		std::cout << std::endl;*/
		//for (size_t i = 0; i < nCount; ++i)
		//{
		//	std::cout << std::get<i>(t1) << std::endl;
		//}
		std::cout << "变长参数个数:" << sizeof...(args) << std::endl;
		m_writer.EndArray();
	}

	void WriteObjectStart();
	void WriteObjectEnd();
	void WriteArrayStart();
	void WriteArrayEnd();


	//读取json(DOM)
	bool ReadUInt(const char *key, unsigned int &value);
	bool ReadInt(const char *key, int &value);
	bool ReadString(const char *key, char *value);
	bool ReadFloat(const char *key, float &value);
	bool ReadDouble(const char *key, double &value);
	bool ReadArray(const char *key, rapidjson::Value &value);
	bool ReadObject(const char *key, rapidjson::Value &value);


	//获取json字符串
	const char* GetJsonString();
	void PrintJsonString();

	//处理异常
	bool IsJsonString(void *buffer);
public:
	void InitData();
	bool InitDocument(std::string& JsonString);
	bool InitDocument(const char *JsonString);
private:
	rapidjson::Value&  DocumentParse(const char *str);

private:
	rapidjson::Document m_d;
private:
	rapidjson::Writer<rapidjson::StringBuffer> m_writer;
	rapidjson::StringBuffer m_sBuffer;
	rapidjson::Value vEmpty;
	bool	WriteObjectFlag;
	bool	WriteArrayFlag;
	bool	IsDocRead;
};

#ifdef DEBUG
void writeTest();
void test();
#endif