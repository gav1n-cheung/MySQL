// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pointcloud.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_pointcloud_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_pointcloud_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020001 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_pointcloud_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_pointcloud_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_pointcloud_2eproto;
class Pointcloud;
struct PointcloudDefaultTypeInternal;
extern PointcloudDefaultTypeInternal _Pointcloud_default_instance_;
class Vertex;
struct VertexDefaultTypeInternal;
extern VertexDefaultTypeInternal _Vertex_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::Pointcloud* Arena::CreateMaybeMessage<::Pointcloud>(Arena*);
template<> ::Vertex* Arena::CreateMaybeMessage<::Vertex>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class Vertex final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Vertex) */ {
 public:
  inline Vertex() : Vertex(nullptr) {}
  ~Vertex() override;
  explicit PROTOBUF_CONSTEXPR Vertex(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Vertex(const Vertex& from);
  Vertex(Vertex&& from) noexcept
    : Vertex() {
    *this = ::std::move(from);
  }

  inline Vertex& operator=(const Vertex& from) {
    CopyFrom(from);
    return *this;
  }
  inline Vertex& operator=(Vertex&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Vertex& default_instance() {
    return *internal_default_instance();
  }
  static inline const Vertex* internal_default_instance() {
    return reinterpret_cast<const Vertex*>(
               &_Vertex_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Vertex& a, Vertex& b) {
    a.Swap(&b);
  }
  inline void Swap(Vertex* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Vertex* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Vertex* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Vertex>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Vertex& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Vertex& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Vertex* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Vertex";
  }
  protected:
  explicit Vertex(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kXFieldNumber = 1,
    kYFieldNumber = 2,
    kZFieldNumber = 3,
  };
  // float x = 1;
  void clear_x();
  float x() const;
  void set_x(float value);
  private:
  float _internal_x() const;
  void _internal_set_x(float value);
  public:

  // float y = 2;
  void clear_y();
  float y() const;
  void set_y(float value);
  private:
  float _internal_y() const;
  void _internal_set_y(float value);
  public:

  // float z = 3;
  void clear_z();
  float z() const;
  void set_z(float value);
  private:
  float _internal_z() const;
  void _internal_set_z(float value);
  public:

  // @@protoc_insertion_point(class_scope:Vertex)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  float x_;
  float y_;
  float z_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_pointcloud_2eproto;
};
// -------------------------------------------------------------------

class Pointcloud final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Pointcloud) */ {
 public:
  inline Pointcloud() : Pointcloud(nullptr) {}
  ~Pointcloud() override;
  explicit PROTOBUF_CONSTEXPR Pointcloud(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Pointcloud(const Pointcloud& from);
  Pointcloud(Pointcloud&& from) noexcept
    : Pointcloud() {
    *this = ::std::move(from);
  }

  inline Pointcloud& operator=(const Pointcloud& from) {
    CopyFrom(from);
    return *this;
  }
  inline Pointcloud& operator=(Pointcloud&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Pointcloud& default_instance() {
    return *internal_default_instance();
  }
  static inline const Pointcloud* internal_default_instance() {
    return reinterpret_cast<const Pointcloud*>(
               &_Pointcloud_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Pointcloud& a, Pointcloud& b) {
    a.Swap(&b);
  }
  inline void Swap(Pointcloud* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Pointcloud* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Pointcloud* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Pointcloud>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Pointcloud& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const Pointcloud& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Pointcloud* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Pointcloud";
  }
  protected:
  explicit Pointcloud(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kVertexPart1FieldNumber = 1,
    kVertexPart2FieldNumber = 2,
    kVertexPart3FieldNumber = 3,
  };
  // repeated .Vertex Vertex_part1 = 1;
  int vertex_part1_size() const;
  private:
  int _internal_vertex_part1_size() const;
  public:
  void clear_vertex_part1();
  ::Vertex* mutable_vertex_part1(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >*
      mutable_vertex_part1();
  private:
  const ::Vertex& _internal_vertex_part1(int index) const;
  ::Vertex* _internal_add_vertex_part1();
  public:
  const ::Vertex& vertex_part1(int index) const;
  ::Vertex* add_vertex_part1();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >&
      vertex_part1() const;

  // repeated .Vertex Vertex_part2 = 2;
  int vertex_part2_size() const;
  private:
  int _internal_vertex_part2_size() const;
  public:
  void clear_vertex_part2();
  ::Vertex* mutable_vertex_part2(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >*
      mutable_vertex_part2();
  private:
  const ::Vertex& _internal_vertex_part2(int index) const;
  ::Vertex* _internal_add_vertex_part2();
  public:
  const ::Vertex& vertex_part2(int index) const;
  ::Vertex* add_vertex_part2();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >&
      vertex_part2() const;

  // repeated .Vertex Vertex_part3 = 3;
  int vertex_part3_size() const;
  private:
  int _internal_vertex_part3_size() const;
  public:
  void clear_vertex_part3();
  ::Vertex* mutable_vertex_part3(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >*
      mutable_vertex_part3();
  private:
  const ::Vertex& _internal_vertex_part3(int index) const;
  ::Vertex* _internal_add_vertex_part3();
  public:
  const ::Vertex& vertex_part3(int index) const;
  ::Vertex* add_vertex_part3();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >&
      vertex_part3() const;

  // @@protoc_insertion_point(class_scope:Pointcloud)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex > vertex_part1_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex > vertex_part2_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex > vertex_part3_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_pointcloud_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Vertex

// float x = 1;
inline void Vertex::clear_x() {
  x_ = 0;
}
inline float Vertex::_internal_x() const {
  return x_;
}
inline float Vertex::x() const {
  // @@protoc_insertion_point(field_get:Vertex.x)
  return _internal_x();
}
inline void Vertex::_internal_set_x(float value) {
  
  x_ = value;
}
inline void Vertex::set_x(float value) {
  _internal_set_x(value);
  // @@protoc_insertion_point(field_set:Vertex.x)
}

// float y = 2;
inline void Vertex::clear_y() {
  y_ = 0;
}
inline float Vertex::_internal_y() const {
  return y_;
}
inline float Vertex::y() const {
  // @@protoc_insertion_point(field_get:Vertex.y)
  return _internal_y();
}
inline void Vertex::_internal_set_y(float value) {
  
  y_ = value;
}
inline void Vertex::set_y(float value) {
  _internal_set_y(value);
  // @@protoc_insertion_point(field_set:Vertex.y)
}

// float z = 3;
inline void Vertex::clear_z() {
  z_ = 0;
}
inline float Vertex::_internal_z() const {
  return z_;
}
inline float Vertex::z() const {
  // @@protoc_insertion_point(field_get:Vertex.z)
  return _internal_z();
}
inline void Vertex::_internal_set_z(float value) {
  
  z_ = value;
}
inline void Vertex::set_z(float value) {
  _internal_set_z(value);
  // @@protoc_insertion_point(field_set:Vertex.z)
}

// -------------------------------------------------------------------

// Pointcloud

// repeated .Vertex Vertex_part1 = 1;
inline int Pointcloud::_internal_vertex_part1_size() const {
  return vertex_part1_.size();
}
inline int Pointcloud::vertex_part1_size() const {
  return _internal_vertex_part1_size();
}
inline void Pointcloud::clear_vertex_part1() {
  vertex_part1_.Clear();
}
inline ::Vertex* Pointcloud::mutable_vertex_part1(int index) {
  // @@protoc_insertion_point(field_mutable:Pointcloud.Vertex_part1)
  return vertex_part1_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >*
Pointcloud::mutable_vertex_part1() {
  // @@protoc_insertion_point(field_mutable_list:Pointcloud.Vertex_part1)
  return &vertex_part1_;
}
inline const ::Vertex& Pointcloud::_internal_vertex_part1(int index) const {
  return vertex_part1_.Get(index);
}
inline const ::Vertex& Pointcloud::vertex_part1(int index) const {
  // @@protoc_insertion_point(field_get:Pointcloud.Vertex_part1)
  return _internal_vertex_part1(index);
}
inline ::Vertex* Pointcloud::_internal_add_vertex_part1() {
  return vertex_part1_.Add();
}
inline ::Vertex* Pointcloud::add_vertex_part1() {
  ::Vertex* _add = _internal_add_vertex_part1();
  // @@protoc_insertion_point(field_add:Pointcloud.Vertex_part1)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >&
Pointcloud::vertex_part1() const {
  // @@protoc_insertion_point(field_list:Pointcloud.Vertex_part1)
  return vertex_part1_;
}

// repeated .Vertex Vertex_part2 = 2;
inline int Pointcloud::_internal_vertex_part2_size() const {
  return vertex_part2_.size();
}
inline int Pointcloud::vertex_part2_size() const {
  return _internal_vertex_part2_size();
}
inline void Pointcloud::clear_vertex_part2() {
  vertex_part2_.Clear();
}
inline ::Vertex* Pointcloud::mutable_vertex_part2(int index) {
  // @@protoc_insertion_point(field_mutable:Pointcloud.Vertex_part2)
  return vertex_part2_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >*
Pointcloud::mutable_vertex_part2() {
  // @@protoc_insertion_point(field_mutable_list:Pointcloud.Vertex_part2)
  return &vertex_part2_;
}
inline const ::Vertex& Pointcloud::_internal_vertex_part2(int index) const {
  return vertex_part2_.Get(index);
}
inline const ::Vertex& Pointcloud::vertex_part2(int index) const {
  // @@protoc_insertion_point(field_get:Pointcloud.Vertex_part2)
  return _internal_vertex_part2(index);
}
inline ::Vertex* Pointcloud::_internal_add_vertex_part2() {
  return vertex_part2_.Add();
}
inline ::Vertex* Pointcloud::add_vertex_part2() {
  ::Vertex* _add = _internal_add_vertex_part2();
  // @@protoc_insertion_point(field_add:Pointcloud.Vertex_part2)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >&
Pointcloud::vertex_part2() const {
  // @@protoc_insertion_point(field_list:Pointcloud.Vertex_part2)
  return vertex_part2_;
}

// repeated .Vertex Vertex_part3 = 3;
inline int Pointcloud::_internal_vertex_part3_size() const {
  return vertex_part3_.size();
}
inline int Pointcloud::vertex_part3_size() const {
  return _internal_vertex_part3_size();
}
inline void Pointcloud::clear_vertex_part3() {
  vertex_part3_.Clear();
}
inline ::Vertex* Pointcloud::mutable_vertex_part3(int index) {
  // @@protoc_insertion_point(field_mutable:Pointcloud.Vertex_part3)
  return vertex_part3_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >*
Pointcloud::mutable_vertex_part3() {
  // @@protoc_insertion_point(field_mutable_list:Pointcloud.Vertex_part3)
  return &vertex_part3_;
}
inline const ::Vertex& Pointcloud::_internal_vertex_part3(int index) const {
  return vertex_part3_.Get(index);
}
inline const ::Vertex& Pointcloud::vertex_part3(int index) const {
  // @@protoc_insertion_point(field_get:Pointcloud.Vertex_part3)
  return _internal_vertex_part3(index);
}
inline ::Vertex* Pointcloud::_internal_add_vertex_part3() {
  return vertex_part3_.Add();
}
inline ::Vertex* Pointcloud::add_vertex_part3() {
  ::Vertex* _add = _internal_add_vertex_part3();
  // @@protoc_insertion_point(field_add:Pointcloud.Vertex_part3)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Vertex >&
Pointcloud::vertex_part3() const {
  // @@protoc_insertion_point(field_list:Pointcloud.Vertex_part3)
  return vertex_part3_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_pointcloud_2eproto
