#pragma once

using MouseCode = uint16_t;

namespace Mouse {
enum : MouseCode {
  // From sfml.h
  Left,     //!< The left mouse button
  Right,    //!< The right mouse button
  Middle,   //!< The middle (wheel) mouse button
  XButton1, //!< The first extra mouse button
  XButton2, //!< The second extra mouse button

  ButtonCount //!< Keep last -- the total number of mouse buttons
};
}
