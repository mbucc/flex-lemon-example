lemon-parser-tutorial
=====================

[Lemon](http://www.hwaci.com/sw/lemon/) is a
replacement for bison and yacc, and is part the SQLite source tree.
It's uses a different grammar, is thread-safe, and is designed to run
inside long-running processes (ie not leak).

This repo started from David Wheeler's
([@theory](https://github.com/theory) C port of a [C++ shell
example](https://github.com/bskari/lemon-parser-tutorial) by
[@bskari](https://github.com/bskari).


To build it, run:

    make

Then to run it:

    ./shell
