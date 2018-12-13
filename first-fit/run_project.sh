#!/usr/bin/env bash

echo "Compiling exponential.c..."
gcc exponential.c -o exponential -lm
echo -e "Done\n\n"

echo "Compiling polynomial.c..."
gcc polynomial.c -o polynomial
echo -e "Done\n\n"

echo "Compiling input-generator.c..."
gcc input-generator.c -o input-generator
echo -e "Done\n\n"
