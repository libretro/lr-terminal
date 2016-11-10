#include "terminal_color.h"
#include "terminal_utils.h"
#include <algorithm>
#include <cmath>

namespace LRTerminal
{
  // Constructors
  Color::Color(): m_R(0u), m_G(0u), m_B(0u)
  {
  }

  Color::Color(uint8_t R, uint8_t G, uint8_t B): m_R(R), m_G(G), m_B(B)
  {
  }

  // Factory functions
  Color Color::fromRGB(uint8_t R, uint8_t G, uint8_t B)
  {
    return Color(R, G, B);
  }

  Color Color::fromHSV(float H, float S, float V)
  {
    Color ret;
    ret.setHSV(H, S, V);
    return ret;
  }

  Color Color::fromHSL(float H, float S, float L)
  {
    Color ret;
    ret.setHSL(H, S, L);
    return ret;
  }

  // Copy constructor
  Color::Color(const Color& that):
      m_R(that.m_R),
      m_G(that.m_G),
      m_B(that.m_B)
  {
  }

  // Operator =
  Color& Color::operator=(const Color& that)
  {
    m_R = that.m_R;
    m_G = that.m_G;
    m_B = that.m_B;
    return *this;
  }

  // Operator ==, !=
  bool Color::operator==(const Color& that) const
  {
    return (m_R == that.m_R)
        && (m_G == that.m_G)
        && (m_B == that.m_B);
  }

  bool Color::operator!=(const Color& that) const
  {
    return (m_R != that.m_R)
        || (m_G != that.m_G)
        || (m_B != that.m_B);
  }

  // Operator *
  uint8_t _multiplyColorComponents(const uint8_t a, const uint8_t b)
  {
    return static_cast<uint8_t>((static_cast<unsigned>(a) * static_cast<unsigned>(b)) / UINT8_MAX);
  }

  Color Color::operator*(const Color& other) const
  {
    uint8_t R = _multiplyColorComponents(m_R, other.m_R);
    uint8_t G = _multiplyColorComponents(m_G, other.m_G);
    uint8_t B = _multiplyColorComponents(m_B, other.m_B);
    //
    return Color(R, G, B);
  }

  uint8_t _scaleColorComponents(const uint8_t a, const float coeff)
  {
    return static_cast<uint8_t>(Utils::clamp(static_cast<int>(static_cast<float>(a) * coeff), 0, UINT8_MAX));
  }

  Color Color::operator*(const float scalar) const
  {
    uint8_t R = _scaleColorComponents(m_R, scalar);
    uint8_t G = _scaleColorComponents(m_G, scalar);
    uint8_t B = _scaleColorComponents(m_B, scalar);
    //
    return Color(R, G, B);
  }

  // Operator +, -
  uint8_t _addColorComponents(const uint8_t a, const uint8_t b)
  {
    return static_cast<uint8_t>(std::min((static_cast<int>(a) + static_cast<int>(b)), UINT8_MAX));
  }

  Color Color::operator+(const Color& other) const
  {
    uint8_t R = _addColorComponents(m_R, other.m_R);
    uint8_t G = _addColorComponents(m_G, other.m_G);
    uint8_t B = _addColorComponents(m_B, other.m_B);
    //
    return Color(R, G, B);
  }

  // Operator -
  uint8_t _substractColorComponents(const uint8_t a, const uint8_t b)
  {
    return static_cast<uint8_t>(std::max((static_cast<int>(a) - static_cast<int>(b)), 0));
  }

  Color Color::operator-(const Color& other) const
  {
    uint8_t R = _substractColorComponents(m_R, other.m_R);
    uint8_t G = _substractColorComponents(m_G, other.m_G);
    uint8_t B = _substractColorComponents(m_B, other.m_B);
    //
    return Color(R, G, B);
  }

  // Getters
  uint8_t Color::getRed(void) const
  {
    return m_R;
  }

  uint8_t Color::getGreen(void) const
  {
    return m_G;
  }

  uint8_t Color::getBlue(void) const
  {
    return m_B;
  }

  void Color::getRGB(uint8_t& R, uint8_t& G, uint8_t& B)
  {
    R = m_R;
    G = m_G;
    B = m_B;
  }

  // RGB -> HSV
  void Color::getHSV(float& H, float& S, float& V)
  {
    uint8_t MN = std::min(m_R, std::min(m_G, m_B));
    uint8_t MX = std::max(m_R, std::max(m_G, m_B));
    //
    //
    float mn = static_cast<float>(MN) / 255.0f;
    float mx = static_cast<float>(MX) / 255.0f;
    //
    float delta = mx - mn;
    float s = 0.0f;
    float h = 0.0f;
    if (mx > 0.0f)
    {
      s = delta / mx;
      //
      float r = static_cast<float>(m_R) / 255.0f;
      float g = static_cast<float>(m_G) / 255.0f;
      float b = static_cast<float>(m_B) / 255.0f;
      //
      if (MX == m_R)
      {
        h = (g - b) / delta;
      }
      else if (MX == m_G)
      {
        h = 2.0 + (b - r) / delta;
      }
      else // MX == m_B
      {
        h = 4.0 + (r - g) / delta;
      }
    }
    //
    V = 100.0 * mx;
    S = 100.0f * s;
    H = h * 60.0f;
    if (H < 0.0f)
    {
      H = H + 360.0f;
    }
  }

