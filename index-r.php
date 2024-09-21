<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Status Monitor</title>

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
    <script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
    <script src="https://cdn.datatables.net/1.10.21/js/jquery.dataTables.min.js"></script>
    <script>
        function fetchStatus() {
            fetch('https://catuses.com/proyecto/show_status.php')
                .then(response => response.text())
                .then(data => {
                    const status = parseInt(data, 10);
                    const ledStatus = document.getElementById('ledStatus');
                    const toggleButton = document.getElementById('toggleButton');
                    
                    if (status === 1) {
                        ledStatus.textContent = "LED is ON";
                        ledStatus.style.color = "green";
                        toggleButton.classList.remove('btn-off');
                        toggleButton.classList.add('btn-on');
                    } else {
                        ledStatus.textContent = "LED is OFF";
                        ledStatus.style.color = "red";
                        toggleButton.classList.remove('btn-on');
                        toggleButton.classList.add('btn-off');
                    }
                })
                .catch(error => console.error('Error fetching status:', error));
        }

        function fetchTableData() {
            fetch('https://catuses.com/proyecto/fetch_table_data.php')
                .then(response => response.json())
                .then(data => {
                    const table = $('#statusTable').DataTable();
                    table.clear(); // Clear existing data
                    data.forEach(row => {
                        table.row.add([row.id, row.status]);
                    });
                    table.draw(); // Redraw table
                })
                .catch(error => console.error('Error fetching table data:', error));
        }

        function toggleStatus() {
            fetch('https://catuses.com/proyecto/save.php?status=1') // Send request to turn LED on
                .then(response => response.text())
                .then(data => {
                    console.log('Response:', data);
                    fetchStatus(); // Update status after toggling
                })
                .catch(error => console.error('Error updating status:', error));
        }

        $(document).ready(function() {
            fetchStatus(); // Initial fetch for LED status
            fetchTableData(); // Initial fetch for table data
            setInterval(fetchStatus, 1000); // Poll LED status every second
            setInterval(fetchTableData, 1000); // Poll table data every 10 seconds

            // DataTable initialization
            $('#statusTable').DataTable({
                // Configuration options can go here
            });

            // Event listener for the button
            $('#toggleButton').click(function() {
                const status = $(this).hasClass('btn-on') ? 0 : 1;
                fetch(`https://catuses.com/proyecto/save.php?status=${status}`)
                    .then(response => response.text())
                    .then(data => {
                        console.log('Response:', data);
                        fetchStatus(); // Update status after toggling
                    })
                    .catch(error => console.error('Error updating status:', error));
            });
        });
    </script>
</head>

<body>
    <div class="container">
        <h1 class="mb-4">Status Monitor</h1>
        <div class="row">
            <div class="col-md-6">
                <div class="card">
                    <div class="card-body">
                        <h5 class="card-title">LED Status</h5>
                        <p id="ledStatus" class="status">Loading...</p>
                        <button id="toggleButton" class="btn btn-status">Toggle LED</button>
                    </div>
                </div>
            </div>
            <div class="col-md-6">
                <table id="statusTable" class="table table-striped table-bordered">
                    <thead>
                        <tr>
                            <th>Time</th>
                            <th>Status</th>
                        </tr>
                    </thead>
                    <tbody>
                        <!-- Table data will be inserted here by JavaScript -->
                    </tbody>
                </table>
            </div>
        </div>
    </div>
</body>

</html>
