
#ifndef _TERMINAL_COLOR__H_
#define _TERMINAL_COLOR__H_

#include <cstdint>
#include <vector>
#include <map>

namespace LRTerminal
{
  // The color class is partly based on the TCODColor of the tcod library.
  class Color
  {
  public:
    // Default constructor
    Color();
    // RGB constructor
    Color(uint8_t R, uint8_t G, uint8_t B);
    // To make a color from other color spaces
    static Color fromRGB(uint8_t R, uint8_t G, uint8_t B); // Same as constructor
    static Color fromHSV(float H, float S, float V); // Hue [0;360[, Saturation [0;1[, Value [0;1[
    static Color fromHSL(float H, float S, float L); // Hue [0;360[, Saturation [0;1[, Luminosity [0;1[
    //
    // Copy constructor
    Color(const Color& that);
    // Operator =
    Color& operator=(const Color& that);
    //
    // Operator ==, !=
    bool operator==(const Color& that) const;
    bool operator!=(const Color& that) const;
    //
    // Operator *
    Color operator*(const Color& other) const;
    Color operator*(const float scalar) const;
    // Operator +, -
    Color operator+(const Color& other) const;
    // Operator -
    Color operator-(const Color& other) const;

    // Getters
    uint8_t getRed(void) const;
    uint8_t getGreen(void) const;
    uint8_t getBlue(void) const;

    void getRGB(uint8_t& R, uint8_t& G, uint8_t& B);
    void getHSV(float& H, float& S, float& V);
    void getHSL(float& H, float& S, float& L);

    // Convert to an XRGB value
    unsigned toXRGB(void) const;

    // Setters
    void setRed(uint8_t R);
    void setGreen(uint8_t R);
    void setBlue(uint8_t R);

    void setRGB(const uint8_t R, const uint8_t G, const uint8_t B);
    void setHSV(const float H, const float S, const float V);
    void setHSL(const float H, const float S, const float L);

    //
    // Shift Hue, Hue in grades
    void shiftHueHSV(float HShift);
    void shiftHueHSL(float HShift);

    // Scale colors
    void scaleHSV(float sscale, float vscale);
    void scaleHSL(float sscale, float lscale);

    //
    // Interpolation/Extrapolation
    static Color lerp(const Color& a, const Color& b, const float coeff);

    // Other operations
    // Lighten: max on each component
    static Color lighten(const Color& a, const Color& b);
    // Darken: min on each component
    static Color darken(const Color& a, const Color& b);
    // Screen: (1 - (1-a)*(1-b)) on each component
    static Color screen(const Color& a, const Color& b);
    // Color Dodge: (b / (1-a)) on each component
    static Color colorDodge(const Color& a, const Color& b);
    // Color Burn: (1 - (1-a)/b) on each component
    static Color colorBurn(const Color& a, const Color& b);
    // Burn: (a + b - 1) on each component
    static Color burn(const Color& a, const Color& b);
    // Overlay: ((b < 0.5) ? (2*a*b) : (1 - 2*(1-a)*(1-b))) on each component
    static Color overlay(const Color& a, const Color& b);

  private:
    // RGB components
    uint8_t m_R;
    uint8_t m_G;
    uint8_t m_B;

  public:
    // Named colors are constant colors in the namespace of this class
    // Names comes from the libTCOD

    // Black & white
    static const Color black;
    static const Color white;

    // Grey
    static const Color darkestGrey;
    static const Color darkerGrey;
    static const Color darkGrey;
    static const Color grey;
    static const Color lightGrey;
    static const Color lighterGrey;
    static const Color lightestGrey;

    // Sepia
    static const Color darkestSepia;
    static const Color darkerSepia;
    static const Color darkSepia;
    static const Color sepia;
    static const Color lightSepia;
    static const Color lighterSepia;
    static const Color lightestSepia;

    // Red
    static const Color darkestRed;
    static const Color darkerRed;
    static const Color darkRed;
    static const Color red;
    static const Color lightRed;
    static const Color lighterRed;
    static const Color lightestRed;
    static const Color desaturatedRed;

    // Flame
    static const Color darkestFlame;
    static const Color darkerFlame;
    static const Color darkFlame;
    static const Color flame;
    static const Color lightFlame;
    static const Color lighterFlame;
    static const Color lightestFlame;
    static const Color desaturatedFlame;

    // Orange
    static const Color darkestOrange;
    static const Color darkerOrange;
    static const Color darkOrange;
    static const Color orange;
    static const Color lightOrange;
    static const Color lighterOrange;
    static const Color lightestOrange;
    static const Color desaturatedOrange;

    // Amber
    static const Color darkestAmber;
    static const Color darkerAmber;
    static const Color darkAmber;
    static const Color amber;
    static const Color lightAmber;
    static const Color lighterAmber;
    static const Color lightestAmber;
    static const Color desaturatedAmber;

    // Yellow
    static const Color darkestYellow;
    static const Color darkerYellow;
    static const Color darkYellow;
    static const Color yellow;
    static const Color lightYellow;
    static const Color lighterYellow;
    static const Color lightestYellow;
    static const Color desaturatedYellow;

    // Lime
    static const Color darkestLime;
    static const Color darkerLime;
    static const Color darkLime;
    static const Color lime;
    static const Color lightLime;
    static const Color lighterLime;
    static const Color lightestLime;
    static const Color desaturatedLime;

