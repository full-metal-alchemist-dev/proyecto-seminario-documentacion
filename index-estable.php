<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Status and Potentiometer Monitor</title>

    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css" rel="stylesheet">
    <link href="https://cdn.datatables.net/1.10.21/css/jquery.dataTables.min.css" rel="stylesheet">
    <style>
        body {
            padding: 20px;
        }

        .status {
            font-weight: bold;
        }

        .btn-status {
            font-weight: bold;
        }

        .btn-on {
            background-color: green;
            color: white;
        }

        .btn-off {
            background-color: red;
            color: white;
        }
    </style>

    <!-- Chart.js CDN -->
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

    <script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
    <script src="https://cdn.datatables.net/1.10.21/js/jquery.dataTables.min.js"></script>

    <script>
        let potentiometerChart;

        // Fetch LED status and update UI
        function fetchStatus() {
            fetch('https://catuses.com/proyecto/show_status.php')
                .then(response => response.text())
                .then(data => {
                    const status = parseInt(data, 10);
                    const ledStatus = document.getElementById('ledStatus');
                    const toggleButton = document.getElementById('toggleButton');

                    if (status === 1) {
                        ledStatus.textContent = "El LED está encendido";
                        ledStatus.style.color = "green";
                        toggleButton.classList.remove('btn-off');
                        toggleButton.classList.add('btn-on');
                        toggleButton.textContent = "Apagar LED";
                    } else {
                        ledStatus.textContent = "El LED está apagado";
                        ledStatus.style.color = "red";
                        toggleButton.classList.remove('btn-on');
                        toggleButton.classList.add('btn-off');
                        toggleButton.textContent = "Encender LED";
                    }
                })
                .catch(error => console.error('Error fetching status:', error));
        }

        // Fetch table data for LED status history
        function fetchTableData() {
            fetch('https://catuses.com/proyecto/fetch_table_data.php')
                .then(response => response.json())
                .then(data => {
                    const table = $('#statusTable').DataTable();
                    table.clear();
                    data.forEach(row => {
                        table.row.add([row.id, row.status == 1 ? 'ENCENDIDO' : 'APAGADO']);
                    });
                    table.draw();
                })
                .catch(error => console.error('Error fetching table data:', error));
        }

        // Fetch potentiometer data and update both table and chart
        function fetchPotentiometerData() {
            fetch('https://catuses.com/proyecto/fetch_potentiometer_data.php')
                .then(response => response.json())
                .then(data => {
                    const potTable = $('#potentiometerTable').DataTable();
                    potTable.clear();
                    const labels = [];
                    const values = [];

                    data.forEach(row => {
                        potTable.row.add([row.id, row.pot_value, row.recorded_at]);
                        labels.push(row.recorded_at);
                        values.push(row.pot_value);
                    });
                    potTable.draw();

                    // Update Chart
                    updateChart(potentiometerChart, labels, values);
                })
                .catch(error => console.error('Error fetching potentiometer data:', error));
        }

        // Update the Chart.js chart
        function updateChart(chart, labels, data) {
            chart.data.labels = labels;
            chart.data.datasets[0].data = data;
            chart.update();
        }

        // Toggle LED status
        function toggleStatus() {
            fetch('https://catuses.com/proyecto/save.php?status=1')
                .then(response => response.text())
                .then(data => {
                    console.log('Response:', data);
                    fetchStatus();
                })
                .catch(error => console.error('Error updating status:', error));
        }

        $(document).ready(function() {
            fetchStatus();
            fetchTableData();
            fetchPotentiometerData();

            setInterval(fetchStatus, 1000); // Fetch LED status every second
            setInterval(fetchTableData, 1000); // Fetch status table every second
            setInterval(fetchPotentiometerData, 1000); // Fetch potentiometer data every second

            // Initialize DataTables
            $('#statusTable').DataTable();
            $('#potentiometerTable').DataTable();

            // Initialize Chart.js
            const ctx = document.getElementById('potentiometerChart').getContext('2d');
            potentiometerChart = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: [],
                    datasets: [{
                        label: 'lectura del voltaje en tiempo real',
                        data: [],
                        backgroundColor: 'rgba(0, 123, 255, 0.2)',
                        borderColor: 'rgba(0, 123, 255, 1)',
                        borderWidth: 2,
                        fill: true
                    }]
                },
                options: {
                    scales: {
                        x: {
                            title: {
                                display: true,
                                text: 'Timestamp'
                            }
                        },
                        y: {
                            title: {
                                display: true,
                                text: 'Voltage'
                            },
                            beginAtZero: true
                        }
                    }
                }
            });

            // Button toggle listener
            $('#toggleButton').click(function() {
                const status = $(this).hasClass('btn-on') ? 0 : 1;
                fetch(`https://catuses.com/proyecto/save.php?status=${status}`)
                    .then(response => response.text())
                    .then(data => {
                        console.log('Response:', data);
                        fetchStatus();
                    })
                    .catch(error => console.error('Error updating status:', error));
            });
        });
    </script>
</head>

<body>
    <div class="container">
        <h1 class="mb-4">Monitoreo en Tiempo Real</h1>
        <div class="row">
            <!-- LED Status Card -->
            <div class="col-md-6">
                <div class="card">
                    <div class="card-body">
                        <h5 class="card-title">Estado del LED</h5>
                        <p id="ledStatus" class="status">Cargando...</p>
                        <button id="toggleButton" class="btn btn-status">Cambiar estado LED</button>
                    </div>
                </div>
            </div>

            <!-- Status Table -->
            <div class="col-md-6">
                <table id="statusTable" class="table table-striped table-bordered">
                    <thead>
                        <tr>
                            <th>Id</th>
                            <th>Estado</th>
                        </tr>
                    </thead>
                    <tbody></tbody>
                </table>
            </div>
        </div>

        <hr>

        <!-- Potentiometer Table -->
        <h2>Lectura de Voltajes en tiempo real (c/1s)</h2>
        <table id="potentiometerTable" class="table table-striped table-bordered">
            <thead>
                <tr>
                    <th>Id</th>
                    <th>Voltaje</th>
                    <th>Fecha y Hora</th>
                </tr>
            </thead>
            <tbody></tbody>
        </table>

        <!-- Potentiometer Chart -->
        <h2>Gráfico de Voltaje</h2>
        <canvas id="potentiometerChart" width="400" height="200"></canvas>
    </div>
</body>

</html>