SHADERC = "./tools/shaderc"

OUT_DIR = "./Game/data/shader"
IN_DIR = "./shader"

NAME = "cubes"

OUT = "${OUT_DIR}/glsl/vs_${NAME}.bin"
IN = "${IN_DIR}/vs_${NAME}.sc"

all: cubes.sc

%.sc: ${OUT_DIR}/glsl/vs_%.bin ${OUT_DIR}/glsl/fs_%.bin
	@echo $@

${OUT_DIR}/glsl/vs_%.bin:
	${SHADERC} --platform linux -p 120 --type vertex -o $@ -f ${IN_DIR}/vs_$*.sc

${OUT_DIR}/glsl/fs_%.bin:
	${SHADERC} --platform linux -p 120 --type fragment -o $@ -f ${IN_DIR}/fs_$*.sc