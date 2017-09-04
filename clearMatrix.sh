#!/bin/sh

find ./matrix -name "*.bc" | xargs rm
find ./matrix -name "*.o" | xargs rm
find ./matrix -name "*.js" | xargs rm
find ./matrix -name "*.html" | xargs rm
find ./matrix -name "*.mem" | xargs rm
