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

	unsigned int ReadUInt(const char *key);
	int ReadInt(const char *key);
	const char* ReadString(const char *key);
	float ReadFloat(const char *key);
	double ReadDouble(const char *key);
	rapidjson::Value& ReadArray(const char *key);
	rapidjson::Value& ReadObject(const char *key);

	//获取json字符串
	const char* GetJsonString();
	void PrintJsonString();

	//处理异常
	bool IsJsonString();
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
	rapidjson::Value vEmpty;
	bool	WriteObjectFlag;
	bool	WriteArrayFlag;
	bool	IsDocRead;
};

#if 0
void writeTest()
{
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value root(rapidjson::kObjectType);
	root.AddMember("name", "哥伦布啊", allocator);
	root.AddMember("gold", 1234, allocator);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	root.Accept(writer);
	std::string reststring = buffer.GetString();
	std::cout << reststring << std::endl;
	getchar();
}

void test()
{
	BufferStream ss;
	ss.InitDocument("{\"project\":\"rapidjson\",\"stars\":10}");
	std::cout << ss.GetJsonString() << std::endl;
	// 	BufferStream ss;
	// 	ss.InitDocument("{\"UpdateInfo\":[{\"url\":\"aaaa.ipa\",\"platform\":\"ios\"}]}");
	// 	rapidjson::Value& v = ss.ReadArray("UpdateInfo");

	//BufferStream ss;
	//ss.WriteObjectStart();
	//ss.Write("123", "val");
	//ss.WriteObjectEnd();
	//std::cout << ss.GetJsonString() << std::endl;
	getchar();

}
#endif