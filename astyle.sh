#!/bin/sh

astyle --indent=spaces=2 --brackets=linux \
      --indent-labels --pad-oper --pad-paren-in --unpad-paren --pad-header \
      --keep-one-line-statements --convert-tabs \
      --indent-preprocessor --max-code-length=80 \
      `git status -uno -s | cut -d" " -f3 | egrep '\.h$|\.cpp$'`
