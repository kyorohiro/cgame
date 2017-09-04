#!/bin/sh

find ./examples -name "*.bc" | xargs rm
find ./examples -name "*.o" | xargs rm
find ./examples -name "*.js" | xargs rm
find ./examples -name "*.html" | xargs rm
find ./examples -name "*.mem" | xargs rm
