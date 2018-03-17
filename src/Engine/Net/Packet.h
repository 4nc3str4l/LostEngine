/* Copyright 2016 Guillem Pascual */

#pragma once

#include <inttypes.h>
#include <algorithm>
#include <glm/glm.hpp>
#include "asio/asio.hpp"

union f2u
{
	float f;
	uint32_t u;
};

class Packet
{

public:
	virtual ~Packet();
	
	Packet();

	Packet(uint16_t opcode)
	{
		*this << opcode;
		*this << uint16_t{ 0x0000 };
	}

	Packet(Packet* from, uint16_t size)
	{
		memcpy(this->_buffer, from->_buffer, size);
		this->_size = size;
	}

	template <typename T>
	Packet& operator<<(T v)
	{
		*reinterpret_cast<T*>(_buffer + _write) = v;
		_write += sizeof(T);
		return *this;
	}

	Packet& operator<<(float v)
	{
		*reinterpret_cast<uint32_t*>(_buffer + _write) = f2u{ v }.u;  // NOLINT(whitespace/braces)
		_write += sizeof(uint32_t);
		return *this;
	}

	Packet& operator<<(const glm::vec2& v)
	{
		*this << v.x;
		*this << v.y;
		return *this;
	}

	Packet& operator<<(const glm::vec3& v)
	{
		*this << v.x;
		*this << v.y;
		*this << v.z;
		return *this;
	}

	Packet& operator<<(Packet* packet)
	{
		uint16_t end = (uint16_t)std::max({ packet->totalRead(),   // NOLINT(whitespace/braces)
			packet->size(),
			packet->written() });  // NOLINT(whitespace/braces)

		for (uint16_t i = 4; i < end; ++i)
		{
			*this << packet->data()[i];
		}

		return *this;
	}

	template <typename T>
	T peek(uint16_t offset)
	{
		return *reinterpret_cast<T*>(_buffer + offset);
	}

	template <typename T>
	T read()
	{
		T v = peek<T>(_read);
		_read += sizeof(T);
		return v;
	}

	inline void reset() { _read = _write = _size = 0; }

	inline uint16_t size() { return _size; }
	inline uint16_t totalRead() { return _read; }
	inline uint16_t written() { return _write; }

	inline uint8_t* data() { return _buffer; }
	inline asio::mutable_buffers_1 sendBuffer()
	{
		*reinterpret_cast<uint16_t*>(_buffer + sizeof(uint16_t)) = _write - sizeof(uint16_t) * 2;
		return asio::buffer(_buffer, _write);
	}
	inline asio::mutable_buffers_1 recvBuffer(uint16_t len) { return asio::buffer(_buffer + _size, len); }
	inline void addSize(uint16_t offset) { _size += offset; }

private:
	uint16_t _read;
	uint16_t _size;
	uint16_t _write;
	uint16_t _refs;
	uint8_t _buffer[1024];
};

template <> float Packet::read();
template <> glm::vec2 Packet::read();
template <> glm::vec3 Packet::read();