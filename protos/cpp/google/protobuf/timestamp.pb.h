/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/timestamp.proto

#ifndef PROTOBUF_INCLUDED_google_2fprotobuf_2ftimestamp_2eproto
#define PROTOBUF_INCLUDED_google_2fprotobuf_2ftimestamp_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3007000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2ftimestamp_2eproto

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2ftimestamp_2eproto {
  static const ::google::protobuf::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors_google_2fprotobuf_2ftimestamp_2eproto();
namespace google {
namespace protobuf {
class Timestamp;
class TimestampDefaultTypeInternal;
extern TimestampDefaultTypeInternal _Timestamp_default_instance_;
template<> ::google::protobuf::Timestamp* Arena::CreateMaybeMessage<::google::protobuf::Timestamp>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace google {
namespace protobuf {

// ===================================================================

class Timestamp final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:google.protobuf.Timestamp) */ {
 public:
  Timestamp();
  virtual ~Timestamp();

  Timestamp(const Timestamp& from);

  inline Timestamp& operator=(const Timestamp& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Timestamp(Timestamp&& from) noexcept
    : Timestamp() {
    *this = ::std::move(from);
  }

  inline Timestamp& operator=(Timestamp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline ::google::protobuf::Arena* GetArena() const final {
    return GetArenaNoVirtual();
  }
  inline void* GetMaybeArenaPointer() const final {
    return MaybeArenaPtr();
  }
  static const ::google::protobuf::Descriptor* descriptor() {
    return default_instance().GetDescriptor();
  }
  static const Timestamp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Timestamp* internal_default_instance() {
    return reinterpret_cast<const Timestamp*>(
               &_Timestamp_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void UnsafeArenaSwap(Timestamp* other);
  void Swap(Timestamp* other);
  friend void swap(Timestamp& a, Timestamp& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Timestamp* New() const final {
    return CreateMaybeMessage<Timestamp>(nullptr);
  }

  Timestamp* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Timestamp>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Timestamp& from);
  void MergeFrom(const Timestamp& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  static const char* _InternalParse(const char* begin, const char* end, void* object, ::google::protobuf::internal::ParseContext* ctx);
  ::google::protobuf::internal::ParseFunc _ParseFunc() const final { return _InternalParse; }
  #else
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Timestamp* other);
  protected:
  explicit Timestamp(::google::protobuf::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::google::protobuf::Arena* arena);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int64 seconds = 1;
  void clear_seconds();
  static const int kSecondsFieldNumber = 1;
  ::google::protobuf::int64 seconds() const;
  void set_seconds(::google::protobuf::int64 value);

  // int32 nanos = 2;
  void clear_nanos();
  static const int kNanosFieldNumber = 2;
  ::google::protobuf::int32 nanos() const;
  void set_nanos(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:google.protobuf.Timestamp)
 private:
  class HasBitSetters;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  template <typename T> friend class ::google::protobuf::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::google::protobuf::int64 seconds_;
  ::google::protobuf::int32 nanos_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_google_2fprotobuf_2ftimestamp_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Timestamp

// int64 seconds = 1;
inline void Timestamp::clear_seconds() {
  seconds_ = PROTOBUF_LONGLONG(0);
}
inline ::google::protobuf::int64 Timestamp::seconds() const {
  // @@protoc_insertion_point(field_get:google.protobuf.Timestamp.seconds)
  return seconds_;
}
inline void Timestamp::set_seconds(::google::protobuf::int64 value) {
  
  seconds_ = value;
  // @@protoc_insertion_point(field_set:google.protobuf.Timestamp.seconds)
}

// int32 nanos = 2;
inline void Timestamp::clear_nanos() {
  nanos_ = 0;
}
inline ::google::protobuf::int32 Timestamp::nanos() const {
  // @@protoc_insertion_point(field_get:google.protobuf.Timestamp.nanos)
  return nanos_;
}
inline void Timestamp::set_nanos(::google::protobuf::int32 value) {
  
  nanos_ = value;
  // @@protoc_insertion_point(field_set:google.protobuf.Timestamp.nanos)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // PROTOBUF_INCLUDED_google_2fprotobuf_2ftimestamp_2eproto
