#!/bin/bash

if ! command -v magick &> /dev/null; then
    echo "error: ImageMagick (magick) is not installed."
    exit 1
fi

if [[ $# -ne 2 ]]; then
    echo "usage: $0 <input_image> <output_image>"
    exit 1
fi

INPUT="$1"
OUTPUT="$2"

if [[ ! -f "$INPUT" ]]; then
    echo "error: input image does not exist: $INPUT"
    exit 1
fi

magick "$INPUT" "$OUTPUT"
rm -f "$INPUT"