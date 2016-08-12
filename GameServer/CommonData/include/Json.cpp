#include "Json.h"

BufferStream::BufferStream()
	:m_writer(m_Buf)
{
	m_writer.StartObject();
}

BufferStream::~BufferStream()
{

}

void BufferStream::Write(std::string key, std::string value)
{
	Write(key.c_str(), value.c_str());
}


void BufferStream::Write(const char *key, const char *value)
{
	m_writer.Key(key);
	m_writer.String(value);
}

unsigned int BufferStream::ReadUInt(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	return DocumentParse(key.c_str()).GetUint();
}

int BufferStream::ReadInt(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	return DocumentParse(key.c_str()).GetInt();
}

const char* BufferStream::ReadString(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	return DocumentParse(key.c_str()).GetString();
}

float BufferStream::ReadFloat(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	return DocumentParse(key.c_str()).GetFloat();
}

double BufferStream::ReadDouble(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	return DocumentParse(key.c_str()).GetDouble();
}

rapidjson::Value& BufferStream::ReadArray(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	rapidjson::Value&& array = DocumentParse(key.c_str()).GetArray();
	while (array.IsArray())
	{
		array = array.GetArray();
	}
	return array[key.c_str()];
}

rapidjson::Value & BufferStream::ReadObject(std::string key)
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	rapidjson::Value&& object = DocumentParse(key.c_str()).GetObject();
	while (object.IsObject())
	{
		object = object.GetObject();
	}
	return object[key.c_str()];
}

const char* BufferStream::GetJsonString()
{
	RAPIDJSON_ASSERT(m_Buf.GetSize() > 0);
	m_writer.EndObject();
	return m_Buf.GetString();
}

void BufferStream::InitDocument(std::string JsonString)
{
	InitDocument(JsonString.c_str());
}

void BufferStream::InitDocument(const char *JsonString)
{
	m_d.Clear();
	m_d.Parse(JsonString);
}

void BufferStream::InitStringBuffer()
{
	m_Buf.Clear();
}


rapidjson::Value& BufferStream::DocumentParse(const char *str)
{
	const char* Json = GetJsonString();
	m_d.Parse(Json);
	return m_d[str];
}
