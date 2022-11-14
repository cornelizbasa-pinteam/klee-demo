#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 1 ]
then
    echo "Usage: $0 test.cpp"
    exit 1
fi

FILE="${1}"

KLEE_IMAGE="klee/klee:2.3"
RUN="docker run -w $(pwd) --ulimit stack=2024000 -v $(pwd):$(pwd) --rm ${KLEE_IMAGE}"

CLANG_BIN=/tmp/llvm-110-install_O_D_A/bin
CLANGXX="${RUN} ${CLANG_BIN}/clang++"

KLEE_INCLUDE=/home/klee/klee_src/include
KLEE_BUILD=/home/klee/klee_build
KLEE_BIN="${KLEE_BUILD}/bin"

KLEE="${RUN} ${KLEE_BIN}/klee"
KTEST="${RUN} ${KLEE_BIN}/ktest-tool"

${CLANGXX} -std=c++14 -O2 -DKLEE -g -emit-llvm -I"${KLEE_INCLUDE}" -c "${FILE}" -o "$(pwd)/${FILE%%.*}.bc"

set +e
${KLEE} --optimize --libc=uclibc --posix-runtime "$(pwd)/${FILE%%.*}.bc"
set -e

for err in klee-last/*.err; do
    if [ -f "${err}" ]; then
        echo "=== Input for ${err} ==="
        ${KTEST} "${err%%.*}.ktest"
    fi
done