  // RGB -> HSL
  void Color::getHSL(float& H, float& S, float& L)
  {
    uint8_t MN = std::min(m_R, std::min(m_G, m_B));
    uint8_t MX = std::max(m_R, std::max(m_G, m_B));
    //
    //
    float mn = static_cast<float>(MN) / 255.0f;
    float mx = static_cast<float>(MX) / 255.0f;
    //
    float delta = mx - mn;
    float h = 0.0f;
    float s = 0.0f;
    float l = (mx + mn) / 2.0f;

    if (MX != MN) // delta != 0.0f
    {
      if (l <= 0.5)
      {
        s = delta / (mx + mn);
      }
      else
      {
        s = delta / (2.0f - mx - mn);
      }
      //
      float r = static_cast<float>(m_R) / 255.0f;
      float g = static_cast<float>(m_G) / 255.0f;
      float b = static_cast<float>(m_B) / 255.0f;
      //
      if (MX == m_R)
      {
        h = (g - b) / (6.0f * delta);
      }
      else if (MX == m_G)
      {
        h = (1.0f / 3.0f) + (b - r) / (6.0 * delta);
      }
      else // MX == m_B
      {
        h = (2.0f / 3.0f) + (r - g) / (6.0 * delta);
      }
      //
      if (h < 0.0f)
      {
        h = h + 1.0f;
      }
      if (h > 1.0f)
      {
        h = h - 1.0f;
      }
    }
    //
    H = 360.0f * h;
    S = 100.0f * s;
    L = 100.0f * l;
  }

  uint32_t Color::toXRGB(void) const
  {
    uint32_t red = m_R;
    uint32_t green = m_G;
    uint32_t blue = m_B;
    return ((red << 16u) | (green << 8u) | blue);
  }

  // Setters
  void Color::setRed(uint8_t R)
  {
    m_R = R;
  }

  void Color::setGreen(uint8_t G)
  {
    m_G = G;
  }

  void Color::setBlue(uint8_t B)
  {
    m_B = B;
  }

  void Color::setRGB(const uint8_t R, const uint8_t G, const uint8_t B)
  {
    m_R = R;
    m_G = G;
    m_B = B;
  }

  // HSV -> RGB
  void Color::setHSV(const float H, const float S, const float V)
  {
    // Clamp to limits
    float hr = Utils::clamp(fmodf(H, 360.0f), 0.0f, 360.0f) / 360.0f;
    float sr = Utils::clamp(S, 0.0f, 100.0f) / 100.0f;
    float vr = Utils::clamp(V, 0.0f, 100.0f) / 100.0f;
    //
    float r = vr;
    float g = vr;
    float b = vr;
    //
    if (sr > 0.0f)
    {
      float vH = fmodf(hr * 6.0f, 6.0f);
      int vI = static_cast<int>(floorf(vH));
      float v1 = vr * (1.0f - sr);
      float v2 = vr * (1.0f - sr * (vH - static_cast<float>(vI)));
      float v3 = vr * (1.0f - sr * (1.0f - vH + static_cast<float>(vI)));
      //
      switch (vI)
      {
        case 0:
          r = vr;
          g = v3;
          b = v1;
          break;
        case 1:
          r = v2;
          g = vr;
          b = v1;
          break;
        case 2:
          r = v1;
          g = vr;
          b = v3;
          break;
        case 3:
          r = v1;
          g = v2;
          b = vr;
          break;
        case 4:
          r = v3;
          g = v1;
          b = vr;
          break;
        default:
          r = vr;
          g = v1;
          b = v2;
          break;
      }
    }
    m_R = static_cast<uint8_t>(Utils::clamp(static_cast<int>(255.0f * r), 0, UINT8_MAX));
    m_G = static_cast<uint8_t>(Utils::clamp(static_cast<int>(255.0f * g), 0, UINT8_MAX));
    m_B = static_cast<uint8_t>(Utils::clamp(static_cast<int>(255.0f * b), 0, UINT8_MAX));
  }

  // HSL -> RGB
  // Helping function
  float hToRBG(float v1, float v2, float hr)
  {
    float vH = hr;
    if (hr < 0.0f)
    {
      vH = hr + 1.0f;
    }
    if (hr > 1.0f)
    {
      vH = hr - 1.0f;
    }
    //
    float res = 0.0f;
    if ((6.0f * vH) < 1.0f)
    {
      res = v1 + ((v2 - v1) * 6.0f * vH);
    }
    else if ((2.0f * vH) < 1.0f)
    {
      res = v2;
    }
    else if ((3.0f * vH) < 2.0f)
    {
      res = v1 + ((v2 - v1) * 6.0f * ((2.0f / 3.0f) - vH));
    }
    else
    {
      res = v1;
    }
    return res;
  }

