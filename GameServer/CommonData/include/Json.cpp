#include "Json.h"
#include <assert.h>

BufferStream::BufferStream()
{
}

BufferStream::~BufferStream()
{

}

/************************************************************************/
/* Writer                                                               */
/************************************************************************/
void BufferStream::Write(std::string key, std::string value)
{
	Write(key.c_str(), value.c_str());
}


void BufferStream::Write(const char *key, const char *value)
{
	m_writer.Key(key);
	m_writer.String(value);
}

void BufferStream::WriteObjectStart()
{
	m_writer.StartObject();
}

void BufferStream::WriteObjectEnd()
{
	m_writer.EndObject();
}

void BufferStream::WriteArrayStart()
{
	m_writer.StartArray();
}

void BufferStream::WriteArrayEnd()
{
	m_writer.EndArray();
}

/************************************************************************/
/* Reader                                                               */
/************************************************************************/
unsigned int BufferStream::ReadUInt(std::string key)
{
	
	return DocumentParse(key.c_str()).GetUint();
}

int BufferStream::ReadInt(std::string key)
{
	
	return DocumentParse(key.c_str()).GetInt();
}

const char* BufferStream::ReadString(std::string key)
{
	
	return DocumentParse(key.c_str()).GetString();
}

float BufferStream::ReadFloat(std::string key)
{
	return DocumentParse(key.c_str()).GetFloat();
}

double BufferStream::ReadDouble(std::string key)
{
	return DocumentParse(key.c_str()).GetDouble();
}

rapidjson::Value& BufferStream::ReadArray(std::string key)
{
	rapidjson::Value &array = DocumentParse(key.c_str());
	return array;
}

rapidjson::Value & BufferStream::ReadObject(std::string key)
{
	rapidjson::Value& object = DocumentParse(key.c_str());
	return object;
}

/*****************************************************************************/

const char* BufferStream::GetJsonString()
{
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	m_d.Accept(writer);
	return sb.GetString();
}

void BufferStream::InitDocument(std::string JsonString)
{
	InitDocument(JsonString.c_str());
}

void BufferStream::InitDocument(const char *JsonString)
{
	m_d.Parse(JsonString);
}

void BufferStream::InitStringBuffer()
{
}


rapidjson::Value& BufferStream::DocumentParse(const char *str)
{
	return m_d[str];
}
