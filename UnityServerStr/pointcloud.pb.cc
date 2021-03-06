// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pointcloud.proto

#include "pointcloud.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR Vertex::Vertex(
    ::_pbi::ConstantInitialized)
  : x_(0)
  , y_(0)
  , z_(0){}
struct VertexDefaultTypeInternal {
  PROTOBUF_CONSTEXPR VertexDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~VertexDefaultTypeInternal() {}
  union {
    Vertex _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 VertexDefaultTypeInternal _Vertex_default_instance_;
PROTOBUF_CONSTEXPR Pointcloud::Pointcloud(
    ::_pbi::ConstantInitialized)
  : vertex_part1_()
  , vertex_part2_()
  , vertex_part3_(){}
struct PointcloudDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PointcloudDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PointcloudDefaultTypeInternal() {}
  union {
    Pointcloud _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PointcloudDefaultTypeInternal _Pointcloud_default_instance_;
static ::_pb::Metadata file_level_metadata_pointcloud_2eproto[2];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_pointcloud_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_pointcloud_2eproto = nullptr;

const uint32_t TableStruct_pointcloud_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Vertex, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Vertex, x_),
  PROTOBUF_FIELD_OFFSET(::Vertex, y_),
  PROTOBUF_FIELD_OFFSET(::Vertex, z_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Pointcloud, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Pointcloud, vertex_part1_),
  PROTOBUF_FIELD_OFFSET(::Pointcloud, vertex_part2_),
  PROTOBUF_FIELD_OFFSET(::Pointcloud, vertex_part3_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Vertex)},
  { 9, -1, -1, sizeof(::Pointcloud)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_Vertex_default_instance_._instance,
  &::_Pointcloud_default_instance_._instance,
};

const char descriptor_table_protodef_pointcloud_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\020pointcloud.proto\")\n\006Vertex\022\t\n\001x\030\001 \001(\002\022"
  "\t\n\001y\030\002 \001(\002\022\t\n\001z\030\003 \001(\002\"i\n\nPointcloud\022\035\n\014V"
  "ertex_part1\030\001 \003(\0132\007.Vertex\022\035\n\014Vertex_par"
  "t2\030\002 \003(\0132\007.Vertex\022\035\n\014Vertex_part3\030\003 \003(\0132"
  "\007.Vertexb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_pointcloud_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_pointcloud_2eproto = {
    false, false, 176, descriptor_table_protodef_pointcloud_2eproto,
    "pointcloud.proto",
    &descriptor_table_pointcloud_2eproto_once, nullptr, 0, 2,
    schemas, file_default_instances, TableStruct_pointcloud_2eproto::offsets,
    file_level_metadata_pointcloud_2eproto, file_level_enum_descriptors_pointcloud_2eproto,
    file_level_service_descriptors_pointcloud_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_pointcloud_2eproto_getter() {
  return &descriptor_table_pointcloud_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_pointcloud_2eproto(&descriptor_table_pointcloud_2eproto);

// ===================================================================

class Vertex::_Internal {
 public:
};

Vertex::Vertex(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:Vertex)
}
Vertex::Vertex(const Vertex& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&x_, &from.x_,
    static_cast<size_t>(reinterpret_cast<char*>(&z_) -
    reinterpret_cast<char*>(&x_)) + sizeof(z_));
  // @@protoc_insertion_point(copy_constructor:Vertex)
}

inline void Vertex::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&x_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&z_) -
    reinterpret_cast<char*>(&x_)) + sizeof(z_));
}

Vertex::~Vertex() {
  // @@protoc_insertion_point(destructor:Vertex)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Vertex::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Vertex::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Vertex::Clear() {
// @@protoc_insertion_point(message_clear_start:Vertex)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&x_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&z_) -
      reinterpret_cast<char*>(&x_)) + sizeof(z_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Vertex::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // float x = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 13)) {
          x_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float y = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 21)) {
          y_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float z = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          z_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Vertex::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Vertex)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // float x = 1;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(1, this->_internal_x(), target);
  }

  // float y = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(2, this->_internal_y(), target);
  }

  // float z = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = this->_internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_z(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Vertex)
  return target;
}

size_t Vertex::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Vertex)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // float x = 1;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    total_size += 1 + 4;
  }

  // float y = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    total_size += 1 + 4;
  }

  // float z = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = this->_internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Vertex::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Vertex::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Vertex::GetClassData() const { return &_class_data_; }

void Vertex::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Vertex *>(to)->MergeFrom(
      static_cast<const Vertex &>(from));
}