  void Color::setHSL(const float H, const float S, const float L)
  {
    // Clamp to limits
    float hr = Utils::clamp(fmodf(H, 360.0f), 0.0f, 360.0f) / 360.0f;
    float sr = Utils::clamp(S, 0.0f, 100.0f) / 100.0f;
    float lr = Utils::clamp(L, 0.0f, 100.0f) / 100.0f;
    //
    float r = lr;
    float g = lr;
    float b = lr;
    //
    if (sr > 0.0f)
    {
      float v2 = 0.0f;
      if (lr < 0.5)
      {
        v2 = lr * (1.0 + sr);
      }
      else
      {
        v2 = (lr + sr) - (lr * sr);
      }
      float v1 = (2.0 * lr) - v2;
      //
      r = hToRBG(v1, v2, hr + (1.0f / 3.0f));
      g = hToRBG(v1, v2, hr);
      b = hToRBG(v1, v2, hr - (1.0f / 3.0f));
    }
    m_R = static_cast<uint8_t>(Utils::clamp(static_cast<int>(255.0f * r), 0, UINT8_MAX));
    m_G = static_cast<uint8_t>(Utils::clamp(static_cast<int>(255.0f * g), 0, UINT8_MAX));
    m_B = static_cast<uint8_t>(Utils::clamp(static_cast<int>(255.0f * b), 0, UINT8_MAX));
  }

  //
  // Shift Hue, Hue in grades
  void Color::shiftHueHSV(float HShift)
  {
    float H = 0.0f;
    float S = 0.0f;
    float V = 0.0f;
    getHSV(H, S, V);
    setHSV(H + HShift, S, V);
  }

  void Color::shiftHueHSL(float HShift)
  {
    float H = 0.0f;
    float S = 0.0f;
    float L = 0.0f;
    getHSL(H, S, L);
    setHSL(H + HShift, S, L);
  }

  // Scale colors
  void Color::scaleHSV(float sscale, float vscale)
  {
    float H = 0.0f;
    float S = 0.0f;
    float V = 0.0f;
    getHSV(H, S, V);
    setHSV(H, S * sscale, V * vscale);
  }

  void Color::scaleHSL(float sscale, float lscale)
  {
    float H = 0.0f;
    float S = 0.0f;
    float L = 0.0f;
    getHSL(H, S, L);
    setHSL(H, S * sscale, L * lscale);
  }

  // Interpolation/Extrapolation in RGB
  uint8_t _lerpColorComponents(const uint8_t a, const uint8_t b, float coeff)
  {
    float ret = Utils::lerp(static_cast<float>(a), static_cast<float>(b), coeff);
    return static_cast<uint8_t>(Utils::clamp(static_cast<int>(ret), 0, UINT8_MAX));
  }

  Color Color::lerp(const Color& a, const Color& b, const float coeff)
  {
    uint8_t R = _lerpColorComponents(a.m_R, b.m_R, coeff);
    uint8_t G = _lerpColorComponents(a.m_G, b.m_G, coeff);
    uint8_t B = _lerpColorComponents(a.m_B, b.m_B, coeff);
    //
    return Color(R, G, B);
  }

