#pragma once

public:

bool Initialize();
void Deinitialize() const;

void SetTitle(const char* NewTitle) const;
void SetSize(FUIntVector2D Size) const;

private:
