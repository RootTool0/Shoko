#pragma once

#define SHOKO_STATIC_ASSERT(Condition, Message) static_assert(Condition, "\n\'\n[Shoko]\n" Message "\n")

#define SHOKO_CLASS(Class) \
static constexpr GUTID Class##_GUTID = __COUNTER__; \
class Class; \
template<> struct TClassByGUTIDPrivate<Class##_GUTID> { using Type = Class; };

#define SHOKO_GENERATED_BODY(Class)  \
public: \
    static constexpr GUTID StaticGUTID = Class##_GUTID; \
private:

#define SHOKO_GENERATED_TEMPLATE_BODY()  \
public: \
    static constexpr GUTID StaticGUTID = __COUNTER__; \
private:

// GUTID - Globally Unique Type Identifier
// Я знаю, звучит странно - но мне нравится

#define SHOKO_CHECK_ALIAS_EXISTS(Alias) static_assert(Shoko::Meta::IsDefined<Shoko::Alias>, "Алиас " #Alias " не существует");

#define SHOKO_REFLECTION_HAS_METHOD(Obj, MethodName) Reflection::HasMember<decltype(Obj)>([](auto& x) -> decltype(&Meta::Decay<decltype(x)>::MethodName) {})
#define SHOKO_REFLECTION_HAS_FIELD(Obj, FieldName)   Reflection::HasMember<decltype(Obj)>
