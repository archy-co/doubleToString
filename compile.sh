#!/bin/bash -x
# Use to print each step: #!/bin/bash -x
#
# Example script -- boilerplate to automate compilation (and, possibly, execution) the lab project.
#

set -o errexit
set -o nounset
set -o pipefail

debug_build=true
optimize_build=false
remove_dirs=false
install_prefix=".."

while [[ $# -gt 0 ]]; do
  case $1 in
  -I  | --install_prefix)
    if [ "$2" -eq "$2" ] 2>/dev/null; then
      install_prefix=$2
      shift 2
    else
      echo "Option --install_prefix requires an numerical argument." >&2
      exit 1
    fi
    ;;
  -D | --debug-build)
    debug_build=true
    shift
    ;;
  -d | --no-debug-build)
    debug_build=false
    shift
    ;;
  -O | --optimize-build)
    optimize_build=true
    shift
    ;;
  -o | --no-optimize-build)
    optimize_build=false
    shift
    ;;
  -R | --remove-build-dirs)
    remove_dirs=true
    shift
    ;;
  -h | --help)
    echo "Usage: ./start.sh [options]
  Options:
    -h      --help                  Show help message.
    -O      --optimize-build        Compile with optimization before executing.
    -o      --no-optimize-build     Compile without optimization before executing.
    -D      --debug-build           Compile with debug options.
    -d      --no-debug-build        Compile without debug options.
    -I      --install_prefix        Installation path.
    -R      --remove-build-dirs     Remove build dirs after the install."
    exit 0
    ;;
  \?)
    echo "Invalid option: -$OPTARG" >&2
    exit 1
    ;;
  :)
    echo "Option -$OPTARG requires an numerical argument." >&2
    exit 1
    ;;
  *)
    break
    ;;
  esac
done


if [[ "$debug_build" == true ]]; then
  mkdir -p ./cmake-build-debug
  (
    pushd ./cmake-build-debug > /dev/null || exit 1
    echo Compiling...
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX="${install_prefix}" .. || exit 1
    cmake --build . || exit 1
    cmake --install . || exit 1
    popd
  )
fi

if [[ "$optimize_build" == true ]]; then
  mkdir -p ./cmake-build-release
  (
    pushd ./cmake-build-release >/dev/null || exit 1
    echo Compiling...
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="${install_prefix}" .. || exit 1
    cmake --build . || exit 1
    cmake --install . || exit 1
    popd
  )
fi

if [[ "$remove_dirs" == true ]]; then
  rm -rf ./cmake-build-debug ./cmake-build-release
fi
