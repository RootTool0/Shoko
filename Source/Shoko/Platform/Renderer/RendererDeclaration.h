#pragma once

public:

static bool Initialize();
static void Deinitialize();

static void PreRender();
static void PostRender();
        
static void Fill(FColor Color);
static void DrawRect(FGeometry Geometry, FColor Color);

private:
