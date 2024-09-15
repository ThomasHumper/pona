<p align="center">
	<h1 align="center">Pona ✍️</h2>
	<p align="center">Another terminal based text editor written in C++ 💻</p>
</p>
<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=7aca00"/>
	</a>
	<a href="https://github.com/LordOfTrident/pona/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/pona?color=0088ff"/>
	</a>
	<a href="https://github.com/LordOfTrident/pona/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/pona?color=0088ff"/>
	</a>
	<br><br><br>
	<img width="600px" src="res/screenshots.png"/>
</p>

## 📋 Table of contents
* [Introduction](#introduction)
* [Features](#features)
* [Bugs](#bugs)
* [Dependencies](#dependencies)
* [Make](#make)

## 📝 Introduction
Pona is a [C++](https://en.wikipedia.org/wiki/C%2B%2B)-based [terminal](https://en.wikipedia.org/wiki/Terminal_emulator) [text editor](https://en.wikipedia.org/wiki/Text_editor) designed for [Linux](https://en.wikipedia.org/wiki/Linux). Unlike my previous editor, [tr-ed](https://github.com/LordOfTrident/trident-editor), Pona is focused on simplicity, speed, and practicality. For help using the editor, press Ctrl+H while inside the editor.

## 🌟 Features
- [X] Basic text editing 📝
- [X] Scrolling (horizontal & vertical) 🖱️
- [X] Ruler 📏
- [X] Scrollbar 📜
- [X] File input/output 📂
- [X] Tabs 🗂️
- [X] Config files ⚙️
- [X] Themes 🎨
- [X] Command line input 🖥️
- [X] Mouse input 🖱️
- [X] Text selection ✂️
- [X] Copy/cut/paste 📋
- [X] Find and replace 🔍
- [ ] Build and run commands 🔨 (In Progress)
- [ ] Syntax highlighting 🎨 (In Progress)
- [ ] Lua plugins 🧩 (In Progress)

## 🐞 Bugs
- Cursor alignment issue: If the current line contains tabs and you click at the end of the line, the cursor will be offset to the left by `tab size * tabs count`.

If you encounter any other bugs, please report them by opening an issue in the repository.

## 📦 Dependencies
- [ncurses](https://en.wikipedia.org/wiki/Ncurses) - for terminal handling
- [xclip](https://github.com/astrand/xclip) - for clipboard interaction

## ⚙️ Make
To build the project, run `make all` to see all the available make rules, or just `make` to compile a static binary.
