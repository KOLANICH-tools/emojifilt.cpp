emojifilt.cpp [![Unlicensed work](https://raw.githubusercontent.com/unlicense/unlicense.org/master/static/favicon.png)](https://unlicense.org/)
=============
~~[![GitHub Actions](https://github.com/KOLANICH-tools/emojifilt.cpp/workflows/CI/badge.svg)](https://github.com/KOLANICH-tools/emojifilt.cpp/actions/)~~
[![Libraries.io Status](https://img.shields.io/librariesio/github/KOLANICH-tools/emojifilt.cpp.svg)](https://libraries.io/github/KOLANICH-tools/emojifilt.cpp)

**We have moved to https://codeberg.org/KOLANICH-tools/emojifilt.cpp, grab new versions there.**

Under the disguise of "better security" Micro$oft-owned GitHub has [discriminated users of 1FA passwords](https://github.blog/2023-03-09-raising-the-bar-for-software-security-github-2fa-begins-march-13/) while having commercial interest in success of [FIDO 1FA specifications](https://fidoalliance.org/specifications/download/) and [Windows Hello implementation](https://support.microsoft.com/en-us/windows/passkeys-in-windows-301c8944-5ea2-452b-9886-97e4d2ef4422) which [it promotes as a replacement for passwords](https://github.blog/2023-07-12-introducing-passwordless-authentication-on-github-com/). It will result in dire consequencies and is competely inacceptable, [read why](https://codeberg.org/KOLANICH/Fuck-GuanTEEnomo).

If you don't want to participate in harming yourself, it is recommended to follow the lead and migrate somewhere away of GitHub and Micro$oft. Here is [the list of alternatives and rationales to do it](https://github.com/orgs/community/discussions/49869). If they delete the discussion, there are certain well-known places where you can get a copy of it. [Read why you should also leave GitHub](https://codeberg.org/KOLANICH/Fuck-GuanTEEnomo).

---

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
