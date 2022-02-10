#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/catdev/repos/AEC3/iOS
  make -f /Users/catdev/repos/AEC3/iOS/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/catdev/repos/AEC3/iOS
  make -f /Users/catdev/repos/AEC3/iOS/CMakeScripts/ReRunCMake.make
fi

