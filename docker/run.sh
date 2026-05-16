#!/usr/bin/env bash
# Usage:
#   ./run.sh shell                  - interactive shell inside container
#   ./run.sh build                  - normal build (Werror, optimized)
#   ./run.sh tsan <args...>         - clang+TSan build & run with given args
#   ./run.sh helgrind <args...>     - valgrind helgrind run
#   ./run.sh drd <args...>          - valgrind drd run
#   ./run.sh memcheck <args...>     - valgrind memcheck run
#   ./run.sh clean                  - fclean
#
# Example: ./run.sh helgrind 5 800 200 200

set -euo pipefail

cd "$(dirname "$0")"

SERVICE=philo
COMPOSE="docker compose"

ensure_up() {
    $COMPOSE up -d --build >/dev/null
}

ensure_up

cmd="${1:-shell}"
shift || true

case "$cmd" in
    shell)
        $COMPOSE exec "$SERVICE" /bin/bash
        ;;
    build)
        $COMPOSE exec "$SERVICE" bash -lc "make -C /work/philo re"
        ;;
    tsan)
        # ThreadSanitizer build via clang. Override CFLAGS to drop -Werror so
        # sanitizer instrumentation does not fail strict warnings.
        $COMPOSE exec "$SERVICE" bash -lc "
            set -e
            cd /work/philo
            make fclean >/dev/null
            make CC=clang CFLAGS='-Wall -Wextra -g -O1 -fsanitize=thread -fno-omit-frame-pointer -pthread'
            echo '--- running with TSan ---'
            TSAN_OPTIONS='halt_on_error=1 second_deadlock_stack=1' ./philo $*
        "
        ;;
    helgrind)
        $COMPOSE exec "$SERVICE" bash -lc "
            set -e
            cd /work/philo
            make >/dev/null
            valgrind --tool=helgrind --error-exitcode=42 --history-level=full ./philo $*
        "
        ;;
    drd)
        $COMPOSE exec "$SERVICE" bash -lc "
            set -e
            cd /work/philo
            make >/dev/null
            valgrind --tool=drd --error-exitcode=42 --exclusive-threshold=10000 --joinlist-threshold=10000 ./philo $*
        "
        ;;
    memcheck)
        $COMPOSE exec "$SERVICE" bash -lc "
            set -e
            cd /work/philo
            make >/dev/null
            valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-fds=yes --error-exitcode=42 ./philo $*
        "
        ;;
    clean)
        $COMPOSE exec "$SERVICE" bash -lc "make -C /work/philo fclean"
        ;;
    down)
        $COMPOSE down
        ;;
    *)
        echo "unknown command: $cmd" >&2
        echo "see top of $(basename "$0") for usage" >&2
        exit 1
        ;;
esac