void Vertex::MergeFrom(const Vertex& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Vertex)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = from._internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    _internal_set_x(from._internal_x());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = from._internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    _internal_set_y(from._internal_y());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = from._internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    _internal_set_z(from._internal_z());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Vertex::CopyFrom(const Vertex& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Vertex)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Vertex::IsInitialized() const {
  return true;
}

void Vertex::InternalSwap(Vertex* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Vertex, z_)
      + sizeof(Vertex::z_)
      - PROTOBUF_FIELD_OFFSET(Vertex, x_)>(
          reinterpret_cast<char*>(&x_),
          reinterpret_cast<char*>(&other->x_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Vertex::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_pointcloud_2eproto_getter, &descriptor_table_pointcloud_2eproto_once,
      file_level_metadata_pointcloud_2eproto[0]);
}

// ===================================================================

class Pointcloud::_Internal {
 public:
};

Pointcloud::Pointcloud(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned),
  vertex_part1_(arena),
  vertex_part2_(arena),
  vertex_part3_(arena) {
  SharedCtor();
  // @@protoc_insertion_point(arena_constructor:Pointcloud)
}
Pointcloud::Pointcloud(const Pointcloud& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      vertex_part1_(from.vertex_part1_),
      vertex_part2_(from.vertex_part2_),
      vertex_part3_(from.vertex_part3_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:Pointcloud)
}

inline void Pointcloud::SharedCtor() {
}

Pointcloud::~Pointcloud() {
  // @@protoc_insertion_point(destructor:Pointcloud)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Pointcloud::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void Pointcloud::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Pointcloud::Clear() {
// @@protoc_insertion_point(message_clear_start:Pointcloud)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  vertex_part1_.Clear();
  vertex_part2_.Clear();
  vertex_part3_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Pointcloud::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .Vertex Vertex_part1 = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_vertex_part1(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated .Vertex Vertex_part2 = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_vertex_part2(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      // repeated .Vertex Vertex_part3 = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_vertex_part3(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<26>(ptr));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Pointcloud::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Pointcloud)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .Vertex Vertex_part1 = 1;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_vertex_part1_size()); i < n; i++) {
    const auto& repfield = this->_internal_vertex_part1(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(1, repfield, repfield.GetCachedSize(), target, stream);
  }

  // repeated .Vertex Vertex_part2 = 2;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_vertex_part2_size()); i < n; i++) {
    const auto& repfield = this->_internal_vertex_part2(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(2, repfield, repfield.GetCachedSize(), target, stream);
  }

  // repeated .Vertex Vertex_part3 = 3;
  for (unsigned i = 0,
      n = static_cast<unsigned>(this->_internal_vertex_part3_size()); i < n; i++) {
    const auto& repfield = this->_internal_vertex_part3(i);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
        InternalWriteMessage(3, repfield, repfield.GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Pointcloud)
  return target;
}

size_t Pointcloud::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Pointcloud)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .Vertex Vertex_part1 = 1;
  total_size += 1UL * this->_internal_vertex_part1_size();
  for (const auto& msg : this->vertex_part1_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated .Vertex Vertex_part2 = 2;
  total_size += 1UL * this->_internal_vertex_part2_size();
  for (const auto& msg : this->vertex_part2_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // repeated .Vertex Vertex_part3 = 3;
  total_size += 1UL * this->_internal_vertex_part3_size();
  for (const auto& msg : this->vertex_part3_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Pointcloud::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Pointcloud::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Pointcloud::GetClassData() const { return &_class_data_; }

void Pointcloud::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Pointcloud *>(to)->MergeFrom(
      static_cast<const Pointcloud &>(from));
}


void Pointcloud::MergeFrom(const Pointcloud& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Pointcloud)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  vertex_part1_.MergeFrom(from.vertex_part1_);
  vertex_part2_.MergeFrom(from.vertex_part2_);
  vertex_part3_.MergeFrom(from.vertex_part3_);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Pointcloud::CopyFrom(const Pointcloud& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Pointcloud)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Pointcloud::IsInitialized() const {
  return true;
}

void Pointcloud::InternalSwap(Pointcloud* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  vertex_part1_.InternalSwap(&other->vertex_part1_);
  vertex_part2_.InternalSwap(&other->vertex_part2_);
  vertex_part3_.InternalSwap(&other->vertex_part3_);
}

::PROTOBUF_NAMESPACE_ID::Metadata Pointcloud::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_pointcloud_2eproto_getter, &descriptor_table_pointcloud_2eproto_once,
      file_level_metadata_pointcloud_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Vertex*
Arena::CreateMaybeMessage< ::Vertex >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Vertex >(arena);
}
template<> PROTOBUF_NOINLINE ::Pointcloud*
Arena::CreateMaybeMessage< ::Pointcloud >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Pointcloud >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
