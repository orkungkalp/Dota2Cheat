// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: messages.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_messages_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_messages_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
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
#define PROTOBUF_INTERNAL_EXPORT_messages_2eproto

#include "../ProtobufDefineFix.h"

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_messages_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_messages_2eproto;
class MsgInvokerCast;
struct MsgInvokerCastDefaultTypeInternal;
extern MsgInvokerCastDefaultTypeInternal _MsgInvokerCast_default_instance_;
class MsgInvokerCast_EntityMsg;
struct MsgInvokerCast_EntityMsgDefaultTypeInternal;
extern MsgInvokerCast_EntityMsgDefaultTypeInternal _MsgInvokerCast_EntityMsg_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::MsgInvokerCast* Arena::CreateMaybeMessage<::MsgInvokerCast>(Arena*);
template<> ::MsgInvokerCast_EntityMsg* Arena::CreateMaybeMessage<::MsgInvokerCast_EntityMsg>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class MsgInvokerCast_EntityMsg final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MsgInvokerCast.EntityMsg) */ {
 public:
  inline MsgInvokerCast_EntityMsg() : MsgInvokerCast_EntityMsg(nullptr) {}
  ~MsgInvokerCast_EntityMsg() override;
  explicit PROTOBUF_CONSTEXPR MsgInvokerCast_EntityMsg(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MsgInvokerCast_EntityMsg(const MsgInvokerCast_EntityMsg& from);
  MsgInvokerCast_EntityMsg(MsgInvokerCast_EntityMsg&& from) noexcept
    : MsgInvokerCast_EntityMsg() {
    *this = ::std::move(from);
  }

  inline MsgInvokerCast_EntityMsg& operator=(const MsgInvokerCast_EntityMsg& from) {
    CopyFrom(from);
    return *this;
  }
  inline MsgInvokerCast_EntityMsg& operator=(MsgInvokerCast_EntityMsg&& from) noexcept {
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

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
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
  static const MsgInvokerCast_EntityMsg& default_instance() {
    return *internal_default_instance();
  }
  static inline const MsgInvokerCast_EntityMsg* internal_default_instance() {
    return reinterpret_cast<const MsgInvokerCast_EntityMsg*>(
               &_MsgInvokerCast_EntityMsg_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MsgInvokerCast_EntityMsg& a, MsgInvokerCast_EntityMsg& b) {
    a.Swap(&b);
  }
  inline void Swap(MsgInvokerCast_EntityMsg* other) {
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
  void UnsafeArenaSwap(MsgInvokerCast_EntityMsg* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MsgInvokerCast_EntityMsg* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MsgInvokerCast_EntityMsg>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MsgInvokerCast_EntityMsg& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MsgInvokerCast_EntityMsg& from) {
    MsgInvokerCast_EntityMsg::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MsgInvokerCast_EntityMsg* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MsgInvokerCast.EntityMsg";
  }
  protected:
  explicit MsgInvokerCast_EntityMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kTargetEntityFieldNumber = 1,
  };
  // required int32 target_entity = 1;
  bool has_target_entity() const;
  private:
  bool _internal_has_target_entity() const;
  public:
  void clear_target_entity();
  int32_t target_entity() const;
  void set_target_entity(int32_t value);
  private:
  int32_t _internal_target_entity() const;
  void _internal_set_target_entity(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:MsgInvokerCast.EntityMsg)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    int32_t target_entity_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_messages_2eproto;
};
// -------------------------------------------------------------------

class MsgInvokerCast final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MsgInvokerCast) */ {
 public:
  inline MsgInvokerCast() : MsgInvokerCast(nullptr) {}
  ~MsgInvokerCast() override;
  explicit PROTOBUF_CONSTEXPR MsgInvokerCast(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MsgInvokerCast(const MsgInvokerCast& from);
  MsgInvokerCast(MsgInvokerCast&& from) noexcept
    : MsgInvokerCast() {
    *this = ::std::move(from);
  }

  inline MsgInvokerCast& operator=(const MsgInvokerCast& from) {
    CopyFrom(from);
    return *this;
  }
  inline MsgInvokerCast& operator=(MsgInvokerCast&& from) noexcept {
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

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
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
  static const MsgInvokerCast& default_instance() {
    return *internal_default_instance();
  }
  static inline const MsgInvokerCast* internal_default_instance() {
    return reinterpret_cast<const MsgInvokerCast*>(
               &_MsgInvokerCast_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(MsgInvokerCast& a, MsgInvokerCast& b) {
    a.Swap(&b);
  }
  inline void Swap(MsgInvokerCast* other) {
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
  void UnsafeArenaSwap(MsgInvokerCast* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MsgInvokerCast* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MsgInvokerCast>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MsgInvokerCast& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const MsgInvokerCast& from) {
    MsgInvokerCast::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MsgInvokerCast* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MsgInvokerCast";
  }
  protected:
  explicit MsgInvokerCast(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  typedef MsgInvokerCast_EntityMsg EntityMsg;

  // accessors -------------------------------------------------------

  enum : int {
    kEntityMsgFieldNumber = 1,
    kCastActivityFieldNumber = 2,
  };
  // required .MsgInvokerCast.EntityMsg entity_msg = 1;
  bool has_entity_msg() const;
  private:
  bool _internal_has_entity_msg() const;
  public:
  void clear_entity_msg();
  const ::MsgInvokerCast_EntityMsg& entity_msg() const;
  PROTOBUF_NODISCARD ::MsgInvokerCast_EntityMsg* release_entity_msg();
  ::MsgInvokerCast_EntityMsg* mutable_entity_msg();
  void set_allocated_entity_msg(::MsgInvokerCast_EntityMsg* entity_msg);
  private:
  const ::MsgInvokerCast_EntityMsg& _internal_entity_msg() const;
  ::MsgInvokerCast_EntityMsg* _internal_mutable_entity_msg();
  public:
  void unsafe_arena_set_allocated_entity_msg(
      ::MsgInvokerCast_EntityMsg* entity_msg);
  ::MsgInvokerCast_EntityMsg* unsafe_arena_release_entity_msg();

  // required int32 cast_activity = 2;
  bool has_cast_activity() const;
  private:
  bool _internal_has_cast_activity() const;
  public:
  void clear_cast_activity();
  int32_t cast_activity() const;
  void set_cast_activity(int32_t value);
  private:
  int32_t _internal_cast_activity() const;
  void _internal_set_cast_activity(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:MsgInvokerCast)
 private:
  class _Internal;

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::HasBits<1> _has_bits_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
    ::MsgInvokerCast_EntityMsg* entity_msg_;
    int32_t cast_activity_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_messages_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MsgInvokerCast_EntityMsg

// required int32 target_entity = 1;
inline bool MsgInvokerCast_EntityMsg::_internal_has_target_entity() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline bool MsgInvokerCast_EntityMsg::has_target_entity() const {
  return _internal_has_target_entity();
}
inline void MsgInvokerCast_EntityMsg::clear_target_entity() {
  _impl_.target_entity_ = 0;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline int32_t MsgInvokerCast_EntityMsg::_internal_target_entity() const {
  return _impl_.target_entity_;
}
inline int32_t MsgInvokerCast_EntityMsg::target_entity() const {
  // @@protoc_insertion_point(field_get:MsgInvokerCast.EntityMsg.target_entity)
  return _internal_target_entity();
}
inline void MsgInvokerCast_EntityMsg::_internal_set_target_entity(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000001u;
  _impl_.target_entity_ = value;
}
inline void MsgInvokerCast_EntityMsg::set_target_entity(int32_t value) {
  _internal_set_target_entity(value);
  // @@protoc_insertion_point(field_set:MsgInvokerCast.EntityMsg.target_entity)
}

// -------------------------------------------------------------------

// MsgInvokerCast

// required .MsgInvokerCast.EntityMsg entity_msg = 1;
inline bool MsgInvokerCast::_internal_has_entity_msg() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.entity_msg_ != nullptr);
  return value;
}
inline bool MsgInvokerCast::has_entity_msg() const {
  return _internal_has_entity_msg();
}
inline void MsgInvokerCast::clear_entity_msg() {
  if (_impl_.entity_msg_ != nullptr) _impl_.entity_msg_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const ::MsgInvokerCast_EntityMsg& MsgInvokerCast::_internal_entity_msg() const {
  const ::MsgInvokerCast_EntityMsg* p = _impl_.entity_msg_;
  return p != nullptr ? *p : reinterpret_cast<const ::MsgInvokerCast_EntityMsg&>(
      ::_MsgInvokerCast_EntityMsg_default_instance_);
}
inline const ::MsgInvokerCast_EntityMsg& MsgInvokerCast::entity_msg() const {
  // @@protoc_insertion_point(field_get:MsgInvokerCast.entity_msg)
  return _internal_entity_msg();
}
inline void MsgInvokerCast::unsafe_arena_set_allocated_entity_msg(
    ::MsgInvokerCast_EntityMsg* entity_msg) {
  if (GetArenaForAllocation() == nullptr) {
    delete reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(_impl_.entity_msg_);
  }
  _impl_.entity_msg_ = entity_msg;
  if (entity_msg) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:MsgInvokerCast.entity_msg)
}
inline ::MsgInvokerCast_EntityMsg* MsgInvokerCast::release_entity_msg() {
  _impl_._has_bits_[0] &= ~0x00000001u;
  ::MsgInvokerCast_EntityMsg* temp = _impl_.entity_msg_;
  _impl_.entity_msg_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old =  reinterpret_cast<::PROTOBUF_NAMESPACE_ID::MessageLite*>(temp);
  temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  if (GetArenaForAllocation() == nullptr) { delete old; }
#else  // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArenaForAllocation() != nullptr) {
    temp = ::PROTOBUF_NAMESPACE_ID::internal::DuplicateIfNonNull(temp);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return temp;
}
inline ::MsgInvokerCast_EntityMsg* MsgInvokerCast::unsafe_arena_release_entity_msg() {
  // @@protoc_insertion_point(field_release:MsgInvokerCast.entity_msg)
  _impl_._has_bits_[0] &= ~0x00000001u;
  ::MsgInvokerCast_EntityMsg* temp = _impl_.entity_msg_;
  _impl_.entity_msg_ = nullptr;
  return temp;
}
inline ::MsgInvokerCast_EntityMsg* MsgInvokerCast::_internal_mutable_entity_msg() {
  _impl_._has_bits_[0] |= 0x00000001u;
  if (_impl_.entity_msg_ == nullptr) {
    auto* p = CreateMaybeMessage<::MsgInvokerCast_EntityMsg>(GetArenaForAllocation());
    _impl_.entity_msg_ = p;
  }
  return _impl_.entity_msg_;
}
inline ::MsgInvokerCast_EntityMsg* MsgInvokerCast::mutable_entity_msg() {
  ::MsgInvokerCast_EntityMsg* _msg = _internal_mutable_entity_msg();
  // @@protoc_insertion_point(field_mutable:MsgInvokerCast.entity_msg)
  return _msg;
}
inline void MsgInvokerCast::set_allocated_entity_msg(::MsgInvokerCast_EntityMsg* entity_msg) {
  ::PROTOBUF_NAMESPACE_ID::Arena* message_arena = GetArenaForAllocation();
  if (message_arena == nullptr) {
    delete _impl_.entity_msg_;
  }
  if (entity_msg) {
    ::PROTOBUF_NAMESPACE_ID::Arena* submessage_arena =
        ::PROTOBUF_NAMESPACE_ID::Arena::InternalGetOwningArena(entity_msg);
    if (message_arena != submessage_arena) {
      entity_msg = ::PROTOBUF_NAMESPACE_ID::internal::GetOwnedMessage(
          message_arena, entity_msg, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  _impl_.entity_msg_ = entity_msg;
  // @@protoc_insertion_point(field_set_allocated:MsgInvokerCast.entity_msg)
}

// required int32 cast_activity = 2;
inline bool MsgInvokerCast::_internal_has_cast_activity() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  return value;
}
inline bool MsgInvokerCast::has_cast_activity() const {
  return _internal_has_cast_activity();
}
inline void MsgInvokerCast::clear_cast_activity() {
  _impl_.cast_activity_ = 0;
  _impl_._has_bits_[0] &= ~0x00000002u;
}
inline int32_t MsgInvokerCast::_internal_cast_activity() const {
  return _impl_.cast_activity_;
}
inline int32_t MsgInvokerCast::cast_activity() const {
  // @@protoc_insertion_point(field_get:MsgInvokerCast.cast_activity)
  return _internal_cast_activity();
}
inline void MsgInvokerCast::_internal_set_cast_activity(int32_t value) {
  _impl_._has_bits_[0] |= 0x00000002u;
  _impl_.cast_activity_ = value;
}
inline void MsgInvokerCast::set_cast_activity(int32_t value) {
  _internal_set_cast_activity(value);
  // @@protoc_insertion_point(field_set:MsgInvokerCast.cast_activity)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_messages_2eproto
