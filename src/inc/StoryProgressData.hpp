#pragma once
#include <stdint.h>

namespace Story {
struct StoryProgress {
  uint16_t nowChapter;

  StoryProgress() : nowChapter(0) {}
} __attribute__((__packed__));
}  // namespace Story