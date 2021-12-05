#!/bin/bash

function compile() {
  echo "compile" $1
  ./tools/shaderc --platform linux -p 120 --type vertex -o "./Game/data/shader/glsl/vs_$1.bin" -f "./shader/$1/vs.sc"
  ./tools/shaderc --platform linux -p 120 --type fragment -o "./Game/data/shader/glsl/fs_$1.bin" -f "./shader/$1/fs.sc"
  ./tools/shaderc --platform linux -p spirv --type vertex -o "./Game/data/shader/spirv/vs_$1.bin" -f "./shader/$1/vs.sc"
  ./tools/shaderc --platform linux -p spirv --type fragment -o "./Game/data/shader/spirv/fs_$1.bin" -f "./shader/$1/fs.sc"
}

if [ ! -d "./Game/data/shader" ]
then
  mkdir ./Game/data/shader
  mkdir ./Game/data/shader/glsl
  mkdir ./Game/data/shader/spirv
fi

compile renderer2dColor
compile renderer2dTexture


