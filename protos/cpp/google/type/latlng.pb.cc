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

#include "google/type/latlng.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace google {
namespace type {
class LatLngDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<LatLng> _instance;
} _LatLng_default_instance_;
}  // namespace type
}  // namespace google
static void InitDefaultsLatLng_google_2ftype_2flatlng_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::google::type::_LatLng_default_instance_;
    new (ptr) ::google::type::LatLng();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::google::type::LatLng::InitAsDefaultInstance();
}

FIRESTORE_EXPORT ::google::protobuf::internal::SCCInfo<0> scc_info_LatLng_google_2ftype_2flatlng_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsLatLng_google_2ftype_2flatlng_2eproto}, {}};

void InitDefaults_google_2ftype_2flatlng_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_LatLng_google_2ftype_2flatlng_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_google_2ftype_2flatlng_2eproto[1];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_google_2ftype_2flatlng_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_google_2ftype_2flatlng_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_google_2ftype_2flatlng_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::google::type::LatLng, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::google::type::LatLng, latitude_),
  PROTOBUF_FIELD_OFFSET(::google::type::LatLng, longitude_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::google::type::LatLng)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::google::type::_LatLng_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_google_2ftype_2flatlng_2eproto = {
  {}, AddDescriptors_google_2ftype_2flatlng_2eproto, "google/type/latlng.proto", schemas,
  file_default_instances, TableStruct_google_2ftype_2flatlng_2eproto::offsets,
  file_level_metadata_google_2ftype_2flatlng_2eproto, 1, file_level_enum_descriptors_google_2ftype_2flatlng_2eproto, file_level_service_descriptors_google_2ftype_2flatlng_2eproto,
};

const char descriptor_table_protodef_google_2ftype_2flatlng_2eproto[] =
  "\n\030google/type/latlng.proto\022\013google.type\""
  "-\n\006LatLng\022\020\n\010latitude\030\001 \001(\001\022\021\n\tlongitude"
  "\030\002 \001(\001B`\n\017com.google.typeB\013LatLngProtoP\001"
  "Z8google.golang.org/genproto/googleapis/"
  "type/latlng;latlng\242\002\003GTPb\006proto3"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_google_2ftype_2flatlng_2eproto = {
  false, InitDefaults_google_2ftype_2flatlng_2eproto, 
  descriptor_table_protodef_google_2ftype_2flatlng_2eproto,
  "google/type/latlng.proto", &assign_descriptors_table_google_2ftype_2flatlng_2eproto, 192,
};

void AddDescriptors_google_2ftype_2flatlng_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_google_2ftype_2flatlng_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_google_2ftype_2flatlng_2eproto = []() { AddDescriptors_google_2ftype_2flatlng_2eproto(); return true; }();
namespace google {
namespace type {

// ===================================================================

void LatLng::InitAsDefaultInstance() {
}
class LatLng::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int LatLng::kLatitudeFieldNumber;
const int LatLng::kLongitudeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

LatLng::LatLng()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:google.type.LatLng)
}
LatLng::LatLng(const LatLng& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&latitude_, &from.latitude_,
    static_cast<size_t>(reinterpret_cast<char*>(&longitude_) -
    reinterpret_cast<char*>(&latitude_)) + sizeof(longitude_));
  // @@protoc_insertion_point(copy_constructor:google.type.LatLng)
}

void LatLng::SharedCtor() {
  ::memset(&latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&longitude_) -
      reinterpret_cast<char*>(&latitude_)) + sizeof(longitude_));
}

LatLng::~LatLng() {
  // @@protoc_insertion_point(destructor:google.type.LatLng)
  SharedDtor();
}

void LatLng::SharedDtor() {
}

void LatLng::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const LatLng& LatLng::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_LatLng_google_2ftype_2flatlng_2eproto.base);
  return *internal_default_instance();
}


void LatLng::Clear() {
// @@protoc_insertion_point(message_clear_start:google.type.LatLng)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&latitude_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&longitude_) -
      reinterpret_cast<char*>(&latitude_)) + sizeof(longitude_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* LatLng::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<LatLng*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // double latitude = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 9) goto handle_unusual;
        msg->set_latitude(::google::protobuf::io::UnalignedLoad<double>(ptr));
        ptr += sizeof(double);
        break;
      }
      // double longitude = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 17) goto handle_unusual;
        msg->set_longitude(::google::protobuf::io::UnalignedLoad<double>(ptr));
        ptr += sizeof(double);
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool LatLng::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:google.type.LatLng)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // double latitude = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (9 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &latitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // double longitude = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (17 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &longitude_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:google.type.LatLng)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:google.type.LatLng)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void LatLng::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:google.type.LatLng)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double latitude = 1;
  if (this->latitude() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(1, this->latitude(), output);
  }

  // double longitude = 2;
  if (this->longitude() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->longitude(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:google.type.LatLng)
}

::google::protobuf::uint8* LatLng::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:google.type.LatLng)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // double latitude = 1;
  if (this->latitude() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(1, this->latitude(), target);
  }

  // double longitude = 2;
  if (this->longitude() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->longitude(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:google.type.LatLng)
  return target;
}

size_t LatLng::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:google.type.LatLng)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // double latitude = 1;
  if (this->latitude() != 0) {
    total_size += 1 + 8;
  }

  // double longitude = 2;
  if (this->longitude() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void LatLng::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:google.type.LatLng)
  GOOGLE_DCHECK_NE(&from, this);
  const LatLng* source =
      ::google::protobuf::DynamicCastToGenerated<LatLng>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:google.type.LatLng)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:google.type.LatLng)
    MergeFrom(*source);
  }
}

void LatLng::MergeFrom(const LatLng& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:google.type.LatLng)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.latitude() != 0) {
    set_latitude(from.latitude());
  }
  if (from.longitude() != 0) {
    set_longitude(from.longitude());
  }
}

void LatLng::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:google.type.LatLng)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LatLng::CopyFrom(const LatLng& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:google.type.LatLng)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LatLng::IsInitialized() const {
  return true;
}

void LatLng::Swap(LatLng* other) {
  if (other == this) return;
  InternalSwap(other);
}
void LatLng::InternalSwap(LatLng* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(latitude_, other->latitude_);
  swap(longitude_, other->longitude_);
}

::google::protobuf::Metadata LatLng::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_google_2ftype_2flatlng_2eproto);
  return ::file_level_metadata_google_2ftype_2flatlng_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace type
}  // namespace google
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::google::type::LatLng* Arena::CreateMaybeMessage< ::google::type::LatLng >(Arena* arena) {
  return Arena::CreateInternal< ::google::type::LatLng >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
