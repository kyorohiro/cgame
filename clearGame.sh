#!/bin/sh

find ./app -name "*.bc" | xargs rm
find ./app -name "*.o" | xargs rm
find ./app -name "*.js" | xargs rm
find ./app -name "*.html" | xargs rm
find ./app -name "*.mem" | xargs rm

find ./game -name "*.bc" | xargs rm
find ./game -name "*.o" | xargs rm
find ./game -name "*.js" | xargs rm
find ./game -name "*.html" | xargs rm
find ./game -name "*.mem" | xargs rm
