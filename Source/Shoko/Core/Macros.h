#pragma once

#define SHOKO_STATIC_ASSERT(Condition, Message) static_assert(Condition, "\n\'\n[Shoko]\n" Message "\n")

#define SHOKO_GENERATED_BODY(ClassName, TempVal)  \
public: \
static constexpr GUTID_t GUTID = TempVal; \
friend ClassName GetClassByGUTID(GUTID_Tag<TempVal>); \
private:

#define SHOKO_GENERATED_BODY_TEMPLATE(TempVal)  \
public: \
static constexpr GUTID_t GUTID = TempVal; \
private:

// friend ClassName GetClassByGUTID(GUTID_Tag<GUTID>); \
// static constexpr GUTID_t GUTID = __COUNTER__; \
// friend ClassName* IdentifyWidget(Meta::IntToType<GUTID>) { return nullptr; } \

// GUTID - Globally Unique Type Identifier
// Я знаю, звучит странно - но мне нравится

#define SHOKO_CHECK_ALIAS_EXISTS(Alias) static_assert(Shoko::Meta::IsDefined<Shoko::Alias>, "Алиас " #Alias " не существует");
