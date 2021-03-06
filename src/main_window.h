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

#pragma once

#include "diceware.h"
#include <gtkmm/aboutdialog.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/frame.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/togglebutton.h>
#include <utility>
#include <vector>

class MainWindow : public Gtk::ApplicationWindow {
public:
  MainWindow();
  struct Settings {
    Diceware::Wordlist wordlist = Diceware::Wordlist::EFF;
    bool is_hyphen = false;
    bool is_space = false;
    bool is_random = false;
    int num_words = 8;
  };

protected:
  static const std::string SPECIAL_CHARS_;
  Gtk::Box box_container_;
  Gtk::Box box_wordlists_;
  Gtk::Box box_options_;
  Gtk::Box box_num_words_;
  Gtk::Box box_buttons_;

  Gtk::Frame frm_wordlists_;
  Gtk::Frame frm_options_;
  Gtk::Frame frm_num_words_;

  Gtk::CheckButton chk_hyphen_;
  Gtk::CheckButton chk_space_;
  Gtk::CheckButton chk_random_char_;

  // Signal connection handlers are needed
  // here because only one of hyphen or space
  // can be enabled and we may need to toggle the
  // status of one from the other. These are used
  // to temporarily block the signals.
  sigc::connection sig_hyphen_clicked_;
  sigc::connection sig_space_clicked_;

  Gtk::Button btn_generate_;
  Gtk::Button btn_copy_;
  Gtk::Button btn_quit_;

  Gtk::RadioButton rdo_eff_;
  Gtk::RadioButton rdo_diceware_;

  Gtk::Entry ent_password_;

  Gtk::AboutDialog about_dialog_;

  Diceware diceware_;

  std::vector<std::string> words_;
  std::pair<int, int> random_word_position_;

  Settings settings_;
  std::string config_file_;

  void InitializeConfigFilePath();
  void CreateHeaderBar();
  void InitializeLayout();
  void InitializeSignals();
  void UpdateDisplay();
  void InitializeAboutDialog();
  void ShowAboutDialog();
  bool LoadSettings();
  bool SaveSettings();

  void OnSelectWordlist(const Diceware::Wordlist wordlist);
  void OnChangeNumWords(const int num);
  void OnSelectHyphen();
  void OnSelectSpace();
  void OnSelectRandom();
  void InsertSpecialChar();
  void RemoveSpecialChar();
  void OnClickGenerate();
  void GenerateNewWords();
  std::string GetPassword();
  void OnClickCopy();
  void OnClipboardPaste(Gtk::SelectionData &selection_data, guint);
  void OnClipboardClear();
  void OnHide();
  void Quit();
};
