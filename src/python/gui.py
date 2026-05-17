import csv
import matplotlib.pyplot as plt
import sys
import os

def calculate_traffic_metrics(file_path):

    packet_times = []
    packet_sizes = []

    with open(file_path, mode='r', newline='') as f:
        csv_reader = csv.reader(f)
        next(csv_reader)
        for row in csv_reader:
            if not row:
                continue
            packet_times.append(float(row[0]))
            packet_sizes.append(int(row[1]))

    total_packets = len(packet_times)
    

    if total_packets == 0:
        return [], [], "unknown", 0.0, 0.0, 0.0

    avg_packet_size = sum(packet_sizes) / total_packets


    intervals = []
    for i in range(1, total_packets):
        diff = packet_times[i] - packet_times[i-1]
        intervals.append(diff)


    if len(intervals) > 0:
        avg_packet_delay = sum(intervals) / len(intervals)
        
        if max(intervals) - min(intervals) < 1e-6:
            model_name = "Равномерная (Equal)"
        else:
            model_name = "Пуассоновская (Poisson)"
    else:
        avg_packet_delay = 0.0
        model_name = "Равномерная (Equal)"

    total_bits = sum(packet_sizes) * 8
    simulation_time = max(packet_times) if len(packet_times) > 0 else 1.0
    
    if simulation_time > 0:
        avg_bitrate = total_bits / simulation_time
    else:
        avg_bitrate = 0.0

    return intervals, packet_sizes, model_name, avg_packet_size, avg_bitrate, avg_packet_delay


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Ошибка запуска!")
        print(f"Правильный формат: python {sys.argv[0]} <путь_к_csv>")
        print("Пример: python main.py output.csv")
        sys.exit(1)

    csv_path = sys.argv[1]

    if not os.path.exists(csv_path):
        print(f"Ошибка: Файл '{csv_path}' не найден.")
        sys.exit(1)


    delays, sizes, traffic_model_name, avg_size, bitrate, avg_delay = calculate_traffic_metrics(csv_path)

    if not sizes:
        print("Файл пуст или содержит некорректные данные.")
        sys.exit(1)

    # Print stats to console
    print("=" * 45)
    print(f"Модель сетевого трафика: {traffic_model_name}")
    print(f"Средний размер пакета: {avg_size:.4f} байт")
    print(f"Средний битрейт: {bitrate:.4f} бит/с")
    print(f"Средняя задержка между пакетами: {avg_delay:.4f} с")
    print(f"Всего пакетов обработано: {len(sizes)}")
    print("=" * 45)


    plt.figure(figsize=(11, 5))


    plt.subplot(1, 2, 1)
    if delays:
        plt.hist(delays, bins=40, color='lightgreen', edgecolor='darkgreen')
        plt.xlabel('Задержка времени (с)')
        plt.ylabel('Количество интервалов')
    else:
        plt.text(0.5, 0.5, 'Нет данных для задержек (1 пакет)', ha='center')
    plt.title('Гистограмма задержек')
    plt.grid(True, linestyle='--', alpha=0.6)


    plt.subplot(1, 2, 2)
    plt.hist(sizes, bins=40, color='coral', edgecolor='brown')
    plt.title('Гистограмма размеров пакетов')
    plt.xlabel('Размер одного пакета (байт)')
    plt.ylabel('Количество пакетов')
    plt.grid(True, linestyle='--', alpha=0.6)

    plt.tight_layout()

    plt.show()