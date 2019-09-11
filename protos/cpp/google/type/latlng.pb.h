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
// source: google/type/latlng.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2ftype_2flatlng_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_google_2ftype_2flatlng_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009001 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_google_2ftype_2flatlng_2eproto FIRESTORE_EXPORT
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct FIRESTORE_EXPORT TableStruct_google_2ftype_2flatlng_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern FIRESTORE_EXPORT const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_google_2ftype_2flatlng_2eproto;
namespace google {
namespace type {
class LatLng;
class LatLngDefaultTypeInternal;
FIRESTORE_EXPORT extern LatLngDefaultTypeInternal _LatLng_default_instance_;
}  // namespace type
}  // namespace google
PROTOBUF_NAMESPACE_OPEN
template<> FIRESTORE_EXPORT ::google::type::LatLng* Arena::CreateMaybeMessage<::google::type::LatLng>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace google {
namespace type {

// ===================================================================

class FIRESTORE_EXPORT LatLng :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:google.type.LatLng) */ {
 public:
  LatLng();
  virtual ~LatLng();

  LatLng(const LatLng& from);
  LatLng(LatLng&& from) noexcept
    : LatLng() {
    *this = ::std::move(from);
  }

  inline LatLng& operator=(const LatLng& from) {
    CopyFrom(from);
    return *this;
  }
  inline LatLng& operator=(LatLng&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const LatLng& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const LatLng* internal_default_instance() {
    return reinterpret_cast<const LatLng*>(
               &_LatLng_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(LatLng& a, LatLng& b) {
    a.Swap(&b);
  }
  inline void Swap(LatLng* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline LatLng* New() const final {
    return CreateMaybeMessage<LatLng>(nullptr);
  }

  LatLng* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<LatLng>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const LatLng& from);
  void MergeFrom(const LatLng& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LatLng* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "google.type.LatLng";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_google_2ftype_2flatlng_2eproto);
    return ::descriptor_table_google_2ftype_2flatlng_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kLatitudeFieldNumber = 1,
    kLongitudeFieldNumber = 2,
  };
  // double latitude = 1;
  void clear_latitude();
  double latitude() const;
  void set_latitude(double value);

  // double longitude = 2;
  void clear_longitude();
  double longitude() const;
  void set_longitude(double value);

  // @@protoc_insertion_point(class_scope:google.type.LatLng)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  double latitude_;
  double longitude_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_google_2ftype_2flatlng_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LatLng

// double latitude = 1;
inline void LatLng::clear_latitude() {
  latitude_ = 0;
}
inline double LatLng::latitude() const {
  // @@protoc_insertion_point(field_get:google.type.LatLng.latitude)
  return latitude_;
}
inline void LatLng::set_latitude(double value) {
  
  latitude_ = value;
  // @@protoc_insertion_point(field_set:google.type.LatLng.latitude)
}

// double longitude = 2;
inline void LatLng::clear_longitude() {
  longitude_ = 0;
}
inline double LatLng::longitude() const {
  // @@protoc_insertion_point(field_get:google.type.LatLng.longitude)
  return longitude_;
}
inline void LatLng::set_longitude(double value) {
  
  longitude_ = value;
  // @@protoc_insertion_point(field_set:google.type.LatLng.longitude)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace type
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_google_2ftype_2flatlng_2eproto
