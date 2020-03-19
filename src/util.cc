// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "util.h"
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

std::string util::GetShareDir() {
  std::string exe_path;
  std::filesystem::path p{"/proc/self/exe"};

  if (std::filesystem::exists(p) && std::filesystem::is_symlink(p)) {
    exe_path = std::filesystem::read_symlink(p);
  } else {
    // Default path, ideally shouldn't come here.
    exe_path = "/usr/bin/executable";
  }

  auto exe_dir = exe_path.substr(0, exe_path.rfind('/'));
  exe_dir = exe_dir.substr(0, exe_dir.rfind('/'));
  return exe_dir + "/share/diceware_generator";
}

std::string util::GetConfigDir() {
  std::string home_dir;
  home_dir = getenv("HOME");
  if (home_dir.empty()) {
    home_dir = getpwuid(getuid())->pw_dir;
  }
  auto config_dir = home_dir + "/.config/diceware_generator";
  std::filesystem::create_directories(config_dir);
  return config_dir;
}
