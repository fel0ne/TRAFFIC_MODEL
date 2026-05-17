
if [ z "$1" ]; then
    echo "Ошибка: Не указан файл конфигурации!"
    echo "Использование: $0 <путь_к_файлу_конфигурации>"
    echo "Пример: $0 test.txt"
    exit 1
fi

CONFIG_FILE=$1

# 1. Проверяем, существует ли этот файл конфигурации
if [ ! -f "$CONFIG_FILE" ]; then
    echo "Ошибка: Файл конфигурации '$CONFIG_FILE' не найден!"
    exit 1
fi

CPP_BINARY="./src/cpp/build/main"
CSV_RESULT="./result.csv"
PYTHON_SCRIPT="./src/python/gui.py"


if [ ! -f "$CPP_BINARY" ]; then
    echo "Ошибка: С++ бинарник не найден по пути $CPP_BINARY"
    echo "Сначала запустите ./install.sh"
    exit 1
fi

echo "=========================================="
echo "Шаг 1: Запуск С++ симуляции..."
echo "Файл конфигурации: $CONFIG_FILE"
echo "=========================================="


$CPP_BINARY "$CONFIG_FILE"


if [ $? -ne 0 ]; then
    echo "Ошибка во время работы С++ программы!"
    exit 1
fi


if [ ! -f "$CSV_RESULT" ]; then
    echo "Ошибка: Симуляция завершилась, но файл результатов '$CSV_RESULT' не создался."
    exit 1
fi

echo ""
echo "=========================================="
echo "Шаг 2: Запуск Python скрипта для графиков..."
echo "Файл данных: $CSV_RESULT"
echo "=========================================="


python3 "$PYTHON_SCRIPT" "$CSV_RESULT"

echo "Работа полностью завершена!"