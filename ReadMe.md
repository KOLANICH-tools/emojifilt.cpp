emojifilt.cpp [![Unlicensed work](https://raw.githubusercontent.com/unlicense/unlicense.org/master/static/favicon.png)](https://unlicense.org/)
=============
~~[![GitHub Actions](https://github.com/KOLANICH-tools/emojifilt.cpp/workflows/CI/badge.svg)](https://github.com/KOLANICH-tools/emojifilt.cpp/actions/)~~
[![Libraries.io Status](https://img.shields.io/librariesio/github/KOLANICH-tools/emojifilt.cpp.svg)](https://libraries.io/github/KOLANICH-tools/emojifilt.cpp)

A tool to replace emoji slugs (i. e. `:lock:`) with actual emoji (i. e. `🔒`) within text files.

## Rationale
Some Markdown sources on GitHub (`ReadMe`s, issues texts, comments, etc.) have emoji inside them in the form of ASCII slugs enclosed in `:`. It is inconvenient to read them in that form. This tool replaces them with actual emoji, so you should be able to see them within a text editor.

## Usage

```bash
emojifilt < ../a.md > ../b.md
```

should do the job, given the emoji database is situated in `./emoji.mo`.

## Emoji database

Emoji database is stored within a `mo` translation file (in fact, a key-value store for strings) for `libintl`/`gettext`. The key is the emoji abbreviation, the value is the emoji sequence. You can download [a pregenerated one (2023-02-06)](https://github.com/KOLANICH-tools/emojifilt.cpp/files/10667460/emoji.zip) (merged from different sources, see the license file inside the archive), or you can generate an own fresh one with [the python-based tool](https://codeberg.org/KOLANICH-tools/emojiSlugMappingGen.py).

## Build and installation
We use [CPack](https://cmake.org/cmake/help/latest/module/CPack.html) to generate native packages for your package manager.

* Modern versions of clang/gcc are recommended as compilers. Modern versions of CMake are recommended as the build system.
* Build and install https://codeberg.org/KOLANICH-libs/libmo.cpp - a library for looking up values in `libintl`/`gettext` `mo` translation files. Since it seems `libintl`/`gettext` don't allow to do hashtable lookup using the concrete file, we use an own lib for it.
* If you build for Windows, build and install a package for [my fork of `whereami`](https://github.com/KOLANICH-libs/whereami/tree/cmake) (the difference to the original is packaging using CPack). This is required: Windows apps don't follow FHS and for it the app is meant to be portable.
* Build and install a package for [CTRE](https://github.com/hanickadot/compile-time-regular-expressions) - a library for generating parsers for regular grammars in compile time. It's optional, if it is unavailable, the tool will use `std::regex`.
* Then build and install this package.
* Generate the database of mapping emoji slugs to code point sequences using [`emojiSlugMappingGen`](https://codeberg.org/KOLANICH-tools/emojiSlugMappingGen.py) tool and save it to `/usr/share/emojifilt/emoji.mo` tool: `python3 -m emojiSlugMappingGen > emoji.mo && sudo fakeroot cp ./emoji.mo /usr/share/emojifilt/emoji.mo` .
* The tool is ready to be used.

## Related projects
* https://github.com/alexandrevicenzi/emojis - an analogue in Python
* https://github.com/bsolomon1124/demoji - a tool doing the reverse transformation in Python
