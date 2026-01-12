#pragma once

#define SHOKO_STATIC_ASSERT(Condition, Message) static_assert(Condition, "\n\'\n[Shoko]\n" Message "\n")

#define SHOKO_GENERATED_BODY() public: static constexpr GUTID_t GUTID = __COUNTER__; private: 

// GUTID - Globally Unique Type Identifier
// Я знаю, звучит странно - но мне нравится

#define SHOKO_CHECK_ALIAS_EXISTS(Alias) static_assert(Shoko::Meta::IsDefined<Shoko::Alias>, "Алиас " #Alias " не существует");
