#pragma once

#include <cstdint>
#include <cassert>
#include <array>
#include <cstring>
#include <iostream>

namespace nob {
	namespace ntv {
		// Reference from https://github.com/zorg93/EnableMpCars-GTAV

		class global_table_t {
			public:
				global_table_t();

				uint64_t &operator[](uint32_t hash) {
					assert(*this);

					return _base_addr[hash >> 18 & 0x3F][hash & 0x3FFFF];
				}

				uint64_t operator[](uint32_t hash) const {
					return (*const_cast<global_table_t *>(this))[hash];
				}

				operator bool() const {
					return _base_addr && *_base_addr;
				}

			private:
				uint64_t **_base_addr;
		};

		struct script_t {
			char padding1[16];					//0x0
			uint8_t **blocks_offset;			//0x10
			char padding2[4];					//0x18
			uint32_t length;					//0x1C
			char padding3[4];					//0x20
			uint32_t local_count;				//0x24
			char padding4[4];					//0x28
			uint32_t native_count;				//0x2C
			int64_t *local_offset;				//0x30
			char padding5[8];					//0x38
			int64_t *native_offset;				//0x40
			char padding6[16];					//0x48
			uint32_t name_hash;					//0x58
			char padding7[4];					//0x5C
			char *name;							//0x60
			char **strings_offset;				//0x68
			uint32_t string_size;				//0x70
			char padding8[12];					//0x74

			bool is_valid() const {
				return length;
			}

			size_t page_count() const {
				return (length + 0x3FFF) >> 14;
			}

			size_t page_size(size_t page) const {
				return page >= page_count() ? 0 : (page == page_count() - 1) ? length & 0x3FFF : 0x4000;
			}

			uint8_t *page_addr(size_t page) const {
				return blocks_offset[page];
			}

			uint8_t *pos_addr(size_t pos) const {
				return pos >= length ? NULL : &blocks_offset[pos >> 14][pos & 0x3FFF];
			}

			char *get_string(size_t str_pos) const {
				return str_pos >= string_size ? NULL : &strings_offset[str_pos >> 14][str_pos & 0x3FFF];
			}
		};

		struct script_list_t {
			struct node_t {
				script_t *script;
				int _unk;
				uint32_t hash;
			};

			node_t *nodes;
			uint8_t _unk[16];
			uint32_t size;

			node_t *find(const char *name) const;
		};

		////////////////////////////////////////////////////////////////////////////

		template <typename T>
		inline uintptr_t argument_cast(T v) {
			static_assert(sizeof(T) == 8, "nob::ntv::argument_cast: origin type size mismatch!");

			return *reinterpret_cast<uintptr_t *>(&v);
		}

		template <>
		inline uintptr_t argument_cast<int32_t>(int32_t v) {
			return static_cast<uintptr_t>(v);
		}

		template <>
		inline uintptr_t argument_cast<uint32_t>(uint32_t v) {
			return static_cast<uintptr_t>(v);
		}

		template <>
		inline uintptr_t argument_cast<float>(float v) {
			return static_cast<uintptr_t>(*reinterpret_cast<uint32_t *>(&v));
		}

		template <>
		inline uintptr_t argument_cast<bool>(bool v) {
			return static_cast<uintptr_t>(*reinterpret_cast<uint8_t *>(&v));
		}

		////////////////////////////////////////////////////////////////////////////

		// Reference from https://github.com/ivanmeler/OpenVHook

		struct call_context_t {
			uintptr_t *result_ptr;
			uint32_t args_length;
			uintptr_t *args_ptr;
			uint32_t result_size;

			////////////////////////////////////////////////////////////////////////

			call_context_t() {}

			call_context_t(uintptr_t *stack_ptr) :
				result_ptr(stack_ptr + 20),
				args_ptr(stack_ptr)
			{}

			template <typename T>
			void set_arg(size_t i, T v) {
				args_ptr[i] = argument_cast<T>(v);
			}

			template <typename T>
			T arg(size_t i) const {
				return *reinterpret_cast<T *>(&args_ptr[i]);
			}

			template<size_t>
			void _set_args() {}

			template<size_t i, typename A, typename ...O>
			void _set_args(A a, O ...o) {
				set_arg<A>(i, a);
				_set_args<i + 1, O...>(o...);
			}

			template<typename ...A>
			void set_args(A ...a) {
				args_length = sizeof...(A);
				_set_args<0, A...>(a...);
			}

			template <typename T>
			void set_result(T v) {
				*reinterpret_cast<T *>(result_ptr) = v;
			}

			template <typename T>
			T result() const {
				return *reinterpret_cast<T *>(result_ptr);
			}

			void print(const std::string &mark = nullptr) {
				if (!mark.empty()) {
					std::cout << mark << std::endl;
				}

				std::cout
				<< "args_ptr: " << args_ptr << std::endl
				<< "args_length: " << args_length << std::endl
				<< "result_ptr: " << result_ptr << std::endl
				<< "result_size: " << result_size << std::endl
				<< std::endl;
			}
		};

		template <>
		inline void call_context_t::result<void>() const {}

		typedef void (__cdecl *func_t)(call_context_t &);

		static func_t nullfunc = nullptr;

		class func_table_t {
			public:
				struct node_t {
					node_t *next_node;
					func_t funcs[7];
					uint32_t length;
					uint64_t hashes[7];
				};

				func_table_t();

				func_t &operator[](uint64_t hash) {
					if (!_nodes) {
						return nullfunc;
					}
					for (auto n = _nodes[hash & 0xFF]; n; n = n->next_node) {
						for (uint8_t i = 0; i < n->length; ++i) {
							if (n->hashes[i] == hash) {
								return n->funcs[i];
							}
						}
					}
					return nullfunc;
				}

				func_t operator[](uint64_t hash) const {
					return (*const_cast<func_table_t *>(this))[hash];
				}

				operator bool() const {
					return _nodes;
				}

			private:
				node_t **_nodes;
		};
	} /* ntv */
} /* nob */
