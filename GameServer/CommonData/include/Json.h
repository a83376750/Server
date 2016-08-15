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
	//Ð´Èëjson(SAX)
	void Write(std::string key, std::string value);
	void Write(const char *key, const char *value);
	void WriteObjectStart();
	void WriteObjectEnd();
	void WriteArrayStart();
	void WriteArrayEnd();


	//¶ÁÈ¡json(DOM)
	unsigned int ReadUInt(std::string& key);
	int ReadInt(std::string& key);
	const char* ReadString(std::string& key);
	float ReadFloat(std::string& key);
	double ReadDouble(std::string& key);
	rapidjson::Value& ReadArray(std::string& key);
	rapidjson::Value& ReadObject(std::string& key);

	//»ñÈ¡json×Ö·û´®
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

#if 0
void writeTest()
{
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value root(rapidjson::kObjectType);
	root.AddMember("name", "¸çÂ×²¼°¡", allocator);
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