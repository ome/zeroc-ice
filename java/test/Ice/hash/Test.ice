// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#pragma once

[["java:package:test.Ice.hash"]]
module Test
{

struct PointF
{
    float x;
    float y;
    float z;
};

struct PointD
{
    double x;
    double y;
    double z;
};

struct Point
{
    int x;
    int y;
};
sequence<Point> Points;

struct Polyline
{
    Points vertices;
};

struct Color
{
    int r;
    int g;
    int b;
    int a;
};


dictionary<int, Color> StringColorMap;

struct ColorPalette
{
    StringColorMap colors;
};

class Pen
{
    int thickness;
    Test::Color color;
};

struct Draw
{
    Test::Color backgroundColor;
    Test::Pen pen;
    bool shared;
};

};