  // Lighten: max on each component
  Color Color::lighten(const Color& a, const Color& b)
  {
    uint8_t R = std::max(a.m_R, b.m_R);
    uint8_t G = std::max(a.m_G, b.m_G);
    uint8_t B = std::max(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Darken: min on each component
  Color Color::darken(const Color& a, const Color& b)
  {
    uint8_t R = std::min(a.m_R, b.m_R);
    uint8_t G = std::min(a.m_G, b.m_G);
    uint8_t B = std::min(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Screen: (1 - (1-a)*(1-b)) on each component
  uint8_t _screenColorComponents(const uint8_t a, const uint8_t b)
  {
    int ret = 255 - (((255 - static_cast<int>(a)) * (255 - static_cast<int>(b))) / 255);
    return static_cast<uint8_t>(Utils::clamp(ret, 0, UINT8_MAX));
  }

  Color Color::screen(const Color& a, const Color& b)
  {
    uint8_t R = _screenColorComponents(a.m_R, b.m_R);
    uint8_t G = _screenColorComponents(a.m_G, b.m_G);
    uint8_t B = _screenColorComponents(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Color Dodge: (b / (1-a)) on each component
  uint8_t _colorDodgeColorComponents(const uint8_t a, const uint8_t b)
  {
    int ret = 255;
    if (a < 255)
    {
      ret = (255 * static_cast<int>(b)) / (255 - static_cast<int>(a));
    }
    return static_cast<uint8_t>(Utils::clamp(ret, 0, UINT8_MAX));
  }

  Color Color::colorDodge(const Color& a, const Color& b)
  {
    uint8_t R = _colorDodgeColorComponents(a.m_R, b.m_R);
    uint8_t G = _colorDodgeColorComponents(a.m_G, b.m_G);
    uint8_t B = _colorDodgeColorComponents(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Color Burn: (1 - (1-a)/b) on each component
  uint8_t _colorBurnColorComponents(const uint8_t a, const uint8_t b)
  {
    int ret = 0;
    if (b > 0)
    {
      ret = 255 - ((255 * (255 - static_cast<int>(a))) / static_cast<int>(b));
    }
    return static_cast<uint8_t>(Utils::clamp(ret, 0, UINT8_MAX));
  }

  Color Color::colorBurn(const Color& a, const Color& b)
  {
    uint8_t R = _colorBurnColorComponents(a.m_R, b.m_R);
    uint8_t G = _colorBurnColorComponents(a.m_G, b.m_G);
    uint8_t B = _colorBurnColorComponents(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Burn: (a + b - 1) on each component
  uint8_t _burnColorComponents(const uint8_t a, const uint8_t b)
  {
    int ret = static_cast<int>(a) + static_cast<int>(b) - 255;
    return static_cast<uint8_t>(Utils::clamp(ret, 0, UINT8_MAX));
  }

  Color Color::burn(const Color& a, const Color& b)
  {
    uint8_t R = _burnColorComponents(a.m_R, b.m_R);
    uint8_t G = _burnColorComponents(a.m_G, b.m_G);
    uint8_t B = _burnColorComponents(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Overlay: ((b < 0.5) ? (2*a*b) : (1 - 2*(1-a)*(1-b))) on each component
  uint8_t _overlayColorComponents(const uint8_t a, const uint8_t b)
  {
    int ret = 0;
    if (b <= 128)
    {
      ret = (2 * static_cast<int>(a) * static_cast<int>(b)) / 255;
    }
    else
    {
      ret = 255 - (2 * (255 - static_cast<int>(a)) * (255 - static_cast<int>(b))) / 255;
    }
    return static_cast<uint8_t>(Utils::clamp(ret, 0, UINT8_MAX));
  }

  Color Color::overlay(const Color& a, const Color& b)
  {
    uint8_t R = _overlayColorComponents(a.m_R, b.m_R);
    uint8_t G = _overlayColorComponents(a.m_G, b.m_G);
    uint8_t B = _overlayColorComponents(a.m_B, b.m_B);
    //
    return Color(R, G, B);
  }

  // Named colors
  // Black & white
  const Color Color::black(0u, 0u, 0u);
  const Color Color::white(255u, 255u, 255u);

  // Grey
  const Color Color::darkestGrey(Color::fromHSL(0.0f, 0.0f, 12.5f));
  const Color Color::darkerGrey(Color::fromHSL(0.0f, 0.0f, 25.0f));
  const Color Color::darkGrey(Color::fromHSL(0.0f, 0.0f, 37.5f));
  const Color Color::grey(Color::fromHSL(0.0f, 0.0f, 50.0f));
  const Color Color::lightGrey(Color::fromHSL(0.0f, 0.0f, 62.5f));
  const Color Color::lighterGrey(Color::fromHSL(0.0f, 0.0f, 75.0f));
  const Color Color::lightestGrey(Color::fromHSL(0.0f, 0.0f, 87.5f));

  // Sepia
  const Color Color::darkestSepia(Color::fromHSL(36.0f, 33.0f, 12.5f));
  const Color Color::darkerSepia(Color::fromHSL(36.0f, 33.0f, 25.0f));
  const Color Color::darkSepia(Color::fromHSL(36.0f, 33.0f, 37.5f));
  const Color Color::sepia(Color::fromHSL(36.0f, 33.0f, 50.0f));
  const Color Color::lightSepia(Color::fromHSL(36.0f, 33.0f, 62.5f));
  const Color Color::lighterSepia(Color::fromHSL(36.0f, 33.0f, 75.0f));
  const Color Color::lightestSepia(Color::fromHSL(36.0f, 33.0f, 87.5f));

  // Red
  const Color Color::darkestRed(Color::fromHSL(0.0f, 100.0f, 12.5f));
  const Color Color::darkerRed(Color::fromHSL(0.0f, 100.0f, 25.0f));
  const Color Color::darkRed(Color::fromHSL(0.0f, 100.0f, 37.5f));
  const Color Color::red(Color::fromHSL(0.0f, 100.0f, 50.0f));
  const Color Color::lightRed(Color::fromHSL(0.0f, 100.0f, 62.5f));
  const Color Color::lighterRed(Color::fromHSL(0.0f, 100.0f, 75.0f));
  const Color Color::lightestRed(Color::fromHSL(0.0f, 100.0f, 87.5f));
  const Color Color::desaturatedRed(Color::fromHSL(0.0f, 33.0f, 37.5f));

  // Flame
  const Color Color::darkestFlame(Color::fromHSL(15.0f, 100.0f, 12.5f));
  const Color Color::darkerFlame(Color::fromHSL(15.0f, 100.0f, 25.0f));
  const Color Color::darkFlame(Color::fromHSL(15.0f, 100.0f, 37.5f));
  const Color Color::flame(Color::fromHSL(15.0f, 100.0f, 50.0f));
  const Color Color::lightFlame(Color::fromHSL(15.0f, 100.0f, 62.5f));
  const Color Color::lighterFlame(Color::fromHSL(15.0f, 100.0f, 75.0f));
  const Color Color::lightestFlame(Color::fromHSL(15.0f, 100.0f, 87.5f));
  const Color Color::desaturatedFlame(Color::fromHSL(15.0f, 33.0f, 37.5f));

  // Orange
  const Color Color::darkestOrange(Color::fromHSL(30.0f, 100.0f, 12.5f));
  const Color Color::darkerOrange(Color::fromHSL(30.0f, 100.0f, 25.0f));
  const Color Color::darkOrange(Color::fromHSL(30.0f, 100.0f, 37.5f));
  const Color Color::orange(Color::fromHSL(30.0f, 100.0f, 50.0f));
  const Color Color::lightOrange(Color::fromHSL(30.0f, 100.0f, 62.5f));
  const Color Color::lighterOrange(Color::fromHSL(30.0f, 100.0f, 75.0f));
  const Color Color::lightestOrange(Color::fromHSL(30.0f, 100.0f, 87.5f));
  const Color Color::desaturatedOrange(Color::fromHSL(30.0f, 33.0f, 37.5f));

  // Amber
  const Color Color::darkestAmber(Color::fromHSL(45.0f, 100.0f, 12.5f));
  const Color Color::darkerAmber(Color::fromHSL(45.0f, 100.0f, 25.0f));
  const Color Color::darkAmber(Color::fromHSL(45.0f, 100.0f, 37.5f));
  const Color Color::amber(Color::fromHSL(45.0f, 100.0f, 50.0f));
  const Color Color::lightAmber(Color::fromHSL(45.0f, 100.0f, 62.5f));
  const Color Color::lighterAmber(Color::fromHSL(45.0f, 100.0f, 75.0f));
  const Color Color::lightestAmber(Color::fromHSL(45.0f, 100.0f, 87.5f));
  const Color Color::desaturatedAmber(Color::fromHSL(45.0f, 33.0f, 37.5f));

  // Yellow
  const Color Color::darkestYellow(Color::fromHSL(60.0f, 100.0f, 12.5f));
  const Color Color::darkerYellow(Color::fromHSL(60.0f, 100.0f, 25.0f));
  const Color Color::darkYellow(Color::fromHSL(60.0f, 100.0f, 37.5f));
  const Color Color::yellow(Color::fromHSL(60.0f, 100.0f, 50.0f));
  const Color Color::lightYellow(Color::fromHSL(60.0f, 100.0f, 62.5f));
  const Color Color::lighterYellow(Color::fromHSL(60.0f, 100.0f, 75.0f));
  const Color Color::lightestYellow(Color::fromHSL(60.0f, 100.0f, 87.5f));
  const Color Color::desaturatedYellow(Color::fromHSL(60.0f, 33.0f, 37.5f));

  // Lime
  const Color Color::darkestLime(Color::fromHSL(75.0f, 100.0f, 12.5f));
  const Color Color::darkerLime(Color::fromHSL(75.0f, 100.0f, 25.0f));
  const Color Color::darkLime(Color::fromHSL(75.0f, 100.0f, 37.5f));
  const Color Color::lime(Color::fromHSL(75.0f, 100.0f, 50.0f));
  const Color Color::lightLime(Color::fromHSL(75.0f, 100.0f, 62.5f));
  const Color Color::lighterLime(Color::fromHSL(75.0f, 100.0f, 75.0f));
  const Color Color::lightestLime(Color::fromHSL(75.0f, 100.0f, 87.5f));
  const Color Color::desaturatedLime(Color::fromHSL(75.0f, 33.0f, 37.5f));

  // Chartreuse
  const Color Color::darkestChartreuse(Color::fromHSL(90.0f, 100.0f, 12.5f));
  const Color Color::darkerChartreuse(Color::fromHSL(90.0f, 100.0f, 25.0f));
  const Color Color::darkChartreuse(Color::fromHSL(90.0f, 100.0f, 37.5f));
  const Color Color::chartreuse(Color::fromHSL(90.0f, 100.0f, 50.0f));
  const Color Color::lightChartreuse(Color::fromHSL(90.0f, 100.0f, 62.5f));
  const Color Color::lighterChartreuse(Color::fromHSL(90.0f, 100.0f, 75.0f));
  const Color Color::lightestChartreuse(Color::fromHSL(90.0f, 100.0f, 87.5f));
  const Color Color::desaturatedChartreuse(Color::fromHSL(90.0f, 33.0f, 37.5f));

  /*
  // Ggreen -- 105° hue not in LibTCOD named colors
  const Color Color::darkestGgreen(Color::fromHSL(105.0f, 100.0f, 12.5f));
  const Color Color::darkerGgreen(Color::fromHSL(105.0f, 100.0f, 25.0f));
  const Color Color::darkGgreen(Color::fromHSL(105.0f, 100.0f, 37.5f));
  const Color Color::ggreen(Color::fromHSL(105.0f, 100.0f, 50.0f));
  const Color Color::lightGgreen(Color::fromHSL(105.0f, 100.0f, 62.5f));
  const Color Color::lighterGgreen(Color::fromHSL(105.0f, 100.0f, 75.0f));
  const Color Color::lightestGgreen(Color::fromHSL(105.0f, 100.0f, 87.5f));
  const Color Color::desaturatedGgreen(Color::fromHSL(105.0f, 33.0f, 37.5f));
  */

  // Green
  const Color Color::darkestGreen(Color::fromHSL(120.0f, 100.0f, 12.5f));
  const Color Color::darkerGreen(Color::fromHSL(120.0f, 100.0f, 25.0f));
  const Color Color::darkGreen(Color::fromHSL(120.0f, 100.0f, 37.5f));
  const Color Color::green(Color::fromHSL(120.0f, 100.0f, 50.0f));
  const Color Color::lightGreen(Color::fromHSL(120.0f, 100.0f, 62.5f));
  const Color Color::lighterGreen(Color::fromHSL(120.0f, 100.0f, 75.0f));
  const Color Color::lightestGreen(Color::fromHSL(120.0f, 100.0f, 87.5f));
  const Color Color::desaturatedGreen(Color::fromHSL(120.0f, 33.0f, 37.5f));

  /*
  // Ssea -- 135° hue not in LibTCOD named colors
  const Color Color::darkestSsea(Color::fromHSL(135.0f, 100.0f, 12.5f));
  const Color Color::darkerSsea(Color::fromHSL(135.0f, 100.0f, 25.0f));
  const Color Color::darkSsea(Color::fromHSL(135.0f, 100.0f, 37.5f));
  const Color Color::ssea(Color::fromHSL(135.0f, 100.0f, 50.0f));
  const Color Color::lightSsea(Color::fromHSL(135.0f, 100.0f, 62.5f));
  const Color Color::lighterSsea(Color::fromHSL(135.0f, 100.0f, 75.0f));
  const Color Color::lightestSsea(Color::fromHSL(135.0f, 100.0f, 87.5f));
  const Color Color::desaturatedSsea(Color::fromHSL(135.0f, 33.0f, 37.5f));
  */

  // Sea
  const Color Color::darkestSea(Color::fromHSL(150.0f, 100.0f, 12.5f));
  const Color Color::darkerSea(Color::fromHSL(150.0f, 100.0f, 25.0f));
  const Color Color::darkSea(Color::fromHSL(150.0f, 100.0f, 37.5f));
  const Color Color::sea(Color::fromHSL(150.0f, 100.0f, 50.0f));
  const Color Color::lightSea(Color::fromHSL(150.0f, 100.0f, 62.5f));
  const Color Color::lighterSea(Color::fromHSL(150.0f, 100.0f, 75.0f));
  const Color Color::lightestSea(Color::fromHSL(150.0f, 100.0f, 87.5f));
  const Color Color::desaturatedSea(Color::fromHSL(150.0f, 33.0f, 37.5f));

  // Turquoise
  const Color Color::darkestTurquoise(Color::fromHSL(165.0f, 100.0f, 12.5f));
  const Color Color::darkerTurquoise(Color::fromHSL(165.0f, 100.0f, 25.0f));
  const Color Color::darkTurquoise(Color::fromHSL(165.0f, 100.0f, 37.5f));
  const Color Color::turquoise(Color::fromHSL(165.0f, 100.0f, 50.0f));
  const Color Color::lightTurquoise(Color::fromHSL(165.0f, 100.0f, 62.5f));
  const Color Color::lighterTurquoise(Color::fromHSL(165.0f, 100.0f, 75.0f));
  const Color Color::lightestTurquoise(Color::fromHSL(165.0f, 100.0f, 87.5f));
  const Color Color::desaturatedTurquoise(Color::fromHSL(165.0f, 33.0f, 37.5f));

  // Cyan
  const Color Color::darkestCyan(Color::fromHSL(180.0f, 100.0f, 12.5f));
  const Color Color::darkerCyan(Color::fromHSL(180.0f, 100.0f, 25.0f));
  const Color Color::darkCyan(Color::fromHSL(180.0f, 100.0f, 37.5f));
  const Color Color::cyan(Color::fromHSL(180.0f, 100.0f, 50.0f));
  const Color Color::lightCyan(Color::fromHSL(180.0f, 100.0f, 62.5f));
  const Color Color::lighterCyan(Color::fromHSL(180.0f, 100.0f, 75.0f));
  const Color Color::lightestCyan(Color::fromHSL(180.0f, 100.0f, 87.5f));
  const Color Color::desaturatedCyan(Color::fromHSL(180.0f, 33.0f, 37.5f));

  // Sky
  const Color Color::darkestSky(Color::fromHSL(195.0f, 100.0f, 12.5f));
  const Color Color::darkerSky(Color::fromHSL(195.0f, 100.0f, 25.0f));
  const Color Color::darkSky(Color::fromHSL(195.0f, 100.0f, 37.5f));
  const Color Color::sky(Color::fromHSL(195.0f, 100.0f, 50.0f));
  const Color Color::lightSky(Color::fromHSL(195.0f, 100.0f, 62.5f));
  const Color Color::lighterSky(Color::fromHSL(195.0f, 100.0f, 75.0f));
  const Color Color::lightestSky(Color::fromHSL(195.0f, 100.0f, 87.5f));
  const Color Color::desaturatedSky(Color::fromHSL(195.0f, 33.0f, 37.5f));

  // Azure
  const Color Color::darkestAzure(Color::fromHSL(210.0f, 100.0f, 12.5f));
  const Color Color::darkerAzure(Color::fromHSL(210.0f, 100.0f, 25.0f));
  const Color Color::darkAzure(Color::fromHSL(210.0f, 100.0f, 37.5f));
  const Color Color::azure(Color::fromHSL(210.0f, 100.0f, 50.0f));
  const Color Color::lightAzure(Color::fromHSL(210.0f, 100.0f, 62.5f));
  const Color Color::lighterAzure(Color::fromHSL(210.0f, 100.0f, 75.0f));
  const Color Color::lightestAzure(Color::fromHSL(210.0f, 100.0f, 87.5f));
  const Color Color::desaturatedAzure(Color::fromHSL(210.0f, 33.0f, 37.5f));

  /*
  // Bblue -- 225° hue not in LibTCOD named colors
  const Color Color::darkestBblue(Color::fromHSL(225.0f, 100.0f, 12.5f));
  const Color Color::darkerBblue(Color::fromHSL(225.0f, 100.0f, 25.0f));
  const Color Color::darkBblue(Color::fromHSL(225.0f, 100.0f, 37.5f));
  const Color Color::bblue(Color::fromHSL(225.0f, 100.0f, 50.0f));
  const Color Color::lightBblue(Color::fromHSL(225.0f, 100.0f, 62.5f));
  const Color Color::lighterBblue(Color::fromHSL(225.0f, 100.0f, 75.0f));
  const Color Color::lightestBblue(Color::fromHSL(225.0f, 100.0f, 87.5f));
  const Color Color::desaturatedBblue(Color::fromHSL(225.0f, 33.0f, 37.5f));
  */

  // Blue
  const Color Color::darkestBlue(Color::fromHSL(240.0f, 100.0f, 12.5f));
  const Color Color::darkerBlue(Color::fromHSL(240.0f, 100.0f, 25.0f));
  const Color Color::darkBlue(Color::fromHSL(240.0f, 100.0f, 37.5f));
  const Color Color::blue(Color::fromHSL(240.0f, 100.0f, 50.0f));
  const Color Color::lightBlue(Color::fromHSL(240.0f, 100.0f, 62.5f));
  const Color Color::lighterBlue(Color::fromHSL(240.0f, 100.0f, 75.0f));
  const Color Color::lightestBlue(Color::fromHSL(240.0f, 100.0f, 87.5f));
  const Color Color::desaturatedBlue(Color::fromHSL(240.0f, 33.0f, 37.5f));

  // Han
  const Color Color::darkestHan(Color::fromHSL(255.0f, 100.0f, 12.5f));
  const Color Color::darkerHan(Color::fromHSL(255.0f, 100.0f, 25.0f));
  const Color Color::darkHan(Color::fromHSL(255.0f, 100.0f, 37.5f));
  const Color Color::han(Color::fromHSL(255.0f, 100.0f, 50.0f));
  const Color Color::lightHan(Color::fromHSL(255.0f, 100.0f, 62.5f));
  const Color Color::lighterHan(Color::fromHSL(255.0f, 100.0f, 75.0f));
  const Color Color::lightestHan(Color::fromHSL(255.0f, 100.0f, 87.5f));
  const Color Color::desaturatedHan(Color::fromHSL(255.0f, 33.0f, 37.5f));

  // Violet
  const Color Color::darkestViolet(Color::fromHSL(270.0f, 100.0f, 12.5f));
  const Color Color::darkerViolet(Color::fromHSL(270.0f, 100.0f, 25.0f));
  const Color Color::darkViolet(Color::fromHSL(270.0f, 100.0f, 37.5f));
  const Color Color::violet(Color::fromHSL(270.0f, 100.0f, 50.0f));
  const Color Color::lightViolet(Color::fromHSL(270.0f, 100.0f, 62.5f));
  const Color Color::lighterViolet(Color::fromHSL(270.0f, 100.0f, 75.0f));
  const Color Color::lightestViolet(Color::fromHSL(270.0f, 100.0f, 87.5f));
  const Color Color::desaturatedViolet(Color::fromHSL(270.0f, 33.0f, 37.5f));

  // Purple
  const Color Color::darkestPurple(Color::fromHSL(285.0f, 100.0f, 12.5f));
  const Color Color::darkerPurple(Color::fromHSL(285.0f, 100.0f, 25.0f));
  const Color Color::darkPurple(Color::fromHSL(285.0f, 100.0f, 37.5f));
  const Color Color::purple(Color::fromHSL(285.0f, 100.0f, 50.0f));
  const Color Color::lightPurple(Color::fromHSL(285.0f, 100.0f, 62.5f));
  const Color Color::lighterPurple(Color::fromHSL(285.0f, 100.0f, 75.0f));
  const Color Color::lightestPurple(Color::fromHSL(285.0f, 100.0f, 87.5f));
  const Color Color::desaturatedPurple(Color::fromHSL(285.0f, 33.0f, 37.5f));

  // Fuchsia
  const Color Color::darkestFuchsia(Color::fromHSL(300.0f, 100.0f, 12.5f));
  const Color Color::darkerFuchsia(Color::fromHSL(300.0f, 100.0f, 25.0f));
  const Color Color::darkFuchsia(Color::fromHSL(300.0f, 100.0f, 37.5f));
  const Color Color::fuchsia(Color::fromHSL(300.0f, 100.0f, 50.0f));
  const Color Color::lightFuchsia(Color::fromHSL(300.0f, 100.0f, 62.5f));
  const Color Color::lighterFuchsia(Color::fromHSL(300.0f, 100.0f, 75.0f));
  const Color Color::lightestFuchsia(Color::fromHSL(300.0f, 100.0f, 87.5f));
  const Color Color::desaturatedFuchsia(Color::fromHSL(300.0f, 33.0f, 37.5f));

  // Magenta
  const Color Color::darkestMagenta(Color::fromHSL(315.0f, 100.0f, 12.5f));
  const Color Color::darkerMagenta(Color::fromHSL(315.0f, 100.0f, 25.0f));
  const Color Color::darkMagenta(Color::fromHSL(315.0f, 100.0f, 37.5f));
  const Color Color::magenta(Color::fromHSL(315.0f, 100.0f, 50.0f));
  const Color Color::lightMagenta(Color::fromHSL(315.0f, 100.0f, 62.5f));
  const Color Color::lighterMagenta(Color::fromHSL(315.0f, 100.0f, 75.0f));
  const Color Color::lightestMagenta(Color::fromHSL(315.0f, 100.0f, 87.5f));
  const Color Color::desaturatedMagenta(Color::fromHSL(315.0f, 33.0f, 37.5f));

  // Pink
  const Color Color::darkestPink(Color::fromHSL(330.0f, 100.0f, 12.5f));
  const Color Color::darkerPink(Color::fromHSL(330.0f, 100.0f, 25.0f));
  const Color Color::darkPink(Color::fromHSL(330.0f, 100.0f, 37.5f));
  const Color Color::pink(Color::fromHSL(330.0f, 100.0f, 50.0f));
  const Color Color::lightPink(Color::fromHSL(330.0f, 100.0f, 62.5f));
  const Color Color::lighterPink(Color::fromHSL(330.0f, 100.0f, 75.0f));
  const Color Color::lightestPink(Color::fromHSL(330.0f, 100.0f, 87.5f));
  const Color Color::desaturatedPink(Color::fromHSL(330.0f, 33.0f, 37.5f));

  // Crimson
  const Color Color::darkestCrimson(Color::fromHSL(345.0f, 100.0f, 12.5f));
  const Color Color::darkerCrimson(Color::fromHSL(345.0f, 100.0f, 25.0f));
  const Color Color::darkCrimson(Color::fromHSL(345.0f, 100.0f, 37.5f));
  const Color Color::crimson(Color::fromHSL(345.0f, 100.0f, 50.0f));
  const Color Color::lightCrimson(Color::fromHSL(345.0f, 100.0f, 62.5f));
  const Color Color::lighterCrimson(Color::fromHSL(345.0f, 100.0f, 75.0f));
  const Color Color::lightestCrimson(Color::fromHSL(345.0f, 100.0f, 87.5f));
  const Color Color::desaturatedCrimson(Color::fromHSL(345.0f, 33.0f, 37.5f));

  // Other colors
  // Brass
  const Color Color::brass(Color::fromHSL(35.0f, 45.0f, 55.0f));
  // Copper
  const Color Color::copper(Color::fromHSL(10.0f, 37.5f, 62.5f));
  // Gold
  const Color Color::gold(Color::fromHSL(50.0f, 100.0f, 45.0f));
  // Silver
  const Color Color::silver(Color::fromHSL(0.0f, 0.0f, 80.0f));
  // Celadon
  const Color Color::celadon(Color::fromHSL(120.0f, 100.0f, 85.0f));
  // Peach
  const Color Color::peach(Color::fromHSL(15.0f, 100.0f, 75.0f));
}