    // Chartreuse
    static const Color darkestChartreuse;
    static const Color darkerChartreuse;
    static const Color darkChartreuse;
    static const Color chartreuse;
    static const Color lightChartreuse;
    static const Color lighterChartreuse;
    static const Color lightestChartreuse;
    static const Color desaturatedChartreuse;

    /*
    // Ggreen -- 105° hue not in LibTCOD named colors
    static const Color darkestGgreen;
    static const Color darkerGgreen;
    static const Color darkGgreen;
    static const Color ggreen;
    static const Color lightGgreen;
    static const Color lighterGgreen;
    static const Color lightestGgreen;
    static const Color desaturatedGgreen;
    */

    // Green
    static const Color darkestGreen;
    static const Color darkerGreen;
    static const Color darkGreen;
    static const Color green;
    static const Color lightGreen;
    static const Color lighterGreen;
    static const Color lightestGreen;
    static const Color desaturatedGreen;

    /*
    // Ssea -- 135° hue not in LibTCOD named colors
    static const Color darkestSsea;
    static const Color darkerSsea;
    static const Color darkSsea;
    static const Color ssea;
    static const Color lightSsea;
    static const Color lighterSsea;
    static const Color lightestSsea;
    static const Color desaturatedSsea;
    */

    // Sea
    static const Color darkestSea;
    static const Color darkerSea;
    static const Color darkSea;
    static const Color sea;
    static const Color lightSea;
    static const Color lighterSea;
    static const Color lightestSea;
    static const Color desaturatedSea;

    // Turquoise
    static const Color darkestTurquoise;
    static const Color darkerTurquoise;
    static const Color darkTurquoise;
    static const Color turquoise;
    static const Color lightTurquoise;
    static const Color lighterTurquoise;
    static const Color lightestTurquoise;
    static const Color desaturatedTurquoise;

    // Cyan
    static const Color darkestCyan;
    static const Color darkerCyan;
    static const Color darkCyan;
    static const Color cyan;
    static const Color lightCyan;
    static const Color lighterCyan;
    static const Color lightestCyan;
    static const Color desaturatedCyan;

    // Sky
    static const Color darkestSky;
    static const Color darkerSky;
    static const Color darkSky;
    static const Color sky;
    static const Color lightSky;
    static const Color lighterSky;
    static const Color lightestSky;
    static const Color desaturatedSky;

    // Azure
    static const Color darkestAzure;
    static const Color darkerAzure;
    static const Color darkAzure;
    static const Color azure;
    static const Color lightAzure;
    static const Color lighterAzure;
    static const Color lightestAzure;
    static const Color desaturatedAzure;

    /*
    // Bblue -- 225° hue not in LibTCOD named colors
    static const Color darkestBblue;
    static const Color darkerBblue;
    static const Color darkBblue;
    static const Color bblue;
    static const Color lightBblue;
    static const Color lighterBblue;
    static const Color lightestBblue;
    static const Color desaturatedBblue;
    */

    // Blue
    static const Color darkestBlue;
    static const Color darkerBlue;
    static const Color darkBlue;
    static const Color blue;
    static const Color lightBlue;
    static const Color lighterBlue;
    static const Color lightestBlue;
    static const Color desaturatedBlue;

    // Han
    static const Color darkestHan;
    static const Color darkerHan;
    static const Color darkHan;
    static const Color han;
    static const Color lightHan;
    static const Color lighterHan;
    static const Color lightestHan;
    static const Color desaturatedHan;

    // Violet
    static const Color darkestViolet;
    static const Color darkerViolet;
    static const Color darkViolet;
    static const Color violet;
    static const Color lightViolet;
    static const Color lighterViolet;
    static const Color lightestViolet;
    static const Color desaturatedViolet;

    // Purple
    static const Color darkestPurple;
    static const Color darkerPurple;
    static const Color darkPurple;
    static const Color purple;
    static const Color lightPurple;
    static const Color lighterPurple;
    static const Color lightestPurple;
    static const Color desaturatedPurple;

    // Fuchsia
    static const Color darkestFuchsia;
    static const Color darkerFuchsia;
    static const Color darkFuchsia;
    static const Color fuchsia;
    static const Color lightFuchsia;
    static const Color lighterFuchsia;
    static const Color lightestFuchsia;
    static const Color desaturatedFuchsia;

    // Magenta
    static const Color darkestMagenta;
    static const Color darkerMagenta;
    static const Color darkMagenta;
    static const Color magenta;
    static const Color lightMagenta;
    static const Color lighterMagenta;
    static const Color lightestMagenta;
    static const Color desaturatedMagenta;

    // Pink
    static const Color darkestPink;
    static const Color darkerPink;
    static const Color darkPink;
    static const Color pink;
    static const Color lightPink;
    static const Color lighterPink;
    static const Color lightestPink;
    static const Color desaturatedPink;

    // Crimson
    static const Color darkestCrimson;
    static const Color darkerCrimson;
    static const Color darkCrimson;
    static const Color crimson;
    static const Color lightCrimson;
    static const Color lighterCrimson;
    static const Color lightestCrimson;
    static const Color desaturatedCrimson;

    // Other colors
    // Brass
    static const Color brass;
    // Copper
    static const Color copper;
    // Gold
    static const Color gold;
    // Silver
    static const Color silver;
    // Celadon
    static const Color celadon;
    // Peach
    static const Color peach;
  };
}

#endif
